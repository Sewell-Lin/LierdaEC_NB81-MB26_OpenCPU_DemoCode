/******************************************************************************

*(C) Copyright 2018 EIGENCOMM International Ltd.

* All Rights Reserved

******************************************************************************
*  Filename: at_onenet_task.h
*
*  Description: Process onenet related AT commands
*
*  History:
*
*  Notes:
*
******************************************************************************/
#ifndef _AT_ONENET_TASK_H
#define _AT_ONENET_TASK_H

#include "at_util.h"
#include "commontypedef.h"
#include "cis_def.h"
#include "cms_util.h"
#include "cis_api.h"
#include "cis_if_sys.h"
#include "ps_event_callback.h"

#define CIS_NVM_FILE_NAME      "cisconfig.nvm"
#define CIS_NVM_FILE_VERSION   0

#define CIS_ERRID_PARAMETER_ERROR         (601)
#define CIS_ERRID_STATUS_ERROR            (602)
#define CIS_ERRID_UNKNOWN_ERROR           (100)

#define CIS_ERRID_OK                      (650)

#define CIS_ERRID_NOT_SUPPORT             (CIS_ERRID_OK + 1)
#define CIS_ERRID_SDK_ERROR               (CIS_ERRID_OK + 2)
#define CIS_ERRID_NO_INSTANCE             (CIS_ERRID_OK + 3)
#define CIS_ERRID_MALLOC_FAIL             (CIS_ERRID_OK + 4)
#define CIS_ERRID_NO_NETWORK              (CIS_ERRID_OK + 5)
#define CIS_ERRID_CONFIG_FAIL             (CIS_ERRID_OK + 6)
#define CIS_ERRID_CONFLICT_FAIL           (CIS_ERRID_OK + 7)// add for SIM OTA
#define CIS_ERRID_TASK_ERR                (CIS_ERRID_OK + 8)// add for AT handle

#define ONENET_ATTR_NUM         (100)
#define ONENET_AT_RESPONSE_DATA_LEN     (100)

#define ONENET_CMD_READRESP           (8)
#define ONENET_CMD_WRITERESP          (9)
#define ONENET_CMD_EXECUTERESP        (10)
#define ONENET_CMD_OBSERVERESP        (11)
#define ONENET_CMD_DISCOVERRESP       (12)
#define ONENET_CMD_PARAMRESP          (13)

#define MTU_SIZE   (1280)

#define ONENET_INSTANCE_NUM          (1)
#define ONENET_CONFIG_MAX_BUFFER_LEN (100)
#define ONENET_CONFIG_BUFFER_DTLS         "130053F10003F20045050011C00005434D494F540000000000123138332E3233302E34302E33393A35363834001D41757468436F64653A45433631363B50534B3A454947454E434F4D4D3BF30008E400C80000" //with DTLS userdata(AuthCode:EC616;PSK:EIGENCOMM;) 83
#define ONENET_CONFIG_BUFFER         "130045F10003F20037050011000005434D494F540000000000123138332E3233302E34302E34303A35363833000F41757468436F64653A3B50534B3A3BF30008E400C80000"
#define ONENET_CONFIG_BUFFER_BS      "130045F10003F20037050011800005434D494F540000000000123138332E3233302E34302E33393A35363833000F41757468436F64653A3B50534B3A3BF30008E400C80000"
#define ONENET_MAX_OBJECT_COUNT      (2)
#define ONENET_MAX_OBJECT_INSTANCE_COUNT (8)
#define ONENET_HOST_NAME_LEN         (16)

#define ONENET_FLAG_LAST             (0)

#define ONENET_MAIN_TASK_STACK_SIZE   1024*3

//AT HANDLE 
#define ONENET_ATHDL_TASK_STACK_SIZE   2048
#define ONENET_MSG_TIMEOUT 500

typedef enum 
{
    MSG_ONENET_NOTIFY,
    MSG_ONENET_OPEN,
    MSG_ONENET_CLOSE, 
    MSG_ONENET_UPDATE, 
}ONENET_MSG_CMD;

