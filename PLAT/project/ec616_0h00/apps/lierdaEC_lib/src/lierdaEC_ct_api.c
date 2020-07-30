/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of EigenComm Ltd.
 * File name:    app.c
 * Description:  EC616 China Telecomm NB-IOT demo ct_api source file
 *               this file complete the work of the lwm2m client,the recovery work of the timer wakeup,
 *               and the work of key wakeup
 * History:      Rev1.0   2020-03-24
 *
 ****************************************************************************/
#include "bsp.h"
#include "bsp_custom.h"
#include "osasys.h"
#include "ostask.h"
#include "queue.h"
#include "ps_event_callback.h"
#include "lierdaEC_ct_api.h"
#include "psifevent.h"
#include "ps_lib_api.h"
#include "lwip/netdb.h"
#include "ctiot_NV_data.h"
#include "ec_ctlwm2m_api.h"
#include "debug_log.h"
#include "slpman_ec616.h"

#define STR_MACHINESTATE(S) \
    ((S) == APP_INIT_STATE ? "APP_INIT_STATE" : ((S) == APP_DEACTIVE_STATE ? "APP_DEACTIVE_STATE" : ((S) == APP_CHECK_IPREADY_FROM_WAKE ? "APP_CHECK_IPREADY_FROM_WAKE" : ((S) == APP_IPREADY_STATE ? "APP_IPREADY_STATE" : ((S) == APP_OC_OBV_SUB_STATE ? "APP_OC_OBV_SUB_STATE" : ((S) == APP_OC_HEART_BEAT_UPDATE ? "APP_OC_HEART_BEAT_UPDATE" : ((S) == APP_OC_HEART_BEAT_ARRIVED ? "APP_OC_HEART_BEAT_ARRIVED" : ((S) == APP_OC_HEART_BEAT_SEND ? "APP_OC_HEART_BEAT_SEND" : ((S) == APP_OC_CONTEXT_RECOVER ? "APP_OC_CONTEXT_RECOVER" : ((S) == APP_OC_UPDATE_SUCCESS_STATE ? "APP_OC_UPDATE_SUCCESS_STATE" : ((S) == APP_OC_REG_SUCCESS_STATE ? "APP_OC_REG_SUCCESS_STATE" : ((S) == APP_SENDING_PACKET_STATE ? "APP_SENDING_PACKET_STATE" : ((S) == APP_WAITING_ONLINE_STATE ? "APP_WAITING_ONLINE_STATE" : ((S) == APP_IDLE_STATE ? "APP_IDLE_STATE" : "Unknown"))))))))))))))

#define STR_CT_REG_EVENT(S) \
    ((S) == REG_FAILED_TIMEOUT ? "REG_FAILED_TIMEOUT" : ((S) == REG_FAILED_AUTHORIZE_FAIL ? "REG_FAILED_AUTHORIZE_FAIL" : ((S) == REG_FAILED_ERROR_ENDPOINTNAME ? "REG_FAILED_ERROR_ENDPOINTNAME" : ((S) == REG_FAILED_PROTOCOL_NOT_SUPPORT ? "REG_FAILED_PROTOCOL_NOT_SUPPORT" : ((S) == REG_FAILED_OTHER ? "REG_FAILED_OTHER" : "Unknown")))))

#define STR_CT_UPDATE_EVENT(S) \
    ((S) == UPDATE_FAILED_TIMEOUT ? "UPDATE_FAILED_TIMEOUT" : ((S) == UPDATE_FAILED_SEND ? "UPDATE_FAILED_SEND" : ((S) == UPDATE_FAILED_SERVER_FORBIDDEN ? "UPDATE_FAILED_SERVER_FORBIDDEN" : ((S) == UPDATE_FAILED_WRONG_PARAM ? "UPDATE_FAILED_WRONG_PARAM" : ((S) == UPDATE_FAILED_UE_OFFLINE ? "UPDATE_FAILED_UE_OFFLINE" : "Unknown")))))

// app task static stack and control block
#define CT_TASK_STACK_SIZE (2048)
static StaticTask_t ctTask;
static UINT8 ctTaskStack[CT_TASK_STACK_SIZE];

