/****************************************************************************

            (c) Copyright 2019 by 天翼物联科技有限公司. All rights reserved.

****************************************************************************/

#ifndef _CTIOT_LWM2M_SDK_H
#define _CTIOT_LWM2M_SDK_H

//#include "ctiot_common_type.h"
#include "../core/ct_liblwm2m.h"
#include "ctiot_aep_msg_queue.h"
#include "ps_event_callback.h"
#include "er-coap-13.h"
#ifdef WITH_MBEDTLS
#include "../port/dtlsconnection.h"
#else
#include "../port/connection.h"
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#define CTIOT_DEFAULT_LOCAL_PORT "56830"
#define CTIOT_DEFAULT_SERVER_ID 123
#define CTIOT_DEFAULT_TAU_TIMER 43200
#define CTIOT_DEREG_WAIT_TIME 20000
#define CTIOT_DEFAULT_LIFETIME(x) 4*x
#define CTIOT_MAX_PACKET_SIZE 1024
#define CTIOT_DEFAULT_CONFIG_FILE_NAME "ctiot_nb.config"
#define CTIOT_MAX_QUEUE_SIZE 20
#define CTIOT_MIN_TAU_TIMER  75
#define CTIOT_DOWNDATA_TIMEOUT 30 //文档�?0S�?
#define CTIOT_MIN_LIFETIME 300
#define CTIOT_THREAD_FREE_TIMEOUT 10
#define CTIOT_CMD_FREE_TIMEOUT 30
#define CTIOT_RECV_TIMEOUT 10
#define CTIOT_THREAD_TIMEOUT 200*1000
#define CTIOT_MAX_IP_LEN     40
#define MAX_DOWNDATA_QUEUE_CHECK_NUM 10
#define CTIOT_MAX_TRAFFIC_TIME 300
#define MAX_INSTANCE_IN_ONE_OBJECT 5
#define MAX_MCU_OBJECT 6

char* ctiot_funcv1_port_str(uint16_t x);

typedef enum{
    SEND_DATA_INITIALIZE,//初始�?
    SEND_DATA_CACHEING,//缓存�?
    SEND_DATA_SENDOUT,//已发�?
    SEND_DATA_DELIVERED,//已送达
    SEND_DATA_TIMEOUT,//发送超�?
    SEND_DATA_RST,//RST
    SEND_DATA_NO_TOKEN_19,//object19 token=0
    SEND_DATA_REQ_RESP=9 //南向请求，北向通知
}ctiot_funcv1_data_send_status_e;
typedef enum{
    THREAD_STATUS_UNKNOWN,
    THREAD_STATUS_BUSY,
    THREAD_STATUS_FREE
}ctiot_funcv1_thread_status_e;
typedef enum
{
    NO_SEC_MODE = 1,
    PRE_TLS_PSK_WITH_AES_128_CCM_8,
    PRE_TLS_PSK_WITH_AES_128_CBC_SHA256,
    AUTO_PSK
}ctiot_funcv1_security_mode_e;     //加密模式
typedef enum
{
    NO_AUTO_HEARTBEAT=1, //不自动心�?
    AUTO_HEARTBEAT     //自动心跳
}ctiot_funcv1_auto_heartbeat_e;//模组自动心跳
typedef enum
{
    SEND_TYPE_NOTIFY_19,///19/0/0 notify
    SEND_TYPE_OTHER,//其他（需判断同步异步发送）
    SEND_TYPE_NOTIFY //请求中Msgid=0或不存在
}ctiot_funcv1_send_type_e;

typedef enum
{
    NO_NOTICE_MCU=1,
    NOTICE_MCU
}ctiot_funcv1_wakeup_notify_e;//模组退出休眠通知，整�?
typedef enum
{
    PROTOCOL_MODE_NORMAL = 1,
    PROTOCOL_MODE_ENHANCE = 2
}ctiot_funcv1_protocol_mode_e;//
typedef enum
{
    DATA_FORMAT_TLV=1,      //按照TLV封装发�?
    DATA_FORMAT_OPAQUE=2,   //按照application/octet-stream封装发�?
    DATA_FORMAT_TEXT = 7,   //按照text/plain封装发�?
    DATA_FORMAT_JSON = 8,   //按照application/vnd.oma.lwm2m+json封装发�?
    DATA_FORMAT_LINK = 9    //按照application/link-format封装发�?
}ctiot_funcv1_send_format_e; //发送时数据格式
typedef enum
{
    DATA_TYPE_STRING=1,
    DATA_TYPE_OPAQUE,
    DATA_TYPE_INTEGER,
    DATA_TYPE_FLOAT,
    DATA_TYPE_BOOL
}ctiot_funcv1_data_type_e;//数据类型定义
typedef enum
{
    MODE_NONEDRX,
    MODE_DRX,
    MODE_eDRX,
    MODE_Other
}ctiot_funcv1_terminal_mode_e;//终端工作模式

