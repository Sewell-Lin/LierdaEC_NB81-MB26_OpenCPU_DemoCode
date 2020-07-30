/******************************************************************************
 * (C) Copyright 2018 EIGENCOMM International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: atec_tcpip.h
 *
 *  Description:
 *
 *  History:
 *
 *  Notes:
 *
******************************************************************************/
#ifndef _ATEC_TCPIP_H
#define _ATEC_TCPIP_H

#include "at_util.h"

/*AT+ECSNTP*/
#define SNTP_0_STR_MAX_LEN              MAX_URL_IPADDR_LEN
#define SNTP_0_STR_DEF                  NULL
#define SNTP_DEC_1_MIN                  0
#define SNTP_DEC_1_MAX                  AT_SOC_PORT_MAX
#define SNTP_DEC_1_DEF                  0
#define SNTP_DEC_2_MIN                  0
#define SNTP_DEC_2_MAX                  1
#define SNTP_DEC_2_DEF                  0

/* AT+ECPING */
#define PING_DEC_0_MIN                  0
#define PING_DEC_0_MAX                  0
#define PING_DEC_0_DEF                  0
#define PING_0_STR_MAX_LEN              MAX_URL_IPADDR_LEN
#define PING_0_STR_DEF                  NULL
#define PING_1_COUNT_MIN                1
#define PING_1_COUNT_MAX                255
#define PING_1_COUNT_DEF                4
#define PING_2_PAYLOAD_MIN           1
#define PING_2_PAYLOAD_MAX           1500
#define PING_2_PAYLOAD_DEF           32
#define PING_3_TIMEOUT_MIN              1
#define PING_3_TIMEOUT_MAX              10*60*1000
#define PING_3_TIMEOUT_DEF              20000

/* AT+CMDNS */
#define CMDNS_0_STR_MAX_LEN              MAX_URL_IPADDR_LEN
#define CMDNS_0_STR_DEF                  NULL

/* AT+ECIPERF */
#define ECIPERF_0_ACT_MIN                 0
#define ECIPERF_0_ACT_MAX                 5
#define ECIPERF_0_ACT_DEF                 0

#define ECIPERF_1_PROTO_MIN               0   //UDP
#define ECIPERF_1_PROTO_MAX               1   //TCP
#define ECIPERF_1_PROTO_DEF               0   //UDP

#define ECIPERF_2_PORT_MIN                AT_SOC_PORT_MIN
#define ECIPERF_2_PORT_MAX                AT_SOC_PORT_MAX
#define ECIPERF_2_PORT_DEF                5001

#define ECIPERF_3_STR_MAX_LEN              64
#define ECIPERF_3_STR_DEF                  NULL

#define ECIPERF_4_TPT_MIN                 1
#define ECIPERF_4_TPT_MAX                 250000  //250kbps
#define ECIPERF_4_TPT_DEF                 20000   //20kbps

#define ECIPERF_5_PAYLOAD_MIN             1
#define ECIPERF_5_PAYLOAD_MAX             1472
#define ECIPERF_5_PAYLOAD_DEF             1350

#define ECIPERF_6_PKG_NUM_MIN             1
#define ECIPERF_6_PKG_NUM_MAX             65000
#define ECIPERF_6_PKG_NUM_DEF             100

#define ECIPERF_7_DURATION_MIN            1
#define ECIPERF_7_DURATION_MAX            65000
#define ECIPERF_7_DURATION_DEF            65000

#define ECIPERF_8_RPT_INTERVAL_MIN        1
#define ECIPERF_8_RPT_INTERVAL_MAX        65000
#define ECIPERF_8_RPT_INTERVAL_DEF        10

/* AT+SKTCREATE */
#define SKTCREATE_0_MIN                   1
#define SKTCREATE_0_MAX                   2
#define SKTCREATE_0_DEF                   1
#define SKTCREATE_1_MIN                1
#define SKTCREATE_1_MAX                3
#define SKTCREATE_1_DEF                1
#define SKTCREATE_2_MIN                   0
#define SKTCREATE_2_MAX                   0xff
#define SKTCREATE_2_DEF                   0

