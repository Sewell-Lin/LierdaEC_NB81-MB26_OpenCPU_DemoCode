/******************************************************************************

*(C) Copyright 2018 EIGENCOMM International Ltd.

* All Rights Reserved

******************************************************************************
*  Filename: atec_mqtt.h
*
*  Description:
*
*  History:
*
*  Notes:
*
******************************************************************************/
#ifndef _ATEC_MQTT_H
#define _ATEC_MQTT_H

#include "at_util.h"

#define MQTT_ID_MIN                 0
#define MQTT_ID_MAX                 3
#define MQTT_ID_DEF                 0xff
#define MQTT_TCP_ID_MIN          0
#define MQTT_TCP_ID_MAX          0
#define MQTT_TCP_ID_DEF          0

/* AT+ECMTCFG */
#define MQTTCFG_CFG_MAX_LEN            16
#define MQTTCFG_CFG_STR_DEF             NULL
#define MQTTCFG_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTCFG_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTCFG_TCP_ID_DEF          MQTT_TCP_ID_DEF

#define MQTTCFG_2_ECHO_MIN              0
#define MQTTCFG_2_ECHO_MAX              2
#define MQTTCFG_2_ECHO_DEF              0

#define MQTTCFG_2_TXFORMAT_MIN              0
#define MQTTCFG_2_TXFORMAT_MAX              2
#define MQTTCFG_2_TXFORMAT_DEF              0
#define MQTTCFG_3_RXFORMAT_MIN              0
#define MQTTCFG_3_RXFORMAT_MAX              2
#define MQTTCFG_3_RXFORMAT_DEF              0

#define MQTTCFG_2_KEEPALIVE_MIN              0
#define MQTTCFG_2_KEEPALIVE_MAX              3601
#define MQTTCFG_2_KEEPALIVE_DEF              0

#define MQTTCFG_2_SESSION_MIN              0
#define MQTTCFG_2_SESSION_MAX              2
#define MQTTCFG_2_SESSION_DEF              0

#define MQTTCFG_2_PKT_MIN              1
#define MQTTCFG_2_PKT_MAX              61
#define MQTTCFG_2_PKT_DEF              10
#define MQTTCFG_3_RETRY_MIN              1
#define MQTTCFG_3_RETRY_MAX              11
#define MQTTCFG_3_RETRY_DEF              3
#define MQTTCFG_4_NOTICE_MIN               0
#define MQTTCFG_4_NOTICE_MAX               2
#define MQTTCFG_4_NOTICE_DEF               0

#define MQTTCFG_2_WILLFLAG_MIN              0
#define MQTTCFG_2_WILLFLAG_MAX              2
#define MQTTCFG_2_WILLFLAG_DEF              0
#define MQTTCFG_3_WILLQOS_MIN             0
#define MQTTCFG_3_WILLQOS_MAX             3
#define MQTTCFG_3_WILLQOS_DEF             0
#define MQTTCFG_4_WILLQRETAIN_MIN            0
#define MQTTCFG_4_WILLQRETAIN_MAX            2
#define MQTTCFG_4_WILLQRETAIN_DEF            0
#define MQTTCFG_5_WILLTOPIC_MAX_LEN               256
#define MQTTCFG_5_WILLTOPIC_STR_DEF               NULL
#define MQTTCFG_6_WILLMSG_MAX_LEN               256
#define MQTTCFG_6_WILLMSG_STR_DEF               NULL

#define MQTTCFG_2_VERSION_MIN              3
#define MQTTCFG_2_VERSION_MAX              5
#define MQTTCFG_2_VERSION_DEF              4

#define MQTTCFG_2_PK_MAX_LEN             64
#define MQTTCFG_2_PK_STR_DEF             NULL
#define MQTTCFG_3_DN_MAX_LEN               64
#define MQTTCFG_3_DN_STR_DEF               NULL
#define MQTTCFG_4_DS_MAX_LEN             128
#define MQTTCFG_4_DS_STR_DEF             NULL

#define MQTTCFG_2_CLOUD_MIN              0
#define MQTTCFG_2_CLOUD_MAX              256
#define MQTTCFG_2_CLOUD_DEF              0
#define MQTTCFG_3_PAYLOADTYPE_MIN              0
#define MQTTCFG_3_PAYLOADTYPE_MAX              256
#define MQTTCFG_3_PAYLOADTYPE_DEF              1

/* AT+ECMTOPEN */
#define MQTTOPEN_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTOPEN_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTOPEN_TCP_ID_DEF          MQTT_TCP_ID_DEF
#define MQTTOPEN_1_HOST_MAX_LEN             128
#define MQTTOPEN_1_HOST_STR_DEF             NULL
#define MQTTOPEN_2_PORT_MIN          1
#define MQTTOPEN_2_PORT_MAX          65536
#define MQTTOPEN_2_PORT_DEF          5830