enum ONENET_TASK_STATUS
{
    ONENET_TASK_STAT_NONE, 
    ONENET_TASK_STAT_CREATE
};
//AT HANDLE

/*
 * APPL SGID: APPL_Onenet, related PRIM ID
*/
typedef enum applOnenetPrimId_Enum
{
    APPL_ONENET_PRIM_ID_BASE = 0,
    APPL_ONENET_OPEN_CNF,
    APPL_ONENET_NOTIFY_CNF,
    APPL_ONENET_CLOSE_CNF,
    APPL_ONENET_UPDATE_CNF,
    APPL_ONENET_IND,
    APPL_ONENET_PRIM_ID_END = 0xFF
}applOnenetPrimId;

typedef enum {
    ONENET_OP_RESULT_205_CONTENT = 1,
    ONENET_OP_RESULT_204_CHANGED = 2,
    ONENET_OP_RESULT_400_BAD_REQUEST = 11,
    ONENET_OP_RESULT_401_UNAUTHORIZED = 12,
    ONENET_OP_RESULT_404_NOT_FOUND = 13,
    ONENET_OP_RESULT_405_METHOD_NOT_ALLOWED = 14,
    ONENET_OP_RESULT_406_NOT_ACCEPTABLE = 15
} onenet_at_result_t;

typedef enum {
    TASK_STATUS_INIT = 0,
    TASK_STATUS_OPEN,
    TASK_STATUS_CLOSE
} onenetTaskStatus;

typedef enum
{
    SYSTEM_FREE,
    SYSTEM_BUSY
}onenet_sleep_status_e;

//AT HANDLE
typedef struct
{
    UINT32 msgid;
    UINT32 objectid;
    UINT32 instanceid;
    UINT32 resourceid;
    UINT32 valuetype;
    UINT32 len;
    UINT8 *value;
    UINT32 ackid;
    cis_coapret_t result;
    UINT8 raiflag;
}onenetResuourcCmd;

typedef struct
{
    UINT32 msgid;
    cis_coapret_t result;
    UINT8 raiflag;
}onenetRspCmd;

typedef struct
{
    UINT32 lifetime;
    BOOL withObjectFlag;
    UINT8 raiflag;
}onenetUpdateCmd;

typedef struct
{
    INT32 cmd_type;
    UINT16 reqhandle;
    UINT32 onenetId;
    INT32 lifetime;
    INT32 timeout;
    UINT8 oflag;
    UINT8 raiflag;
    void* cmd;
}ONENET_ATCMD_Q_MSG;

typedef struct
{
    int ret;
}onenet_cnf_msg;
//AT HANDLE

typedef struct {
    BOOL bUsed;
    cis_oid_t objectId;
    cis_instcount_t instCount;
    UINT8 instBitmap[(ONENET_MAX_OBJECT_INSTANCE_COUNT + 7) / 8];
    cis_attrcount_t attrCount;
    cis_actcount_t actCount;
} onenetObjectInfo;

typedef struct {
    BOOL bUsed;
    BOOL bConnected;
    BOOL bConfiged;
    BOOL bRestoreFlag;
    BOOL noNeedStart;
    UINT32 onenetId;
    void *cis_context;
    cis_time_t lifeTime;
    cis_time_t timeout;
    UINT8 configBuf[ONENET_CONFIG_MAX_BUFFER_LEN];
    UINT16 configLen;
    onenetObjectInfo objectInfo[ONENET_MAX_OBJECT_COUNT];
    osTimerId_t timerHandle;
    BOOL timerEnable;
    UINT8 host[ONENET_HOST_NAME_LEN];
} onenetContext;