/* AT+SKTSEND */
#define SKTSEND_0_MIN                   AT_SOC_FD_MIN
#define SKTSEND_0_MAX                   AT_SOC_FD_MAX
#define SKTSEND_0_DEF                   0
#define SKTSEND_1_MIN                1
#define SKTSEND_1_MAX                SUPPORT_MAX_SOCKET_RAW_DATA_LENGTH
#define SKTSEND_1_DEF                1
#define SKTSEND_2_STR_MAX_LEN           6
#define SKTSEND_2_STR_DEF               NULL
#define SKTSEND_3_MIN                0
#define SKTSEND_3_MAX                2
#define SKTSEND_3_DEF                0
#define SKTSEND_4_MIN                0
#define SKTSEND_4_MAX                1
#define SKTSEND_4_DEF                0


/* AT+SKTCONNECT */
#define SKTCONNECT_0_SEQ_MIN                AT_SOC_FD_MIN
#define SKTCONNECT_0_SEQ_MAX                AT_SOC_FD_MAX//max socket fd
#define SKTCONNECT_0_SEQ_DEF                0
#define SKTCONNECT_1_ADDR_STR_MAX_LEN       AT_SOC_IP_ADDR_STRING_LENGTH_MAX
#define SKTCONNECT_1_ADDR_STR_DEF           NULL
#define SKTCONNECT_2_PORT_MIN               AT_SOC_PORT_MIN
#define SKTCONNECT_2_PORT_MAX               AT_SOC_PORT_MAX
#define SKTCONNECT_2_PORT_DEF               0

/* AT+SKTBIND */
#define SKTBIND_0_SEQ_MIN                   AT_SOC_FD_MIN
#define SKTBIND_0_SEQ_MAX                   AT_SOC_FD_MAX//max socket fd
#define SKTBIND_0_SEQ_DEF                   0
#define SKTBIND_1_ADDR_STR_MAX_LEN             AT_SOC_IP_ADDR_STRING_LENGTH_MAX
#define SKTBIND_1_ADDR_STR_DEF                 NULL
#define SKTBIND_2_PORT_MIN                  0
#define SKTBIND_2_PORT_MAX                  AT_SOC_PORT_MAX
#define SKTBIND_2_PORT_DEF                  0

/* AT+SKTSTATUS */
#define SKTSTATUS_0_SEQ_MIN                   AT_SOC_FD_MIN
#define SKTSTATUS_0_SEQ_MAX                   AT_SOC_FD_MAX//max socket fd
#define SKTSTATUS_0_SEQ_DEF                   0

/* AT+SKTDELETE */
#define SKTDELETE_0_SEQ_MIN                   AT_SOC_FD_MIN
#define SKTDELETE_0_SEQ_MAX                   AT_SOC_FD_MAX//max socket fd
#define SKTDELETE_0_SEQ_DEF                   0

#define MAX_URL_IPADDR_LEN                    255

/* AT+ECDNSCFG */
#define ECDNSCFG_DNS_NUM                      4

#define ECDNSCFG_DNS_STR_MAX_LEN              64
#define ECDNSCFG_DNS_STR_DEF                  PNULL
#define ATEC_ECDNSCFG_GET_CNF_STR_LEN        256
#define ATEC_ECDNSCFG_GET_CNF_TMP_STR_LEN    50

/* AT+ECSOCR*/
#define ECSOCR_0_TYPE_STR_MAX_LEN              6
#define ECSOCR_0_TYPE_STR_DEF                  NULL
#define ECSOCR_1_PROTOCOL_MIN                  6
#define ECSOCR_1_PROTOCOL_MAX                  17
#define ECSOCR_1_PROTOCOL_DEF                  17
#define ECSOCR_2_LISTEN_PORT_MIN               0
#define ECSOCR_2_LISTEN_PORT_MAX               AT_SOC_PORT_MAX
#define ECSOCR_2_LISTEN_PORT_DEF               0
#define ECSOCR_3_RECEIVE_CONTROL_MIN           0
#define ECSOCR_3_RECEIVE_CONTROL_MAX           1
#define ECSOCR_3_RECEIVE_CONTROL_DEF           1
#define ECSOCR_4_AF_TYPE_STR_MAX_LEN           8
#define ECSOCR_4_AF_TYPE_STR_DEF               NULL
#define ECSOCR_5_IP_ADDR_STR_MAX_LEN           AT_SOC_IP_ADDR_STRING_LENGTH_MAX
#define ECSOCR_5_IP_ADDR_STR_DEF               NULL