typedef enum
{
    AUTHMODE_IMEI=1,
    AUTHMODE_SIMID_MCU=2,
    AUTHMODE_SIM9_MCU=3,
    AUTHMODE_SIMID_MODULE=4,
    AUTHMODE_SIM9_MODULE=5
}ctiot_funcv1_id_auth_mode_e;     //身份认证模式

typedef enum
{
    TAU_UPDATE_NON=1,
    TAU_UPDATE_NOTIFY_MCU,
    TAU_UPDATE_AUTO
}ctiot_funcv1_auto_tau_timer_update_e;     //TAU到期处理模式

typedef enum
{
    DISABLE_UQ_MODE=1,
    ENABLE_UQ_MODE
}ctiot_funcv1_on_uq_mode_e;     //手动阻塞功能

typedef enum
{
    CE_LEVEL2_POLICY_SEND=1,
    CE_LEVEL2_POLICY_NOT_SEND
}ctiot_funcv1_on_ce_level2_policy_e;     //覆盖等级2下的数据发送策�?
#if 1
typedef enum
{
    WITHOUT_PSM_MODE,
    WITH_PSM_MODE
}ctiot_funcv1_wp_saving_mode_e;     //无线省电模式
#endif

typedef enum
{
    NETWORK_UNCONNECTED = 0,//未连�?
    NETWORK_CONNECTED,      //已连�?
    NETWORK_UNAVAILABLE,    //连接不可�?
    NETWORK_JAM,            //网络拥塞
    NETWORK_RECOVERING,     //Engine环境异常，恢复中,与芯片间异常，软启动�?
    NETWORK_MANUAL_RESTART  //Engine环境异常，需手工重启,与芯片间失败，软启动仍失�?
}ctiot_funcv1_wireless_status_e;     //无线连接状�?
typedef enum
{
    SIGNAL_LEVEL_0 = 1,
    SIGNAL_LEVEL_1,
    SIGNAL_LEVEL_2
}ctiot_funcv1_signal_level_e;//无线连接状态下的网络覆盖等�?

typedef enum
{
    UE_NOT_LOGINED,
    UE_LOGINED,
    UE_LOGINING,
    UE_HANGUP,
    UE_LOGIN_OUTING
}ctiot_funcv1_login_status_e;     //登录状�?

typedef enum
{
    BOOT_NOT_LOAD = 0,
    BOOT_LOCAL_BOOTUP,
    BOOT_FOTA_REBOOT,
    BOOT_HANGUP_REBOOT,
    BOOT_FLAG_MAX_VALUE
}ctiot_funcv1_boot_flag_e;     //加载方式
typedef enum
{
    AUTH_IMEI_NAKED,
    AUTH_IMEI_IMEI,
    AUTH_IMEI_IMSI,
    AUTH_IMEI_SM9
}ctiot_funcv1_endpointname_auth_type_e;
typedef enum{
    OBSERVE_SET,                  //set observe且无后续参数
    OBSERVE_CANCEL,               //cancel observe且无后续参数
    OBSERVE_WITH_NO_DATA_FOLLOW=8,//后续�?dataformat>,<data>参数，适用于只有响应码场景
    OBSERVE_WITH_DATA_FOLLOW      //后续�?dataformat>,<data>参数
}ctiot_funcv1_observe_e;
typedef enum
{
    CHIPEVENT_REALTIME,  //实时通知事件
    CHIPEVENT_TAUTIME,   //TAU_Time 到期通知事件
    CHIPEVENT_TRAFFIC,   //拥塞控制事件
    CHIPEVENT_REBOOT     //Reboot事件
}ctiot_funcv1_chip_events_e;
#if 1
typedef struct
{
    uint8_t reserve:4;
    uint8_t sIpFlag:1;
    uint8_t pskFlag:1;
    uint8_t sObjectFlag:1;
    uint8_t regFlag:1;
}ctiot_funcv1_data_state_t;
#endif