appStateMachine_t stateMachine = APP_INIT_STATE;
UINT8 recvBuff[256] = {0};
slpManTimerID_e heartBeatTimerID = DEEPSLP_TIMER_ID0;
slpManTimerID_e sendDataTimerID = DEEPSLP_TIMER_ID1;
UINT32 defaultLifetime = 86400;
extern UINT32 sendDataItv;
QueueHandle_t ct_state_msg_handle = NULL;
UINT8 deactCount = 0;
UINT8 pressKey = KEY_NOT_PRESS;

extern QueueHandle_t app_cmd_msg_handle;

static INT32 ocPSUrcCallback(urcID_t eventID, void *param, UINT32 paramLen)
{
    UINT8 rssi = 0;
    CmiPsCeregInd *cereg = NULL;
    NmAtiNetifInfo *netif = NULL;
    ctiot_funcv1_context_t *pContext = ctiot_funcv1_get_context();
    ctiot_funcv1_chip_info_ptr pChipInfo = pContext->chipInfo;

    switch (eventID)
    {
    case NB_URC_ID_MM_SIGQ:
    {
        rssi = *(UINT8 *)param;
        ECOMM_TRACE(UNILOG_PLA_APP, ocPSUrcCallback_1, P_INFO, 1, "URCCallBack:RSSI signal=%d", rssi);
        break;
    }
    case NB_URC_ID_PS_BEARER_ACTED:
    {
        ECOMM_TRACE(UNILOG_PLA_APP, ocPSUrcCallback_2, P_INFO, 0, "URCCallBack:Default bearer activated");
        break;
    }
    case NB_URC_ID_PS_BEARER_DEACTED:
    {
        ECOMM_TRACE(UNILOG_PLA_APP, ocPSUrcCallback_3, P_INFO, 0, "URCCallBack:Default bearer Deactivated");
        break;
    }
    case NB_URC_ID_PS_CEREG_CHANGED:
    {
        cereg = (CmiPsCeregInd *)param;
        ECOMM_TRACE(UNILOG_PLA_APP, ocPSUrcCallback_4, P_INFO, 4, "URCCallBack:CEREG changed act:%d celId:%d locPresent:%d tac:%d", cereg->act, cereg->celId, cereg->locPresent, cereg->tac);
        break;
    }
    case NB_URC_ID_MM_CERES_CHANGED: //网络覆盖等级变化事件
    {
        /*
             * 0 No Coverage Enhancement in the serving cell
             * 1 Coverage Enhancement level 0
             * 2 Coverage Enhancement level 1
             * 3 Coverage Enhancement level 2
             * 4 Coverage Enhancement level 3
            */
        pChipInfo->cSignalLevel = (ctiot_funcv1_signal_level_e)(*(uint8_t *)param);
        ctiot_setCoapAckTimeout(pChipInfo->cSignalLevel);
        ECOMM_TRACE(UNILOG_PLA_APP, ocPSUrcCallback_5, P_INFO, 1, "URCCallBack:NB_URC_ID_MM_CERES_CHANGED celevel=%d", pChipInfo->cSignalLevel);
        break;
    }
    case NB_URC_ID_PS_NETINFO:
    {
        netif = (NmAtiNetifInfo *)param;
        if (netif->netStatus == NM_NETIF_ACTIVATED)
        {
            stateMachine = APP_IPREADY_STATE;
            ECOMM_TRACE(UNILOG_PLA_APP, ocPSUrcCallback_6, P_INFO, 0, "URCCallBack:PSIF network active");
        }
        else
        {
            stateMachine = APP_DEACTIVE_STATE;
            ECOMM_TRACE(UNILOG_PLA_APP, ocPSUrcCallback_7, P_ERROR, 0, "URCCallBack:PSIF network deactive");
        }
        break;
    }
    }
    return 0;
}