/*AT+ECSOST*/
#define ECSOST_0_SOCKET_ID_MIN                 AT_SOC_FD_MIN
#define ECSOST_0_SOCKET_ID_MAX                 AT_SOC_FD_MAX
#define ECSOST_0_SOCKET_ID_DEF                 AT_SOC_FD_DEF
#define ECSOST_1_IP_ADDR_STR_MAX_LEN           AT_SOC_IP_ADDR_STRING_LENGTH_MAX
#define ECSOST_1_IP_ADDR_STR_DEF               NULL
#define ECSOST_2_REMOTE_PORT_MIN               AT_SOC_PORT_MIN
#define ECSOST_2_REMOTE_PORT_MAX               AT_SOC_PORT_MAX
#define ECSOST_2_REMOTE_PORT_DEF               0
#define ECSOST_3_LENGTH_MIN                    AT_SOC_UL_LENGTH_MIN
#define ECSOST_3_LENGTH_MAX                    AT_SOC_UL_LENGTH_MAX
#define ECSOST_3_LENGTH_DEF                    0
#define ECSOST_4_DATA_MAX_LEN                  AT_SOC_UL_LENGTH_MAX
#define ECSOST_4_DATA_DEF                      NULL
#define ECSOST_5_SEQUENCE_MIN                  AT_SOC_UL_DATA_SEQUENCE_MIN
#define ECSOST_5_SEQUENCE_MAX                  AT_SOC_UL_DATA_SEQUENCE_MAX
#define ECSOST_5_SEQUENCE_DEF                  0
#define ECSOST_6_SEGMENT_ID_MIN                AT_SOC_UL_SEGMENT_ID_MIN
#define ECSOST_6_SEGMENT_ID_MAX                AT_SOC_UL_SEGMENT_ID_MAX
#define ECSOST_6_SEGMENT_ID_DEF                0
#define ECSOST_7_SEGMENT_NUM_MIN               AT_SOC_UL_SEGMENT_NUM_MIN
#define ECSOST_7_SEGMENT_NUM_MAX               AT_SOC_UL_SEGMENT_NUM_MAX
#define ECSOST_7_SEGMENT_NUM_DEF               0

/*AT+ECSOSTF*/
#define ECSOSTF_0_SOCKET_ID_MIN                 AT_SOC_FD_MIN
#define ECSOSTF_0_SOCKET_ID_MAX                 AT_SOC_FD_MAX
#define ECSOSTF_0_SOCKET_ID_DEF                 AT_SOC_FD_DEF
#define ECSOSTF_1_IP_ADDR_STR_MAX_LEN           AT_SOC_IP_ADDR_STRING_LENGTH_MAX
#define ECSOSTF_1_IP_ADDR_STR_DEF               NULL
#define ECSOSTF_2_REMOTE_PORT_MIN               AT_SOC_PORT_MIN
#define ECSOSTF_2_REMOTE_PORT_MAX               AT_SOC_PORT_MAX
#define ECSOSTF_2_REMOTE_PORT_DEF               0
#define ECSOSTF_3_FLAG_STR_MAX_LEN              5
#define ECSOSTF_3_FLAG_STR_DEF                  NULL
#define ECSOSTF_4_LENGTH_MIN                    AT_SOC_UL_LENGTH_MIN
#define ECSOSTF_4_LENGTH_MAX                    AT_SOC_UL_LENGTH_MAX
#define ECSOSTF_4_LENGTH_DEF                    0
#define ECSOSTF_5_DATA_MAX_LEN                  AT_SOC_UL_LENGTH_MAX
#define ECSOSTF_5_DATA_DEF                      NULL
#define ECSOSTF_6_SEQUENCE_MIN                  AT_SOC_UL_DATA_SEQUENCE_MIN
#define ECSOSTF_6_SEQUENCE_MAX                  AT_SOC_UL_DATA_SEQUENCE_MAX
#define ECSOSTF_6_SEQUENCE_DEF                  0
#define ECSOSTF_7_SEGMENT_ID_MIN                AT_SOC_UL_SEGMENT_ID_MIN
#define ECSOSTF_7_SEGMENT_ID_MAX                AT_SOC_UL_SEGMENT_ID_MAX
#define ECSOSTF_7_SEGMENT_ID_DEF                0
#define ECSOSTF_8_SEGMENT_NUM_MIN               AT_SOC_UL_SEGMENT_NUM_MIN
#define ECSOSTF_8_SEGMENT_NUM_MAX               AT_SOC_UL_SEGMENT_NUM_MAX
#define ECSOSTF_8_SEGMENT_NUM_DEF               0

