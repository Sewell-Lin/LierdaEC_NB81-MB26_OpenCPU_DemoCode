/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of EigenComm Ltd.
 * File name:    ps_lib_api.h
 * Description:  EC616 opencpu pslibapi header file
 * History:      Rev1.0   2018-12-10
 *
 ****************************************************************************/

#ifndef __PS_LIB_API_H__
#define __PS_LIB_API_H__
#include "task.h"
#include "cmsis_os2.h"
#include "cms_util.h"
#include "netmgr.h"

/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/
#define NV9_DATA_LEN               96       /*not suitable to put here, -TBD*/
#define NV9_DATA_IMEI_LEN          32
#define NV9_DATA_SN_LEN            32
#define NV9_DATA_IMEI_LOCK_LEN     16
#define NV9_DATA_SN_LOCK_LEN       16

#define NV9_DATA_IMEI_OFFSET          0
#define NV9_DATA_SN_OFFSET            32
#define NV9_DATA_IMEI_LOCK_OFFSET     64
#define NV9_DATA_SN_LOCK_OFFSET       72



/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/



/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/*
 * APP request PS service
*/
typedef struct AppPsCmiReqData_Tag
{
    /* request input */
    UINT8   sgId;       //PS service group ID: CacSgIdEnum
    UINT8   rsvd0;

    UINT16  reqPrimId;  //request prim ID.
    UINT16  cnfPrimId;

    UINT16  reqParamLen;
    void    *pReqParam;

    /* confirm output */
    UINT16  cnfRc;      //confirm return code: MtErrorResultCode/SmsErrorResultCode
    UINT16  cnfBufLen;
    void    *pCnfBuf;   //filled in callback API
}AppPsCmiReqData;   //20 bytes