static void ctEventHandler(module_type_t type, INT32 code, const CHAR *arg, INT32 arg_len)
{
    char logbuf[64] = {0};
    CT_STATUS_Q_MSG ctMsg;
    memset(&ctMsg, 0, sizeof(ctMsg));

    switch (type)
    {
    case MODULE_LWM2M:
    {
        if (code == REG_SUCCESS)
        {
            stateMachine = APP_OC_REG_SUCCESS_STATE; //register ok still need waiting server observe
            ECOMM_TRACE(UNILOG_PLA_APP, ctEventHandler_0, P_INFO, 0, "ctiot register successful");
        }
        else if (code >= REG_FAILED_TIMEOUT && code <= REG_FAILED_OTHER)
        {
            stateMachine = APP_WAIT_APP_ACT; //register fail notify app
            snprintf(logbuf, 64, "%s", STR_CT_REG_EVENT(code));
            ECOMM_STRING(UNILOG_PLA_APP, ctEventHandler_1, P_INFO, "ctiot register failed:%s", (uint8_t *)logbuf);
            ctMsg.status_type = APP_OC_REG_FAILED;
            xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
        }
        else if (code == OBSERVE_UNSUBSCRIBE)
        {
            stateMachine = APP_WAIT_APP_ACT; //observe cancel by server notify app
            ECOMM_TRACE(UNILOG_PLA_APP, ctEventHandler_2, P_INFO, 0, "ctiot observe unsubscribe");
            ctMsg.status_type = APP_OC_OBSV_FAILED;
            xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
        }
        else if (code == OBSERVE_SUBSCRIBE)
        {
            stateMachine = APP_OC_OBV_SUB_STATE; //observe success can send data
            ECOMM_TRACE(UNILOG_PLA_APP, ctEventHandler_3, P_INFO, 0, "ctiot observe subscribe");
        }
        else if (code == SEND_CON_DONE)
        {
            stateMachine = APP_IDLE_STATE; //send data success goto idle state
            if (pressKey == KEY_RESPONSING)
            {
                pressKey = KEY_NOT_PRESS; //send data success clear key status, can response next key press
            }
            ECOMM_TRACE(UNILOG_PLA_APP, ctEventHandler_4, P_INFO, 0, "ctiot send con arrived");
            ctMsg.status_type = APP_SEND_PACKET_DONE;
            xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
        }
        else if (code == SEND_FAILED) //send failed notify app to retry or re-register
        {
            stateMachine = APP_WAIT_APP_ACT;
            ECOMM_TRACE(UNILOG_PLA_APP, ctEventHandler_5, P_INFO, 0, "ctiot send failed");
            ctMsg.status_type = APP_SEND_PACKET_FAILED;
            xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
        }
        else if (code == UPDATE_SUCCESS) //
        {
            ECOMM_TRACE(UNILOG_PLA_APP, ctEventHandler_6, P_INFO, 0, "ctiot update success");
            if (stateMachine == APP_IDLE_STATE)
            {
                stateMachine = APP_OC_UPDATE_SUCCESS_STATE; //if no need send data, enable sleep
            }
        }
        else if (code >= UPDATE_FAILED_TIMEOUT && code <= UPDATE_FAILED_UE_OFFLINE)
        {
            stateMachine = APP_WAIT_APP_ACT; //update failed, notify app to re-register
            snprintf(logbuf, 64, "%s", STR_CT_UPDATE_EVENT(code));
            ECOMM_STRING(UNILOG_PLA_APP, ctEventHandler_7, P_INFO, "ctiot update failed:%s", (uint8_t *)logbuf);
            ctMsg.status_type = APP_UPDATE_FAILED;
            xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
            stateMachine = APP_WAIT_APP_ACT;
        }
        else if (code == RECV_RST_CMD)
        {
            stateMachine = APP_WAIT_APP_ACT; //recevie server's rst cmd, notify app to re-register
            ECOMM_TRACE(UNILOG_PLA_APP, ctEventHandler_8, P_INFO, 0, "ctiot recv RST command notify app");
            ctMsg.status_type = APP_RECV_RST_CMD;
            xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
        }
        break;
    }
    case MODULE_COMM:
    {
        if (code == RECV_DATA_MSG) //recive data from server user can extended implementation
        {
            memset(recvBuff, 0, sizeof(recvBuff));
            memcpy(recvBuff, arg, ((arg_len > 256) ? 256 : arg_len));
            ECOMM_STRING(UNILOG_PLA_APP, ctEventHandler_9, P_INFO, "%s", recvBuff);
            stateMachine = APP_IDLE_STATE;
            ctiot_funcv1_sleep_vote(SYSTEM_STATUS_FREE);
        }
        break;
    }
    }
}