typedef enum
{
    PLAT_ENABLED,
    PLAT_DISALBED
}ctiot_funcv1_plat_disable_e;
typedef enum
{
    OPERATE_TYPE_READ = 0,
    OPERATE_TYPE_OBSERVE,
    OPERATE_TYPE_WRITE,
    OPERATE_TYPE_EXECUTE,
    OPERATE_TYPE_DISCOVER,
    OPERATE_TYPE_CREATE,
    OPERATE_TYPE_DELETE
}ctiot_funcv1_operate_type_e;

#if 0
typedef enum
{
    SENDMODE_NON,
    SENDMODE_NON_REL,
    SENDMODE_NON_RAR,
    SENDMODE_CON,
    SENDMODE_CON_RAR,
    SENDMODE_ACK
}ctiot_funcv1_send_mode_e;
#endif
typedef enum
{
    SENDMODE_CON,
    SENDMODE_NON,
    SENDMODE_NON_REL,
    SENDMODE_CON_REL,
    SENDMODE_ACK
}ctiot_funcv1_send_mode_e;

typedef enum
{
    CMD_TYPE_READ,
    CMD_TYPE_OBSERVE,
    CMD_TYPE_WRITE,
    CMD_TYPE_WRITE_PARTIAL,
    CMD_TYPE_WRITE_ATTRIBUTE,
    CMD_TYPE_DISCOVER,
    CMD_TYPE_EXECUTE,
    CMD_TYPE_CREATE,
    CMD_TYPE_DELETE,
}ctiot_funcv1_cmd_type_e;

typedef enum
{
    STATUS_TYPE_SESSION,            //会话状�?
    STATUS_TYPE_TRANSCHANNEL,       //会话状�?
    STATUS_TYPE_MSG,                //消息状�?
    STATUS_TYPE_CONNECT,            //连接状�?
    STATUS_TYPE_COMINFO             //通信信息
}ctiot_funcv1_query_status_type_e; //状态查询状态返回类�?

typedef enum
{
    RESTORE_NONE,      //not in restore
    RESTORE_ING,       //in restore process
    RESTORE_DONE       //restore complete
}ctiot_funcv1_restroe_status_e;     //手动阻塞功能

typedef enum
{
    HAVE_NOT_SEND,       //haven't been send
    SENT_WAIT_RESP,      //sent, wait for response
    SENT_FAIL,           //sent failed
    SEND_TIMEOUT,        //timeout
    SEND_SUC,            //success
    GET_RST              //get reset command
}ctiot_funcv1_condata_status_e;//for *16*

/*AT status definiton*/
#define SR0 "reg,0"                 //登录成功
#define SR1 "reg,1"                 //登录失败，超时或其他原因
#define SR2 "reg,13"                //鉴权失败，Server拒绝接入
#define SR3 "reg,22"                //IOT Protocol或LWM2M版本不支�?
#define SR4 "reg,10"                //Endpoint Name无法识别或参数错�?
#define SR5 "reg,2"                 //未发出报�?
#define SR6 "reg,26"                //Engine异常，MCU需重启

#define SU0 "update,0"              //操作成功
#define SU1 "update,14"             //会话异常，终端未登录
#define SU2 "update,1"              //超时无响�?
#define SU3 "update,10"             //参数错误
#define SU4 "update,13"             //鉴权失败，Server拒绝接入
#define SU5 "update,2"              //未发出报�?

#define SD0 "dereg,0"               //登出成功

#define SL0 "lwstatus,24"           //lwm2m session已经失效
#define SL1 "lwstatus,25"           //会话加载失败
#define SL2 "lwstatus,26"           //engine异常


#define SE2 "lwstatus,28"         //tau到期通知
#define SE3 "lwstatus,29"         //模组退出休眠�?

#define SO1 "obsrv,0"                //object19传送通道已建�?
#define SO2 "obsrv,2"                //object19传输通道取消

//#define SS1 "send,30"               //数据发送状态，缓存�?
#define SS2 "send,31"               //数据发送状态，已发�?
#define SS3 "send,0"                //数据发送状态，已送达
#define SS4 "send,1"                //数据发送状态，发送超�?
#define SS5 "send,9"                //数据发送状态，平台RST响应
#define SS6 "send,32"               //数据发送状态，传送通道失败
#define SS7 "send,11"               //其它错误，处理失�?
#define SS8 "send,2"                //未发出报�?