/*AT+ECQSOS*/
#define ECQSOS_0_SOCKET1_ID_MIN                 AT_SOC_FD_MIN
#define ECQSOS_0_SOCKET1_ID_MAX                 AT_SOC_FD_MAX
#define ECQSOS_0_SOCKET1_ID_DEF                 AT_SOC_FD_DEF
#define ECQSOS_1_SOCKET2_ID_MIN                 AT_SOC_FD_MIN
#define ECQSOS_1_SOCKET2_ID_MAX                 AT_SOC_FD_MAX
#define ECQSOS_1_SOCKET2_ID_DEF                 AT_SOC_FD_DEF
#define ECQSOS_2_SOCKET3_ID_MIN                 AT_SOC_FD_MIN
#define ECQSOS_2_SOCKET3_ID_MAX                 AT_SOC_FD_MAX
#define ECQSOS_2_SOCKET3_ID_DEF                 AT_SOC_FD_DEF
#define ECQSOS_3_SOCKET4_ID_MIN                 AT_SOC_FD_MIN
#define ECQSOS_3_SOCKET4_ID_MAX                 AT_SOC_FD_MAX
#define ECQSOS_3_SOCKET4_ID_DEF                 AT_SOC_FD_DEF
#define ECQSOS_4_SOCKET5_ID_MIN                 AT_SOC_FD_MIN
#define ECQSOS_4_SOCKET5_ID_MAX                 AT_SOC_FD_MAX
#define ECQSOS_4_SOCKET5_ID_DEF                 AT_SOC_FD_DEF

/*AT+ECSORF*/
#define ECSORF_0_SOCKET_ID_MIN                 AT_SOC_FD_MIN
#define ECSORF_0_SOCKET_ID_MAX                 AT_SOC_FD_MAX
#define ECSORF_0_SOCKET_ID_DEF                 AT_SOC_FD_DEF
#define ECSORF_1_LENGTH_ID_MIN                 AT_SOC_DL_LENGTH_MIN
#define ECSORF_1_LENGTH_ID_MAX                 AT_SOC_DL_LENGTH_MAX
#define ECSORF_1_LENGTH_ID_DEF                 0

/*AT+ECSOCO*/
#define ECSOCO_0_SOCKET_ID_MIN                 AT_SOC_FD_MIN
#define ECSOCO_0_SOCKET_ID_MAX                 AT_SOC_FD_MAX
#define ECSOCO_0_SOCKET_ID_DEF                 AT_SOC_FD_DEF
#define ECSOCO_1_IP_ADDR_STR_MAX_LEN           AT_SOC_IP_ADDR_STRING_LENGTH_MAX
#define ECSOCO_1_IP_ADDR_STR_DEF               NULL
#define ECSOCO_2_REMOTE_PORT_MIN               AT_SOC_PORT_MIN
#define ECSOCO_2_REMOTE_PORT_MAX               AT_SOC_PORT_MAX
#define ECSOCO_2_REMOTE_PORT_DEF               0

/*AT+ECSOSD*/
#define ECSOSD_0_SOCKET_ID_MIN                 AT_SOC_FD_MIN
#define ECSOSD_0_SOCKET_ID_MAX                 AT_SOC_FD_MAX
#define ECSOSD_0_SOCKET_ID_DEF                 AT_SOC_FD_DEF
#define ECSOSD_1_LENGTH_MIN                    AT_SOC_UL_LENGTH_MIN
#define ECSOSD_1_LENGTH_MAX                    AT_SOC_UL_LENGTH_MAX
#define ECSOSD_1_LENGTH_DEF                    0
#define ECSOSD_2_DATA_MAX_LEN                  AT_SOC_UL_LENGTH_MAX
#define ECSOSD_2_DATA_DEF                      NULL
#define ECSOSD_3_FLAG_STR_MAX_LEN              5
#define ECSOSD_3_FLAG_STR_DEF                  NULL
#define ECSOSD_3_FLAG_DEF                      0
#define ECSOSD_4_SEQUENCE_MIN                  AT_SOC_UL_DATA_SEQUENCE_MIN
#define ECSOSD_4_SEQUENCE_MAX                  AT_SOC_UL_DATA_SEQUENCE_MAX
#define ECSOSD_4_SEQUENCE_DEF                  0