void appTimerExpFunc(uint8_t id)
{
    ECOMM_TRACE(UNILOG_PLA_APP, appTimerExpFunc_1, P_SIG, 1, "User DeepSleep Timer Expired: TimerID = %u", id);
    ctiot_funcv1_disable_sleepmode();
    if (heartBeatTimerID == id)
    {
        ECOMM_TRACE(UNILOG_PLA_APP, appTimerExpFunc_2, P_SIG, 0, "it's heartbeat time up");
        if (stateMachine != APP_CHECK_IPREADY_FROM_WAKE)
        { //if not in sending data, to heartbeat, if sending data no need heartbeat
            stateMachine = APP_OC_HEART_BEAT_ARRIVED;
        }
        else
        {
            ECOMM_TRACE(UNILOG_PLA_APP, appTimerExpFunc_2_1, P_SIG, 0, "already in send data time");
        }
        slpManDeepSlpTimerStart(heartBeatTimerID, defaultLifetime * 1000);
    }
    else if (sendDataTimerID == id)
    {
        ECOMM_TRACE(UNILOG_PLA_APP, appTimerExpFunc_3, P_SIG, 1, "it's send data time up (%d)s", sendDataItv);
        stateMachine = APP_CHECK_IPREADY_FROM_WAKE;
        slpManDeepSlpTimerStart(sendDataTimerID, sendDataItv * 1000);
    }
}