#define SN2 "notify,31"               //notify数据发送状态，已发�?
#define SN3 "notify,0"                //notify数据发送状态，已送达
#define SN4 "notify,1"                //notify数据发送状态，发送超�?
#define SN5 "notify,9"                //notify数据发送状态，平台RST响应
#define SN6 "notify,32"               //notify数据发送状态，传送通道失败
#define SN7 "notify,11"               //notify其它错误，处理失�?
#define SN8 "notify,2"                //notify未发出报�?

#define SDa0 "disable,42"           //挂起时间到，退出挂�?
#define SDa1 "disable,40"           //即将执行平台挂起操作，携带挂起时�?
#define SDa2 "disable,41"           //挂起开�?

#define FOTA0 "FIRMWARE DOWNLOADING"
#define FOTA1 "FIRMWARE DOWNLOAD FAILED"
#define FOTA2 "FIRMWARE DOWNLOAD SUCCESS"
#define FOTA3 "FIRMWARE UPDATING"
#define FOTA4 "FIRMWARE UPDATE SUCCESS"
#define FOTA5 "FIRMWARE UPDATE FAILED"
#define FOTA6 "FIRMWARE UPDATE OVER"

#define FOTA7 "QLWEVENTIND:6"
#define FOTA8 "QLWEVENTIND:7"

/*AT ERRORs*/
typedef enum
{
    CTIOT_NB_SUCCESS,
    CTIOT_EA_PARAM_NOT_INTIALIZED = 8,          //物联网开放平台连接参数未初始�?
    CTIOT_EA_ENGINE_EXCEPTION = 950,            //Engine异常，恢复中
    CTIOT_EA_NETWORK_TRAFFIC = 951,             //连接不可用，网络拥塞
    CTIOT_EA_SIGNAL_LEVEL2 = 952,               //操作失败，覆盖等�?
    CTIOT_EA_ENGINE_REBOOT = 953,               //Engine异常，需reboot重启
    CTIOT_EA_ALREADY_LOGIN = 33,                //操作失败，已登录
    CTIOT_EA_NOT_LOGIN = 954,                   //操作失败，未登录
    CTIOT_EA_LOGIN_PROCESSING = 955,            //操作失败，登录中
    CTIOT_EA_SUSPENDING = 956,                  //操作失败，挂起中
    CTIOT_EA_CONNECT_USELESS_TEMP = 957,        //连接暂时不可�?
    CTIOT_EA_OPERATION_FAILED_NOSESSION = 958,  //操作失败，不存在会话
    CTIOT_EA_OPERATION_NOT_PERMITTED = 959,     //操作不允�?（on_UQ<>1�?
    CTIOT_EA_OPERATION_NO_AUTHSTR = 960,        //操作失败，SIMID认证，未设置认证�?
    CTIOT_EA_CONNECT_FAILED_SIMCARD = 16,       //连接不可用，卡原因等
    CTIOT_EC_OBJECT_NOT_OBSERVED = 15,          //传送通道不存�?
    CTIOT_EC_MSG_ID_REPETITIVE = 962,           //msgid消息重复请求
    CTIOT_EC_MSG_AREADY_SEND = 963,             //msgid消息已请求发送，不允许再进行数据设置
    CTIOT_EC_MSG_LENGTH_OVERRUN = 964,          //msgid消息payload长度超限
    CTIOT_EC_MSG_ID_ERROR = 965,                //操作失败，msgid错误
    CTIOT_EC_MSG_SETDATA_FIRST = 966,           //操作失败，应先通过AT+CTM2MSETDATA设置发送数�?
    CTIOT_ED_PSK_ERROR = 5,                     //PSK设置错误，与<Security_Mode>不匹�?
    CTIOT_ED_ONLY_IDAUTHMOD2_PERMITTED = 961,//设置错误，仅允许IDAuth_Mode=2设置
    CTIOT_ED_MODE_ERROR = 968,                  //存在模式设置错误，功能暂不支持或其他
    CTIOT_ED_LIFETIME_ERROR = 969,              //lifetime取值超�?
    CTIOT_EE_QUEUE_OVERRUN = 970,               //缓存队列超限
    CTIOT_EE_URI_ERROR = 972,                   //uri str错误
    CTIOT_EE_OPERATOR_NOT_SUPPORTED = 303,      //该操作不支持
    CTIOT_EB_OTHER = 1,                         //其它错误
    CTIOT_EB_PARAMETER_NUM_ERROR = 2,           //参数数量错误
    CTIOT_EB_PARAMETER_VALUE_ERROR = 3,         //参数值错�?
    CTIOT_EB_DATA_LENGTH_NOT_EVEN = 17,         //Data字段长度不是偶数
    CTIOT_EB_DATA_LENGTH_OVERRRUN = 14,         //Data字段长度超过上限
    CTIOT_EB_NO_RECV_DATA  = 801,               //*16*
}CTIOT_NB_ERRORS;