struct imsiApiMsg {
  CHAR *imsi;
  UINT8 len;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct iccidApiMsg {
  CHAR *iccid;
  UINT8 len;
  osSemaphoreId_t *sem;
  UINT16 result;
};


struct cgcontrdpApiMsg {
  UINT8 *cid;
  UINT8 *len;
  UINT8 index;
  UINT8 *APN;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct celevelApiMsg {
  UINT8 act;
  UINT8 celevel;
  UINT8 cc;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct signalApiMsg {
  INT8 *snr;
  INT8 *rsrp;
  UINT8 *csq;
  osSemaphoreId_t *sem;
  UINT16 result;
};



struct psmApiMsg {
  UINT8 *psmMode;
  UINT32 *tauTimeS;
  UINT32 *activeTimeS;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct edrxApiMsg {
  UINT8 *actType;
  UINT32 *edrxValueMs;
  union {
    UINT32 *nwPtwMs;
    UINT8 *modeVal;
  } share;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct ceregApiMsg {
  UINT8 *state;
  UINT16 *tac;
  UINT32 *cellId;
  UINT32 *tauTimeS;
  UINT32 *activeTimeS;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct extCfgApiMsg {
  UINT8 powerlevel;
  UINT8 powerCfun;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct cfunApiMsg {
  UINT8 fun;
  UINT8 rst;
  osSemaphoreId_t *sem;
  UINT16 result;
};


struct powerStateApiMsg {
  UINT8 powerState;
  UINT16 result;
};

struct cchoApiMsg {
  UINT8 *dfName;
  UINT8 *sessionID;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct cchcApiMsg {
  UINT8 sessionID;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct cglaApiMsg {
  UINT8 sessionID;
  UINT8 *command;
  UINT8 cmdLen;
  UINT8 *response;
  UINT8 *respLen;
  osSemaphoreId_t *sem;
  UINT16 result;
};

#define SIM_FILE_PATH_MAX_LEN 8
#define SIM_APDU_DATA_MAX_LEN 256
typedef struct CrsmCmdParam_Tag
{
    UINT8       command;
    UINT16      fileId;
    UINT8       p1;
    UINT8       p2;
    UINT8       p3;
    UINT16      dataLen;
    UINT8       data[SIM_APDU_DATA_MAX_LEN];
    UINT8       pathLen;
    UINT8       filePath[SIM_FILE_PATH_MAX_LEN];
}
CrsmCmdParam;

typedef struct CrsmRspParam_Tag
{
    UINT8    sw1;
    UINT8    sw2;
    UINT8    respLen;
    UINT8    responseData[SIM_APDU_DATA_MAX_LEN];

}
CrsmRspParam;

struct crsmApiMsg {
  CrsmCmdParam  *cmdParam;
  CrsmRspParam  *responseParam;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct ecbandApiMsg {
    UINT8 networkMode;
    UINT8 bandNum;
    UINT16 result;
    UINT8 *orderBand;
    osSemaphoreId_t *sem;
};


typedef struct SrvCellBasicInfoTag{
    UINT16          mcc;
    UINT16          mncWithAddInfo; // if 2-digit MNC type, the 4 MSB bits should set to 'F',
    /* Example:
    *  46000; mcc = 0x0460, mnc = 0xf000
    *  00101; mcc = 0x0001, mnc = 0xf001
    *  46012; mcc = 0x0460, mnc = 0xf012
    *  460123; mcc = 0x0460, mnc = 0x0123
    */

    //DL earfcn (anchor earfcn), range 0 - 262143
    UINT32          earfcn;
    //the 28 bits Cell-Identity in SIB1, range 0 - 268435455
    UINT32          cellId;

    //physical cell ID, range 0 - 503
    UINT16          phyCellId;
    // value in dB, value range: -30 ~ 30
    BOOL            snrPresent;
    INT8            snr;

    //value in units of dBm, value range: -156 ~ -44
    INT16           rsrp;
    //value in units of dB, value range: -34 ~ 25
    INT16           rsrq;
}SrvCellBasicInfo;

typedef struct NCellBasicInfoTag{
    UINT32          earfcn;     //DL earfcn (anchor earfcn), range 0 - 262143

    UINT16          phyCellId;
    UINT16          revd0;

    //value in units of dBm, value range: -156 ~ -44
    INT16           rsrp;
    //value in units of dB, value range: -34 ~ 25
    INT16           rsrq;
}NCellBasicInfo;

#define NCELL_INFO_CELL_NUM     4
typedef struct BasicCellListInfoTag{
    BOOL                sCellPresent;
    UINT8               nCellNum;

    SrvCellBasicInfo    sCellInfo;
    NCellBasicInfo      nCellList[NCELL_INFO_CELL_NUM];
}BasicCellListInfo;

struct ecbcInfoApiMsg{
    BasicCellListInfo   *bcInfo;
    osSemaphoreId_t     *sem;
    UINT16              result;
};

#define SUPPORT_MAX_FREQ_NUM    8 //== CMI_DEV_SUPPORT_MAX_FREQ_NUM
typedef struct CiotFreqParams_Tag
{
    UINT8   mode;       // CmiDevGetFreqModeEnum  3:means UE has set preferred EARFCN list and has locked EARFCN
    UINT8   cellPresent;// indicate whether phyCellId present
    UINT16  phyCellId; // phyCell ID, 0 - 503

    UINT8   arfcnNum; // 0 is not allowed for mode is CMI_DEV_SET_PREFER_FREQ (1);
                      // max number is CMI_DEV_SUPPORT_MAX_FREQ_NUM
    UINT8   reserved0;
    UINT16  reserved1;
    UINT32  lockedArfcn;//locked EARFCN
    UINT32  arfcnList[SUPPORT_MAX_FREQ_NUM];
}CiotFreqParams; // total 44 bytes


/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/

//void appCheckTcpipReady(void);
void psSyncProcCmiCnf(const SignalBuf *cnfSignalPtr);

CmsRetId initPsCmiReqMapList(void);
CmsRetId appGetNetInfoSync(UINT32 cid, NmAtiSyncRet *result );
CmsRetId appGetImsiNumSync(CHAR *imsi);
CmsRetId appGetIccidNumSync(CHAR *iccid);
CmsRetId appGetImeiNumSync(CHAR *imei);
CmsRetId appGetPSMSettingSync(UINT8 *psmmode, UINT32 *tauTime, UINT32 *activeTime);
CmsRetId appSetPSMSettingSync(UINT8 psmMode, UINT32 tauTime, UINT32 activeTime);
CmsRetId appGetCeregStateSync(UINT8 *state);
CmsRetId appGetEDRXSettingSync(UINT8 *actType, UINT32 *nwEdrxValueMs, UINT32 *nwPtwMs);
CmsRetId appSetEDRXSettingSync(UINT8 modeVal, UINT8 actType, UINT32 reqEdrxValueMs);
CmsRetId appGetLocationInfoSync(UINT16 *tac, UINT32 *cellId);
CmsRetId appGetTAUInfoSync(UINT32 *tauTimeS, UINT32 *activeTimeS);
CmsRetId appGetAPNSettingSync(UINT8 cid, UINT8 *apn);
CmsRetId appCheckSystemTimeSync(void);
CmsRetId appGetSystemTimeSecsSync(time_t *time);
CmsRetId appGetSystemTimeUtcSync(utc_timer_value_t *time);
CmsRetId appSetSystemTimeUtcSync(UINT32 time1, UINT32 time2);
CmsRetId appGetActedCidSync(UINT8 *cid, UINT8 *num);

/**
  \fn          appSetSimLogicalChannelOpenSync
  \brief       Send cmi request to open SIM logical channel
  \param[out]  *sessionID: Pointer to a new logical channel number returned by SIM
  \param[in]   *dfName: Pointer to DFname selected on the new logical channel
  \returns     CMS_RET_SUCC: success
  \            CMS_SIM_NOT_INSERT: SIM not inserted
  \            CMS_OPER_NOT_SUPPROT: operation not supported
*/
CmsRetId appSetSimLogicalChannelOpenSync(UINT8 *sessionID, UINT8 *dfName);

/**
  \fn          appSetSimLogicalChannelCloseSync
  \brief       Send cmi request to close SIM logical channel
  \param[in]   sessionID: the logical channel number to be closed
  \returns     CMS_RET_SUCC---success
  \            CMS_SIM_NOT_INSERT: SIM not inserted
  \            CMS_INVALID_PARAM: input invalid parameters
*/
CmsRetId appSetSimLogicalChannelCloseSync(UINT8 sessionID);

/**
  \fn          appSetSimGenLogicalChannelAccessSync
  \brief       Send cmi request to get generic SIM logical channel access
  \param[in]   sessionID: the logical channel number
  \param[in]   *command: Pointer to command apdu
  \param[in]   cmdLen: the length of command apdu
  \param[out]  *response: Pointer to response apdu
  \param[out]  respLen: the length of command apdu
  \returns     CMS_RET_SUCC---success
  \            CMS_SIM_NOT_INSERT: SIM not inserted
  \            CMS_INVALID_PARAM: input invalid parameters
*/
CmsRetId appSetSimGenLogicalChannelAccessSync(UINT8 sessionID, UINT8 *command, UINT8 cmdLen,
                                                UINT8 *response, UINT8 *respLen);

/**
  \fn          appSetRestrictedSimAccessSync
  \brief       Send cmi request to get generic SIM access
  \param[in]   *pCmdParam: Pointer to command parameters
  \param[out]  *pRspParam: Pointer to response parameters
  \returns     CMS_RET_SUCC---success
  \            CMS_SIM_NOT_INSERT: SIM not inserted
  \            CMS_INVALID_PARAM: input invalid parameters
*/
CmsRetId appSetRestrictedSimAccessSync(CrsmCmdParam *pCmdParam, CrsmRspParam *pRspParam);

/**
  \fn          CmsRetId appSetCFUN(UINT8 fun)
  \brief       Send cfun request to NB
  \param[in]   fun: 0 minimum function and 1 full function
  \returns     CmsRetId
*/
CmsRetId appSetCFUN(UINT8 fun);
CmsRetId appSetBootCFUNMode(UINT8 mode);
UINT8 appGetBootCFUNMode(void);
UINT8 appGetSearchPowerLevelSync(void);
UINT8 appGetCELevelSync(void);
CmsRetId appGetSignalInfoSync(UINT8 *csq, INT8 *snr, INT8 *rsrp);
UINT8* appGetNBVersionInfo(void);
void drvSetPSToWakeup(void);
BOOL appSetImeiNumSync(CHAR* imei);
BOOL appGetSNNumSync(CHAR* sn);
BOOL appSetSNNumSync(CHAR* sn, UINT8 len);

BOOL appGetImeiLockSync(CHAR* imeiLock);
BOOL appSetImeiLockSync(CHAR* imeiLock);
BOOL appGetSNLockSync(CHAR* snLock);
BOOL appSetSNLockSync(CHAR* snLock);
BOOL appSetNV9LockCleanSync(void);

/**
  \fn          CmsRetId appSetBandModeSync(UINT8 networkMode, UINT8 bandNum,  UINT8 *orderBand)
  \brief
  \param[out] networkMode: network mode
  \param[out] bandNum: valid num of orderBand
  \param[out] orderBand is an array of size 16 bytes

  \returns     CmsRetId
*/
CmsRetId appSetBandModeSync(UINT8 networkMode, UINT8 bandNum,  UINT8 *orderBand);
/**
  \fn          CmsRetId appGetBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand)
  \brief
  \param[out] networkMode: network mode
  \param[out] bandNum: valid num of orderBand
  \param[out] orderBand is an array of size 16 bytes
  \returns     CmsRetId
*/
CmsRetId appGetBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand);

/**
  \fn          CmsRetId appGetSupportedBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand)
  \brief
  \param[out] networkMode: network mode
  \param[out] bandNum: valid num of orderBand
  \param[out] orderBand is an array of size 16 bytes
  \returns     CmsRetId
*/
CmsRetId appGetSupportedBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand);


/**
  \fn          CmsRetId appGetECBCInfoSync(BasicCellListInfo *bcListInfo)
  \brief       Send cmi request to get basic cell information
  \param[out]  *bcListInfo     Pointer to store the result basic cell info
  \returns     CmsRetId
*/
CmsRetId appGetECBCInfoSync(BasicCellListInfo *bcListInfo);

/**
  \fn          CmsRetId appSetCiotFreqSync
  \brief       Send cmi request to set prefer EARFCN list, lock or unlock cell
  \param[in]   CiotFreqParams *pCiotFreqParams, the pointer to the CiotFreqParams
  \returns     CmsRetId
  \NTOE:       Set EARFCN must be restricted to execute in power off or air plane state.
*/
CmsRetId appSetCiotFreqSync(CiotFreqParams *pCiotFreqParams);

/**
  \fn          CmsRetId appGetCiotFreqSync
  \brief       Send cmi request to get the current EARFCN setting.
  \param[out]  CiotFreqParams *pCiotFreqParams, the pointer to the CiotFreqParams
  \returns     CmsRetId
*/
CmsRetId appGetCiotFreqSync(CiotFreqParams *pCiotFreqParams);

#endif