static void ctConnectTask(void *arg)
{
    INT8 ret;
    UINT8 *serverIP = "180.101.147.115";
    UINT16 portNum = 5683;
    CT_STATUS_Q_MSG ctMsg;
    memset(&ctMsg, 0, sizeof(ctMsg));

    ctiot_funcv1_context_t *pContext = ctiot_funcv1_get_context();

    while (1)
    {
        char logbuf[64] = {0};
        snprintf(logbuf, 64, "%s", STR_MACHINESTATE(stateMachine));
        ECOMM_STRING(UNILOG_PLA_APP, ctConnectTask_0, P_INFO, "handle stateMachine:%s", (uint8_t *)logbuf);
        switch (stateMachine)
        {
        case APP_INIT_STATE:
            osDelay(500 / portTICK_PERIOD_MS);
            break;
        case APP_OC_CONTEXT_RECOVER:   //wake up to recover nb-iot's context
        case APP_OC_HEART_BEAT_UPDATE: //to heartbeat
        case APP_IPREADY_STATE:        //poweron to register
        {
            pContext->chipInfo->cState = NETWORK_CONNECTED;
            pContext->autoHeartBeat = AUTO_HEARTBEAT;
            pContext->lifetime = defaultLifetime;
            if (appGetImeiNumSync(pContext->chipInfo->cImei) != NBStatusSuccess)
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_1, P_ERROR, 0, "appGetImeiNumSync error");
            }
            ECOMM_STRING(UNILOG_PLA_APP, ctConnectTask_2, P_INFO, "%s", (uint8_t *)pContext->chipInfo->cImei);
            if (pContext->protocolMode == PROTOCOL_MODE_ENHANCE)
            {
                if (appGetAPNSettingSync(0, (UINT8 *)(pContext->chipInfo->cApn)) != NBStatusSuccess)
                {
                    ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_2_1, P_ERROR, 0, "appGetAPNSettingSync error");
                }
            }
            ctiot_funcv1_set_mod(NULL, 0, 1, 0, 0, 0, 0, 0, 0);
            ctiot_funcv1_register_event_handler(ctEventHandler);
            if ((pContext->bootFlag == BOOT_LOCAL_BOOTUP) || (pContext->bootFlag == BOOT_FOTA_REBOOT))
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_3, P_INFO, 0, "call ctiot_session_init");
                ret = ctiot_funcv1_session_init(pContext);
            }
            else
            {
                ret = ctiot_funcv1_set_pm(NULL, (char *)serverIP, portNum, defaultLifetime, NULL);
                if (ret == CTIOT_NB_SUCCESS)
                {
                    ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_4, P_INFO, 0, "OC set platform parameters success");
                }
                else
                {
                    ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_4_1, P_INFO, 1, "OC set platform parameters fail ret=%d", ret);
                    ctMsg.status_type = APP_PARAM_ERROR;
                    xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
                    stateMachine = APP_WAIT_APP_ACT;
                    break;
                }
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_5, P_INFO, 0, "direct call register function");
                ret = ctiot_funcv1_reg(NULL);
            }

            if (ret == CTIOT_NB_SUCCESS)
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_6, P_INFO, 0, "OC register/restore call success");
                if (stateMachine == APP_OC_CONTEXT_RECOVER) //after recover context it can send data
                {
                    stateMachine = APP_SENDING_PACKET_STATE;
                    ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_6_1, P_INFO, 0, "notify app to send data");
                    ctMsg.status_type = APP_READY_TO_SEND_PACKET;
                    xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
                }
                else if (stateMachine == APP_OC_HEART_BEAT_UPDATE) //can heartbeat
                {
                    stateMachine = APP_OC_HEART_BEAT_SEND;
                }
                else if (stateMachine == APP_IPREADY_STATE) //power on wait to online server
                {
                    stateMachine = APP_WAITING_ONLINE_STATE;
                }
            }
            else
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_7, P_INFO, 1, "OC register fail ret=%d", ret);
                stateMachine = APP_WAIT_APP_ACT;
                ctMsg.status_type = APP_INTER_ERROR; //it can't go here check code
                xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
                break;
            }

            break;
        }
        case APP_OC_HEART_BEAT_ARRIVED:
        {
            // Here check actively can't got it from URC callback
            if (ctiot_funcv1_wait_cstate(pContext->chipInfo) != 0)
            {
                pContext->chipInfo->cState = NETWORK_MANUAL_RESTART;
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_8_1, P_ERROR, 0, "app update network connect error");
                stateMachine = APP_WAIT_APP_ACT;
                ctMsg.status_type = APP_NETWORK_DISC;
                xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
            }
            else
            {
                stateMachine = APP_OC_HEART_BEAT_UPDATE;
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_8, P_ERROR, 0, "network ok send heartbeat");
            }
            break;
        }
        case APP_OC_HEART_BEAT_SEND: //check the ct client complete login and update for heartbeat
        {
            //RegisterUpdate;
            if (pContext->loginStatus == UE_LOGINED)
            {
                lwm2m_server_t *serverP = pContext->lwm2mContext->serverList;
                while (serverP != NULL)
                {
                    extern int updateRegistration(lwm2m_context_t * contextP, lwm2m_server_t * server);
                    updateRegistration(pContext->lwm2mContext, serverP);
                    serverP = serverP->next;
                }
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_9, P_ERROR, 0, "has send update package");
                stateMachine = APP_IDLE_STATE;
            }
            else
            {
                osDelay(1000 / portTICK_PERIOD_MS);
            }
            break;
        }
        case APP_OC_OBV_SUB_STATE: //complete observe start heartbeat timer and send data timer
        {
            ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_10, P_INFO, 0, "start heartbeat timer, notify app to send package");
            if (slpManDeepSlpTimerIsRunning(heartBeatTimerID) == FALSE)
                slpManDeepSlpTimerStart(heartBeatTimerID, defaultLifetime * 1000);
            if (slpManDeepSlpTimerIsRunning(sendDataTimerID) == FALSE)
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_10_1, P_INFO, 1, "start send data timer (%d)s", sendDataItv);
                slpManDeepSlpTimerStart(sendDataTimerID, sendDataItv * 1000);
            }
            stateMachine = APP_SENDING_PACKET_STATE;
            ctMsg.status_type = APP_READY_TO_SEND_PACKET;
            xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
            break;
        }
        case APP_CHECK_IPREADY_FROM_WAKE: //after wakeup check the ip ready
        {
            if (ctiot_funcv1_wait_cstate(pContext->chipInfo) != 0) //connection timed out
            {
                //处理无线连接超时
                pContext->chipInfo->cState = NETWORK_MANUAL_RESTART;
                stateMachine = APP_WAIT_APP_ACT;
                ctMsg.status_type = APP_NETWORK_DISC; //notify app network can't connect
                xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_11_1, P_ERROR, 0, "network connect failed");
            }
            else
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_11, P_ERROR, 0, "from wakeup ip ready, to restore oc client");
                stateMachine = APP_OC_CONTEXT_RECOVER; //network available to recover nb-iot's context
            }
            break;
        }
        case APP_OC_UPDATE_SUCCESS_STATE: //heartbeat complete go to idle
        {
            ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_12, P_INFO, 0, "update success enable sleep and app enter idle");
            ctiot_funcv1_enable_sleepmode();
            stateMachine = APP_IDLE_STATE;
            break;
        }
        case APP_DEACTIVE_STATE:
        {
            deactCount += 1;
            if (deactCount < 181)
            { //wait 180 second for the network to recover
                osDelay(1000 / portTICK_PERIOD_MS);
            }
            else
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_13, P_INFO, 0, "confirm network disconnect"); //network can't recover notify app to manual recover
                stateMachine = APP_WAIT_APP_ACT;
                ctMsg.status_type = APP_NETWORK_DISC;
                xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
            }
            break;
        }
        case APP_OC_REG_SUCCESS_STATE: //register success wait server observe
        {
            ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_14, P_INFO, 0, "reg success wait observe ready");
            stateMachine = APP_WAITING_ONLINE_STATE;
            break;
        }
        case APP_WAIT_APP_ACT: //wait app's command
        {
            ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_15, P_INFO, 0, "wait app's act");
            APP_CMD_Q_MSG cmdMsg;
            int cmd_type = 0xff;
            xQueueReceive(app_cmd_msg_handle, &cmdMsg, osWaitForever);
            cmd_type = cmdMsg.cmd_type;
            switch (cmd_type)
            {
            case APP_CMD_REINIT_NETWORK: //cfun0->clear preferance frequency->cfun1
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_15_1, P_INFO, 0, "reinit network");
                stateMachine = APP_WAITING_ONLINE_STATE;
                appSetCFUN(0);
                osDelay(5000 / portTICK_PERIOD_MS);
                CiotFreqParams para;
                memset(&para, 0, sizeof(CiotFreqParams));
                para.mode = 3;
                appSetCiotFreqSync(&para);
                appSetCFUN(1);
                break;
            }
            case APP_CMD_REG_AGAIN:
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_15_2, P_INFO, 0, "register ct again");
                stateMachine = APP_OC_CONTEXT_RECOVER; //to register again
                break;
            }
            case APP_CMD_DEREG_REG:
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_15_3, P_INFO, 0, "deregister ct");
                ret = ctiot_funcv1_dereg(NULL, NULL);
                if (ret == CTIOT_NB_SUCCESS)
                {
                    ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_15_4, P_INFO, 0, "then register ct again");
                    stateMachine = APP_OC_CONTEXT_RECOVER; //after dereg goto reg again
                }
                break;
            }
            }
            break;
        }
        case APP_IDLE_STATE: //nothing to do can handle key event
        {
            ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_16, P_INFO, 0, "app enter idle");
            if (pressKey == KEY_PRESS)
            {
                ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_16_1, P_INFO, 0, "key pressed when active or sleep1 mode, notify app to send data");
                pressKey = KEY_RESPONSING;
                ctMsg.status_type = APP_READY_TO_SEND_PACKET;
                xQueueSend(ct_state_msg_handle, &ctMsg, CT_MSG_TIMEOUT);
            }
            osDelay(500 / portTICK_PERIOD_MS);
            break;
        }
        case APP_SENDING_PACKET_STATE: //send the data waiting ack
        case APP_WAITING_ONLINE_STATE: //waiting nb-iot client online
        default:
        {
            ECOMM_TRACE(UNILOG_PLA_APP, ctConnectTask_17, P_INFO, 0, "app enter waiting state");
            osDelay(500 / portTICK_PERIOD_MS);
            break;
        }
        }
    }
}
// extern void slpManRegisterUsrdefined(void);
void ctApiInit(void)
{
    // Apply own right power policy according to design
    slpManSetPmuSleepMode(true, SLP_HIB_STATE, false);
    ctiot_funcv1_init_sleep_handler();
    // slpManRegisterUsrdefined(); // LUO  200529
    registerPSEventCallback(NB_GROUP_ALL_MASK, ocPSUrcCallback);

    slpManRestoreUsrNVMem();

    if (ct_state_msg_handle == NULL)
    {
        ct_state_msg_handle = xQueueCreate(10, sizeof(CT_STATUS_Q_MSG));
    }
    else
    {
        xQueueReset(ct_state_msg_handle);
    }

    osThreadAttr_t task_attr;
    memset(&task_attr, 0, sizeof(task_attr));
    memset(ctTaskStack, 0xA5, CT_TASK_STACK_SIZE);
    task_attr.name = "ct_task";
    task_attr.stack_mem = ctTaskStack;
    task_attr.stack_size = CT_TASK_STACK_SIZE;
    task_attr.priority = osPriorityNormal;
    task_attr.cb_mem = &ctTask;               //task control block
    task_attr.cb_size = sizeof(StaticTask_t); //size of task control block

    osThreadNew(ctConnectTask, NULL, &task_attr);

    INT32 ret;
    UINT8 cache_boot_flag = 0;
    ctiot_funcv1_context_t *pContext = NULL;
    pContext = ctiot_funcv1_get_context();
    ret = f2c_encode_params(pContext);
    if (ret != NV_OK) //can't read flash
    {
        ECOMM_TRACE(UNILOG_CTLWM2M, ctApiInit_0, P_INFO, 0, "f2c_encode_params fail,use default params");
    }
    slpManSlpState_t slpState = slpManGetLastSlpState();
    ECOMM_TRACE(UNILOG_PLA_APP, ctApiInit_1, P_INFO, 1, "slpState = %d", slpState);
    if (slpState == SLP_HIB_STATE || slpState == SLP_SLP2_STATE) //wakeup from deep sleep
    {
        if (pressKey == KEY_PRESS)
        { //wakeup by key
            ECOMM_TRACE(UNILOG_PLA_APP, ctApiInit_2, P_INFO, 0, "wakeup by pad3 key. set machinestate and disable sleep");
            pressKey = KEY_RESPONSING;
            stateMachine = APP_CHECK_IPREADY_FROM_WAKE;
            ctiot_funcv1_disable_sleepmode();
        }
        ECOMM_TRACE(UNILOG_PLA_APP, ctApiInit_3, P_INFO, 0, "recover from HIB and sleep2");
        ret = cache_get_bootflag(&cache_boot_flag);
        if (ret == NV_OK)
        {
            pContext->bootFlag = (ctiot_funcv1_boot_flag_e)cache_boot_flag;
        }
        else
        {
            pContext->bootFlag = BOOT_NOT_LOAD;
        }
        ECOMM_TRACE(UNILOG_PLA_APP, ctApiInit_4, P_INFO, 1, "OC example bootflag=%d", pContext->bootFlag);
    }
    else
    {
        pContext->bootFlag = BOOT_NOT_LOAD;
        ret = cache_get_bootflag(&cache_boot_flag);
        if (ret == NV_OK)
        {
            if (cache_boot_flag == BOOT_FOTA_REBOOT)
            {
                pContext->bootFlag = (ctiot_funcv1_boot_flag_e)cache_boot_flag;
                ECOMM_TRACE(UNILOG_CTLWM2M, ctApiInit_5, P_INFO, 0, "reboot because FOTA so need to restore context");
            }
        }
    }
}