typedef enum
{
    QUERY_STATUS_SESSION_NOT_EXIST,               //会话不存�?
    QUERY_STATUS_NOT_LOGIN,                       //会话未登�?
    QUERY_STATUS_LOGINING,                        //会话登录�?
    QUERY_STATUS_LOGIN,                           //会话已登�?
    QUERY_STATUS_SESSION_SUSPEND,                 //会话挂起�?
    QUERY_STATUS_NO_TRANSCHANNEL,                 //传送通道不存�?
    QUERY_STATUS_TRANSCHANNEL_ESTABLISHED,        //传送通道已建�?
    QUERY_STATUS_MSGID_NOT_EXIST,                 //msgid查询不到（已发送结束从缓存中清除或不存在）
    QUERY_STATUS_MSG_IN_CACHE,                    //消息缓存�?
    QUERY_STATUS_MSG_SENDOUT,                     //消息已发�?
    QUERY_STATUS_MSG_DELIVERED,                   //消息已送达
    QUERY_STATUS_PLATFORM_TIMEOUT,                //平台响应超时
    QUERY_STATUS_PLATFORM_RST,                    //平台响应RST
    QUERY_STATUS_CONNECTION_UNAVAILABLE,          //连接不可�?
    QUERY_STATUS_CONNECTION_UNAVAILABLE_TEMPORARY,//连接暂不可用
    QUERY_STATUS_CONNECTION_AVAILABLE,            //连接正常（携带覆盖等级）
    QUERY_STATUS_NETWORK_TRAFFIC,                 //网络拥塞（携带拥塞剩余时长）
    QUERY_STATUS_ENGINE_EXCEPTION_RECOVERING,     //Engine异常，恢复中
    QUERY_STATUS_ENGINE_EXCEPTION_REBOOT,         //Engine异常，需reboot重启
    QUERY_STATUS_FIRMWARE_INDEX                   //固件版本指示
}ctiot_funcv1_query_status_e;                            //状态查询返回连接状�?

typedef struct
{
    uint8_t argc;
    char *args[20];
}object_instance_str_t;
typedef struct
{
    uint16_t objId;
    uint8_t intsanceCount;
    uint16_t intanceId[MAX_INSTANCE_IN_ONE_OBJECT];
}object_instance_array_t;

typedef struct _ctiot_funcv1_data_t
{
    struct _ctiot_funcv1_data_t *next;
    ctiot_funcv1_data_type_e dataType;
    union
    {
        bool        asBoolean;
        int64_t     asInteger;
        double      asFloat;
        struct
        {
            size_t    length;
            uint8_t * buffer;
        } asBuffer;
    }u;
}ctiot_funcv1_data_list;
typedef struct _ctiot_funcv1_thread_status_t
{
    ctiot_funcv1_thread_status_e thread_status;
    bool thread_started;
}ctiot_funcv1_thread_status_t;
typedef struct _ctiot_funcv1_updata_t
{
    struct _ctiot_funcv1_updata_t *next;
    //COAP
    uint16_t  msgid;
    uint8_t   token[8];
    uint8_t   tokenLen;
    uint16_t  responseCode;
    ctiot_funcv1_observe_e observeMode;
    ctiot_funcv1_send_mode_e mode;
    ctiot_funcv1_data_send_status_e status;
    ctiot_funcv1_send_format_e sendFormat;
    ctiot_funcv1_send_type_e sendType;
    //LWM2M
    uint8_t* uri;

    //CLIENT
    ctiot_funcv1_data_list *updata;
}ctiot_funcv1_updata_list;