typedef struct {
    BOOL bUsed;
    BOOL bConnected;
    BOOL bConfiged;
    BOOL bRestoreFlag;
    UINT32 onenetId;
    cis_time_t lifeTime;
    onenetObjectInfo objectInfo[ONENET_MAX_OBJECT_COUNT];
    uint8_t observeObjNum;
    observed_backup_t gObservedBackup[MAX_OBSERVED_COUNT];
    UINT16 configLen;
    UINT8 configBuf[ONENET_CONFIG_MAX_BUFFER_LEN];
    UINT8 host[ONENET_HOST_NAME_LEN];
    UINT8  otaFinishState;
} onenetRetentionContext;

typedef struct OnenetSIMOTAContext_Tag
{
    BOOL                bSimOtaStart;
    UINT8               otaFinishState;
    UINT8               otaAtReturnCode;
    UINT32              timeoutValue;
    UINT16              configLen;
    UINT8               configBuf[ONENET_CONFIG_MAX_BUFFER_LEN];
}OnenetSIMOTAContext;

typedef struct cisNvmHeader_Tag
{
    UINT16 fileBodySize; //file body size, not include size of header;
    UINT8  version;
    UINT8  checkSum;
}cisNvmHeader;

//AT HANDLE
CmsRetId onenet_client_open(UINT32 reqHandle, UINT32 id, INT32 lifetime, INT32 timeout);
CmsRetId onenet_client_close(UINT32 reqHandle, UINT32 id);
CmsRetId onenet_client_update(UINT32 reqHandle, UINT32 id, INT32 lifetime, UINT8 oflag, UINT8 raiflag);
CmsRetId onenet_client_notify(UINT32 reqHandle, UINT32 id, void* cmd);
CmsRetId onenet_client_update(UINT32 reqHandle, UINT32 id, INT32 lifetime, UINT8 oflag, UINT8 raiflag);
INT32 onenet_athandle_create(void);
//AT HANDLE

UINT16 check_network_ready(UINT8 waitTime);

void onenetSaveFlash(void);
INT8 onenetRestoreContext(void);
void onenetClearFlash(void);

void onenetSleepVote(onenet_sleep_status_e bSleep);

onenetContext *onenetCreateInstance(void);
onenetContext *onenetSearchInstance(UINT32 onenetId);
onenetContext *onenetSearchCisContext(void *cis_context);
onenetContext *onenetSearchCisInstance(UINT32 onenetId);

UINT32 onenetHexToBin(UINT8 *dest, UINT8 *source, UINT32 max_dest_len);
void onenetDeleteInstance(onenetContext *onenet);

INT32 onenetConfig(BOOL bsMode, CHAR* ip, CHAR* port);
INT32 onenetDelete(UINT32 onenetId);
INT32 onenetAddObj(UINT32 onenet_id, UINT32 objectid, UINT32 instancecount, UINT8 *instancebitmap, UINT32 attributecount, UINT32 actioncount);
INT32 onenetDelObj(UINT32 onenet_id, UINT32 objectid);
BOOL onenetResult2Coapret(UINT32 cmdid, onenet_at_result_t result, cis_coapret_t *coapret);
INT32 onenetResponse(UINT32 onenet_id, UINT32 msgid, const cis_uri_t *uri, const cis_data_t *cis_data, cis_coapret_t result, UINT8 raiflag);
UINT32 onenetParseAttr(const char *param_string, const char *field_buffer, const char *field_key[], char *field_list[], UINT32 field_max_num, const char *delim);
INT32 onenetReadResp(UINT32 onenet_id, UINT32 msgid, UINT32 objectid, UINT32 instanceid, UINT32 resourceid, UINT32 valuetype, UINT32 len, UINT8 *value, cis_coapret_t result, UINT8 raiflag);
UINT32 onenetBinToHex(char *dest, const UINT8 *source, UINT32 max_dest_len);
BOOL getOnenetCfg(UINT8* buf, UINT16 bufLen, INT32* bsMode, CHAR* ip, CHAR* port);

void onenetSimOtaTaskEntry(void *arg);
BOOL atCheckForNumericOnlyChars(const UINT8 *password);

#endif