/* AT+ECMTCLOSE */
#define MQTTCLOSE_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTCLOSE_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTCLOSE_TCP_ID_DEF          MQTT_TCP_ID_DEF

/* AT+ECMTCONN*/
#define MQTTCONN_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTCONN_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTCONN_TCP_ID_DEF          MQTT_TCP_ID_DEF
#define MQTTCONN_1_CLIENTID_MAX_LEN             32//256
#define MQTTCONN_1_CLIENTID_STR_DEF             NULL
#define MQTTCONN_2_USERNAME_MAX_LEN           32//256
#define MQTTCONN_2_USERNAME_STR_DEF           NULL
#define MQTTCONN_3_PWD_MAX_LEN             64//256
#define MQTTCONN_3_PWD_STR_DEF             NULL

/* AT+ECMTDISC */
#define MQTTDISC_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTDISC_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTDISC_TCP_ID_DEF          MQTT_TCP_ID_DEF

/* AT+ECMTSUB */
#define MQTTSUB_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTSUB_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTSUB_TCP_ID_DEF          MQTT_TCP_ID_DEF
#define MQTTSUB_1_MSGID_MIN              1
#define MQTTSUB_1_MSGID_MAX              65535
#define MQTTSUB_1_MSGID_DEF              10
#define MQTTSUB_2_TOPIC_MAX_LEN          128
#define MQTTSUB_2_TOPIC_STR_DEF          NULL
#define MQTTSUB_3_QOS_MIN                    0
#define MQTTSUB_3_QOS_MAX                    3
#define MQTTSUB_3_QOS_DEF                    0

/* AT+ECMTUNSUB */
#define MQTTUNSUB_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTUNSUB_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTUNSUB_TCP_ID_DEF          MQTT_TCP_ID_DEF
#define MQTTUNSUB_1_MSGID_MIN              1
#define MQTTUNSUB_1_MSGID_MAX              65535
#define MQTTUNSUB_1_MSGID_DEF              10
#define MQTTUNSUB_2_TOPIC_MAX_LEN          128
#define MQTTUNSUB_2_TOPIC_STR_DEF          NULL

/* AT+ECMTPUB */
#define MQTTPUB_TCP_ID_MIN          MQTT_TCP_ID_MIN
#define MQTTPUB_TCP_ID_MAX          MQTT_TCP_ID_MAX
#define MQTTPUB_TCP_ID_DEF          MQTT_TCP_ID_DEF
#define MQTTPUB_1_MSGID_MIN              0
#define MQTTPUB_1_MSGID_MAX              65535
#define MQTTPUB_1_MSGID_DEF              10
#define MQTTPUB_2_QOS_MIN                    0
#define MQTTPUB_2_QOS_MAX                    2
#define MQTTPUB_2_QOS_DEF                    1
#define MQTTPUB_3_RETRAINED_MIN                  0
#define MQTTPUB_3_RETRAINED_MAX                  1
#define MQTTPUB_3_RETRAINED_DEF                  0
#define MQTTPUB_4_TOPIC_MAX_LEN          128
#define MQTTPUB_4_TOPIC_STR_DEF              NULL
#define MQTTPUB_5_MSG_MAX_LEN                1024
#define MQTTPUB_5_MSG_STR_DEF                    NULL
#define MQTTPUB_6_CLOUD_MIN                  0
#define MQTTPUB_6_CLOUD_MAX                  128
#define MQTTPUB_6_CLOUD_DEF                  0xff
#define MQTTPUB_7_RETRAINED_MIN                  0
#define MQTTPUB_7_RETRAINED_MAX                  128
#define MQTTPUB_7_RETRAINED_DEF                  0xff

#define MQTT_DATA_FORMAT_TXT                    0
#define MQTT_DATA_FORMAT_HEX                    1

typedef struct
{
    UINT32 reqHandle;
    int tcpId;
    int msgId;
    int qos;
    int retained;
    char *mqttTopic;
    
}mqtt_pub_data;

CmsRetId  mqttCFG(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttOPEN(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttCLOSE(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttCONN(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttDISC(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttSUB(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttUNS(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttPUB(const AtCmdInputContext *AtCmdReqParaPtr);
CmsRetId  mqttPUBInputData(UINT8 chanId, UINT8 *pData, INT16 dataLength);
CmsRetId  mqttPUBCancel(void);

CmsRetId mqttOPENind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);
CmsRetId mqttCLOSEind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);
CmsRetId mqttCONNind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);
CmsRetId mqttDISCind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);
CmsRetId mqttSUBind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);
CmsRetId mqttUNSind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);
CmsRetId mqttPUBind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);

CmsRetId  mqttSTATind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);
CmsRetId  mqttRECVind(UINT16 primId, UINT16 reqHandle, UINT16 rc, void *paras);


#endif