typedef struct _ctiot_funcv1_downdata_t
{
    struct _ctiot_funcv1_downdata_t *next;
    //COAP
    uint16_t  msgid;
    uint8_t token[8];
    uint8_t tokenLen;

    //LWM2M
    uint8_t*uri;
    ctiot_funcv1_operate_type_e type;
    lwm2m_media_type_t mediaType;

    //CLIENT
    uint64_t recvtime;
}ctiot_funcv1_downdata_list;

typedef struct
{
    //ctiot_funcv1_status_type_e statusType;
    char* baseInfo;
    void* extraInfo;
    uint16_t extraInfoLen;
}ctiot_funcv1_status_t;
typedef struct
{
    ctiot_funcv1_query_status_type_e queryType;
    ctiot_funcv1_query_status_e queryResult;
    union
    {
        uint64_t extraInt;
        struct
        {
            uint8_t* buffer;
            uint16_t bufferLen;
        }extraInfo;
    }u;
}ctiot_funcv1_query_status_t;

typedef struct
{
    uint16_t msgId;
    ctiot_funcv1_cmd_type_e cmdType;
    uint8_t token[8];
    uint16_t tokenLen;
    uint8_t* uri;
    uint8_t observe;
    lwm2m_media_type_t dataFormat;
    uint8_t* data;
    uint16_t dataLen;
}ctiot_funcv1_object_operation_t;
typedef struct
{
    char *                   cChipType;
    char *                   cDeviceIP;
    char                     cApn[50];
    char                     cImsi[20];
    char                     cImei[20];
    uint32_t                 cCellID;
    char                     cSDKVersion[30];//芯片软件版本
    char                     cFirmwareVersion[20];//固件版本
    ctiot_funcv1_terminal_mode_e    cTerminalMode;//终端工作模式
    uint16_t                 cSignalIntensity;//信号强度
    uint16_t                 cSignalToNoiseRatio;//信噪
    //uint32_t                 cTauTimer;
    uint32_t                 cActiveTime;
    uint8_t                  cPSMMode;
    /*拥塞时间*/
    time_t                 cTrafficTime;
    /*网络拥塞标识*/
    bool                     cTrafficFlag;
    /*无线连接*/
    ctiot_funcv1_wireless_status_e  cState;
    ctiot_funcv1_signal_level_e     cSignalLevel;
}ctiot_funcv1_chip_info,*ctiot_funcv1_chip_info_ptr;
typedef struct
{
    lwm2m_object_t *securityObjP;
    lwm2m_object_t *serverObject;
    int sock;
#ifdef WITH_MBEDTLS
    dtls_connection_t * connList;
    lwm2m_context_t * lwm2mH;
#else
    connection_t * connList;
#endif
    int addressFamily;
} ctiot_funcv1_client_data_t;
typedef enum{
    AT_TO_MCU_RECEIVE,
    AT_TO_MCU_STATUS,
    AT_TO_MCU_COMMAND,
    AT_TO_MCU_QUERY_STATUS,
    AT_TO_MCU_SENDSTATUS,
    AT_TO_MCU_SENDERROR,
    AT_TO_MCU_NSMI
}ctiot_funcv1_at_to_mcu_type_e;