/*AT+ECSOCL*/
#define ECSOCL_0_SOCKET_ID_MIN                 AT_SOC_FD_MIN
#define ECSOCL_0_SOCKET_ID_MAX                 AT_SOC_FD_MAX
#define ECSOCL_0_SOCKET_ID_DEF                 AT_SOC_FD_DEF

/*AT+ECSONMI*/
#define ECSONMI_0_MODE_MIN                 AT_SOC_NOTIFY_MODE_MIN
#define ECSONMI_0_MODE_MAX                 AT_SOC_NOTIFY_MODE_MAX
#define ECSONMI_0_MODE_DEF                 AT_SOC_NOTIFY_MODE_IGNORE
#define ECSONMI_1_DL_BUFFER_MAX            AT_SOC_PUBLIC_DL_BUFFER_MAX
#define ECSONMI_1_DL_BUFFER_MIN            AT_SOC_PUBLIC_DL_BUFFER_MIN
#define ECSONMI_1_DL_BUFFER_DEF            AT_SOC_PUBLIC_DL_BUFFER_IGNORE
#define ECSONMI_2_DL_PKG_NUM_MAX           AT_SOC_PUBLIC_DL_PKG_NUM_MAX
#define ECSONMI_2_DL_PKG_NUM_MIN           AT_SOC_PUBLIC_DL_PKG_NUM_MIN
#define ECSONMI_2_DL_PKG_NUM_DEF           AT_SOC_PUBLIC_DL_PKG_NUM_IGNORE

/*AT+ECSONMIE*/
#define ECSONMIE_0_SOCKET_ID_MIN            AT_SOC_FD_MIN
#define ECSONMIE_0_SOCKET_ID_MAX            AT_SOC_FD_MAX
#define ECSONMIE_0_SOCKET_ID_DEF            AT_SOC_FD_DEF
#define ECSONMIE_1_MODE_MIN                 AT_SOC_NOTIFY_MODE_MIN
#define ECSONMIE_1_MODE_MAX                 AT_SOC_NOTIFY_MODE_PRIVATE_DISABLE
#define ECSONMIE_1_MODE_DEF                 AT_SOC_NOTIFY_MODE_IGNORE
#define ECSONMIE_2_DL_BUFFER_MAX            AT_SOC_PRIVATE_DL_BUFFER_MAX
#define ECSONMIE_2_DL_BUFFER_MIN            AT_SOC_PRIVATE_DL_BUFFER_MIN
#define ECSONMIE_2_DL_BUFFER_DEF            AT_SOC_PRIVATE_DL_BUFFER_IGNORE
#define ECSONMIE_3_DL_PKG_NUM_MAX           AT_SOC_PRIVATE_DL_PKG_NUM_MAX
#define ECSONMIE_3_DL_PKG_NUM_MIN           AT_SOC_PRIVATE_DL_PKG_NUM_MIN
#define ECSONMIE_3_DL_PKG_NUM_DEF           AT_SOC_PRIVATE_DL_PKG_NUM_IGNORE

CmsRetId  nmSNTP(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmPING(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECDNS(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECIPERF(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmSKTCREATE(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmSKTSEND(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmSKTSTATUS(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmSKTCONNECT(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmSKTBIND(const AtCmdInputContext *pAtCmdReq);

CmsRetId  nmECSOCR(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSOST(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSOSTF(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECQSOS(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSORF(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSOCO(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSOSD(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSOCL(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSONMI(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECSONMIE(const AtCmdInputContext *pAtCmdReq);

CmsRetId  nmSKTDELETE(const AtCmdInputContext *pAtCmdReq);
CmsRetId  nmECDNSCFG(const AtCmdInputContext *pAtCmdReq);

#endif