typedef struct
{

    /*lwm2m_context*/
    lwm2m_context_t *        lwm2mContext;

    /*****************************CLIENT*****************************/
    /*模组信息*/
    ctiot_funcv1_chip_info_ptr      chipInfo;
    ctiot_funcv1_login_status_e     loginStatus;//登录状态，处理时要注意和lwm2m的state同步
    /*平台参数*/
    char *                   serverIP;
    uint32_t                 port;
    uint32_t                 localPort;
    char                     localIP[40];
    uint32_t                 lifetime;
    char *                   objectInstList;//MCU Objects
    ctiot_funcv1_client_data_t      clientInfo;
    uint16_t                 objectCount;//全部object数目
    lwm2m_object_t**         objArray;//初始化时的object*/
    /*MCU提供认证*/
    char *                   idAuthStr;
    #if 1
    ctiot_funcv1_wp_saving_mode_e   wpSavingMode;
    #endif
    #if 1
    /*加载方式*/
    ctiot_funcv1_boot_flag_e              bootFlag;//临时数据*/
    /*环境数据*/
    ctiot_funcv1_data_state_t             dState;//0x0F-ready
    #endif
    /*平台disable*/
    ctiot_funcv1_plat_disable_e     disableFlag;//ServerObject的disable同步
    /*平台disable时间*/
    uint64_t                 disableTime;//和ServerObject的disabletime同步

    ctiot_funcv1_on_uq_mode_e             onUqMode;
    ctiot_funcv1_on_ce_level2_policy_e    onCeLevel2Policy;
    ctiot_funcv1_auto_tau_timer_update_e  atuoTauTimerUpdate;
    ctiot_funcv1_auto_heartbeat_e         autoHeartBeat;
    ctiot_funcv1_wakeup_notify_e          wakeupNotify;
    ctiot_funcv1_protocol_mode_e           protocolMode;

    /*会话数据*/
    ctiot_funcv1_security_mode_e     securityMode;
    ctiot_funcv1_id_auth_mode_e     idAuthMode;
    char *                   locationPath;
    /*FOTA*/
    uint8_t                  fotaFlag;
    uint8_t                  fotaMode;
    /*DIP*/
    uint8_t                  dipFlag;
    uint8_t                  regFlag;
    uint8_t                  nsmiFlag;
    uint8_t                  nnmiFlag;
    char *                   pskid;
    char *                   psk;
    uint16_t                 pskLen;

    /*上下行list*/
    ctiot_funcv1_msg_list_head *      updataList;
    ctiot_funcv1_msg_list_head *    downdataList;

    /*线程*/
    //ctiot_funcv1_thread_status_t at_thread_status;
    ctiot_funcv1_thread_status_t send_thread_status;
    ctiot_funcv1_thread_status_t recv_thread_status;

    /*con data status*/
    ctiot_funcv1_condata_status_e conDataStatus; //for *16*
    uint8_t                       seqNum;     //for *16*
    /*last recv data*/
    uint8_t                       recvdataLen; //for *16*
    uint8_t *                     recvData;    //for *16*
}ctiot_funcv1_context_t;

typedef void (*ctiot_callback_notify)(CTIOT_NB_ERRORS errInfo,ctiot_funcv1_at_to_mcu_type_e infoType,void* params,uint16_t paramLen);
typedef void(*ctlwm2m_at_handler_t)(char* at_str);
typedef void(*ctlwm2m_event_handler_t)(module_type_t type, INT32 code, const CHAR* arg, INT32 arg_len);
void ctiot_funcv1_register_event_handler(ctlwm2m_event_handler_t callback);
void ctiot_funcv1_notify_event(module_type_t type, int code, const char* arg, int arg_len);
void ctiot_funcv1_deregister_event_handler(void);
void ctiot_funcv1_register_at_handler(ctlwm2m_at_handler_t callback);
void ctiot_funcv1_notify_at(char* msg);
void ctiot_funcv1_deregister_at_handler(void);




ctiot_funcv1_chip_info* ctiot_funcv1_get_chip_instance(void);
ctiot_funcv1_context_t* ctiot_funcv1_get_context(void);
void ctiot_funcv1_notify_nb_info(CTIOT_NB_ERRORS errInfo,ctiot_funcv1_at_to_mcu_type_e infoType,void* params,uint16_t paramLen);
int ctiot_funcv1_location_path_validation(char *location);
void prv_set_uri_option(coap_packet_t* messageP,lwm2m_uri_t* uriP);
uint16_t ctiot_funcv1_set_boot_flag(ctiot_funcv1_context_t* pTContext, uint8_t bootFlag);
uint16_t ctiot_funcv1_add_downdata_to_queue(ctiot_funcv1_context_t* pContext, uint16_t msgid, uint8_t* token,uint8_t tokenLen, uint8_t* uri,ctiot_funcv1_operate_type_e type, lwm2m_media_type_t mediaType );
uint16_t ctiot_funcv1_parse_uristr(char* uriStr, object_instance_array_t objInsArray[], uint32_t arraySize);
int prv_extend_query_len(void);
char* prv_extend_query(int querylen);
void ctiot_funcv1_update_bootflag(ctiot_funcv1_context_t* pContext,int bootFlag);

int resource_value_changed(char* uri);
uint32_t ctiot_getCoapMaxTransmitWaitTime(void);
uint32_t ctiot_getExchangeLifetime(void);
uint8_t ctiot_getCoapAckTimeout(void);
    void ctiot_setCoapAckTimeout(ctiot_funcv1_signal_level_e celevel);



#ifdef __cplusplus
}
#endif
#endif//_CTIOT_LWM2M_SDK_H



