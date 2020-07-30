#ifndef __MW_CONFIG_H__
#define __MW_CONFIG_H__
/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of EigenComm Ltd.
 * File name:    mw_config.h
 * Description:  middleware configuration header file
 * History:      Rev1.0   2019-04-10
 *
 ****************************************************************************/
#include "osasys.h"

#include "PhyAtCmdDebug.h"

#include "cms_def.h"
//#include "ps_sms_if.h"


/******************************************************************************
 *****************************************************************************
 * MARCO/MARCO
 *****************************************************************************
******************************************************************************/

/*
 * CMS/AT channel 0 is reserved for internal
*/
#define MID_WARE_USED_AT_CHAN_NUM   (CMS_CHAN_NUM-1)

#define MID_WARE_NVM_FILE_VERSION   0
#define MID_WARE_NVM_FILE_NAME      "midwareconfig.nvm"

#define MID_WARE_DM_APPKEY_LEN      11
#define MID_WARE_DM_SECRET_LEN      33

#define MID_WARE_SIM_CCID_LEN       20
#define MID_WARE_DEFAULT_DNS_NUM    2
#define MID_WARE_IPV4_ADDR_LEN      4
#define MID_WARE_IPV6_ADDR_LEN      16

#define MID_WARE_MODEL_LEN          24   /*for autoreg model*/
#define MID_WARE_SWVER_LEN          24   /*for autoreg swver*/
#define MID_WARE_REGACK_LEN         16   /*for autoreg ack print*/

typedef enum MidWareATChanCfgEnum_Tag
{
    MID_WARE_AT_CHAN_ECHO_CFG,      //ATE0/ATE1
    MID_WARE_AT_CHAN_SUPPRESS_CFG,  //ATQ0/ATQ1
    MID_WARE_AT_CHAN_CREG_RPT_CFG,  //CmiMmCregModeEnum
    MID_WARE_AT_CHAN_CEREG_RPT_CFG, //CmiPsCeregModeEnum
    MID_WARE_AT_CHAN_EDRX_RPT_CFG,  //TRUE/FALSE
    MID_WARE_AT_CHAN_CIOT_OPT_RPT_CFG,  //CmiMmCiotReportModeEnum
    MID_WARE_AT_CHAN_CSCON_RPT_CFG,
    MID_WARE_AT_CHAN_SMS_MODE_CFG,  //PDU mode/TEXT mode
    MID_WARE_AT_CHAN_TIME_ZONE_REP_CFG, //CTZR
    MID_WARE_AT_CHAN_TIME_ZONE_UPD_CFG, //CTZU
    MID_WARE_AT_CHAN_CMEE_CFG,      //CMEE
    MID_WARE_AT_CHAN_ECCESQ_RPT_CFG,    //ECCESQ
    MID_WARE_AT_CHAN_CGEREP_MODE_CFG,   //CGEREP
    MID_WARE_AT_CHAN_PSM_RPT_CFG,     //ECPSMR
    MID_WARE_AT_CHAN_EMM_TIME_RPT_CFG,     //ECEMMTIME
    MID_WARE_AT_CHAN_PTW_EDRX_RPT_CFG,  //ECPTWEDRXP
    MID_WARE_AT_CHAN_ECPIN_STATE_RPT_CFG,  //ECPIN
    MID_WARE_AT_CHAN_ECPADDR_RPT_CFG,   //ECPADDR
    MID_WARE_AT_CHAN_ECPCFUN_RPT_CFG,   //ECPCFUN
    MID_WARE_AT_CHAN_ECLED_MODE_CFG,    //ECLEDMODE
    MID_WARE_AT_CHAN_ECPURC_HIB_RPT_CFG, //ECPURC HIB report

    MID_WARE_AT_CHAN_CFG_MAX
}MidWareATChanCfgEnum;

typedef enum MidWareDMCfgEnum_Tag
{
    MID_WARE_AT_DM_MODE_CFG, //DM mode  0:no dm  1: has dm
    MID_WARE_AT_DM_LIFETIME_CFG, //DM lifetime unit:minute
    MID_WARE_AT_DM_APPKEY_CFG, //DM appkey string like "M100000364"
    MID_WARE_AT_DM_SECRET_CFG, //DM secret string like "j5MOg7I6456971aQN7z6Bl36Xk5wYA5Q"
    MID_WARE_AT_DM_TEST_CFG, //DM test mode 0:commercial platform  1:test platform


    MID_WARE_AT_DM_CFG_MAX
}MidWareDMCfgEnum;


//atChanConfig


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

typedef struct MidWareNvmHeader_Tag
{
    UINT16 fileBodySize; //file body size, not include size of header;
    UINT8  version;
    UINT8  checkSum;
}MidWareNvmHeader;


typedef struct MidWareDefaultDnsCfg_Tag
{
    UINT8   ipv4Dns[MID_WARE_DEFAULT_DNS_NUM][MID_WARE_IPV4_ADDR_LEN];
    UINT8   ipv6Dns[MID_WARE_DEFAULT_DNS_NUM][MID_WARE_IPV6_ADDR_LEN];
}MidWareDefaultDnsCfg;     //40 bytes

typedef struct MidWareDmConfig_Tag
{
    UINT8   mode;        //DM mode  0:no dm  1: has dm
    UINT8   test;        //DM test mode 0:commercial platform  1:test platform
    UINT16  lifeTime;    //DM lifetime unit:minute
    CHAR    appKey[MID_WARE_DM_APPKEY_LEN];    //DM appkey string like "M100000364"
    CHAR    secret[MID_WARE_DM_SECRET_LEN];    //DM secret string like "j5MOg7I6456971aQN7z6Bl36Xk5wYA5Q"
}MidWareDmConfig;   //48 bytes

/*
 * SMS Text Mode Parameters, set by: AT+CSMP=[<fo>[,<vp>[,<pid>[,<dcs>]]]]
*/
typedef struct MidWareCSMPParam_Tag
{
    UINT8   fo;               // First octet +CSMP=
    UINT8   vp;               // Validity Period, this maybe a string type, - TBD
    UINT8   pid;              // Protocol Identifier
    UINT8   dcs;              // Data coding scheme
}MidWareCSMPParam;

typedef struct MidWareSetCSMPParam_Tag
{
    BOOL    foPresent;
    BOOL    vpPresent;
    BOOL    pidPresent;
    BOOL    dcsPresent;

    MidWareCSMPParam    csmpParam;
}MidWareSetCSMPParam;


/*
 * used for AT CMD channel
*/
typedef struct MidWareAtChanConfig_Tag
{
    UINT32  chanId           : 4;       //PSDecoderChann, currently, only one channel used for ATCMD: PS_CHANNEL_MODEM
    UINT32  echoValue        : 1;       //ATE0/ATE1, set whether need to echo each AT CMD REQ
    UINT32  suppressionValue : 1;       //ATQ0/ATQ1, whether suppress result code
    UINT32  cregRptMode      : 2;       //CmiMmCregModeEnum

    UINT32  ceregRptMode     : 3;       //CmiPsCeregModeEnum
    UINT32  needEdrxRpt      : 1;       //AT+CEDRXS, whether need to report EDRX value, when EDRX value changes
    UINT32  needCiotOptRpt   : 3;       //CmiMmCiotReportModeEnum
    UINT32  smsSendMode      : 1;       //+CMGF=[<n>] Pdu/Text mode, PsilSmsFormatMode

    UINT32  csconRptMode     : 2;       //+CSCON=[<n>], AtcCSCONRptLevel
    UINT32  cmeeMode         : 2;       //+CMEE, AtcCMEERetType
    UINT32  timeZoneRptMode  : 2;       //+CTZR, AtcCTZRRptValue
    UINT32  timeZoneUpdMode  : 1;       //+CTZU, AtcCTZUUpdateValue
    UINT32  cgerepMode       : 1;       //+CGEREP, AtcCGEREPMode

    UINT32  eccesqRptMode    : 2;       //+ECCESQ, AtcECCESQRptValue
    UINT32  ecpsmRptMode     : 1;       //+ECPSMR, AtcECPSMRValue
    UINT32  ecemmtimeRptMode : 3;       //+ECEMMTIME
    UINT32  ecPtwEdrxRpt     : 1;       //AT+ECPTWEDRXS, whether need to report PTW/EDRX value, when PTW/EDRX value changes
    UINT32  ecpinRptMode     : 1;       //+ECPIN,

    UINT32  ecpaddrRptMode   : 1;       //+ECPADDR
    UINT32  ecpcfunRptMode   : 1;       //+ECPCFUN
    UINT32  ecledMode        : 1;       //+ECLEDMODE
    UINT32  ecHibRptMode     : 1;       //+ECPURC=Hibnate,enable
    UINT32  rsvd0            : 28;

    MidWareCSMPParam    textSmsParam;
}MidWareAtChanConfig;


/*
 * Middle ware NVM file structure
*/
typedef struct MidWareNvmConfig_Tag
{
    /*
     * used for AT CMD
    */

    /*
     * AT channel NVM config
    */
    MidWareAtChanConfig atChanConfig[MID_WARE_USED_AT_CHAN_NUM];  //8*4 bytes

    /*
     * used for autoReg
    */
    struct {
        UINT32  autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   ccid[MID_WARE_SIM_CCID_LEN];  /* ccid */
        UINT8   model[MID_WARE_MODEL_LEN];  /* autoReg model */
        UINT8   swver[MID_WARE_SWVER_LEN];  /* autoReg swver */
        UINT8   autoRegAck[MID_WARE_REGACK_LEN];  /* autoReg ack */
    } autoRegConfig;    //36 bytes

    struct {
        UINT32  autoRegLastRegSuccTime;       /*autoRegLastRegSuccTime:  last register succ time*/
        UINT32  autoRegPastTime;       /*autoRegPastTime: time form last register succ time*/
        UINT32  autoRegRang;       /*autoRegRang*/
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCuccConfig;    //36 bytes

    struct {
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCtccConfig;    //36 bytes

    /*
     * used for CMS other sub-mode
    */
    MidWareDefaultDnsCfg    defaultDnsCfg;     //40 bytes

    /*
     * used for DM
    */
    MidWareDmConfig         dmConfig; //48 bytes

    /*
     * used for phy
     */
    PhyDebugAtCmdInfo       phyAtCmdContent;  //28 bytes

    /*
     * used for middleware sleep retention power on clear flag
    */
    struct {
        UINT32   timeSyncTriggered;//set when time sync trigger after power on(by NITZ or SNTP)
    } mwSleepRetenFlag;

}MidWareNvmConfig;



/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/

/*
 * load/read "midwareconfig.nvm" NVM file
*/
void mwLoadNvmConfig(void);

/*
 * save "midwareconfig.nvm" NVM file
*/
void mwSaveNvmConfig(void);


/*
 * get one AT channel config item value
*/
UINT32 mwGetAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum);

/*
 * set and save one AT channel config item value
*/
void mwSetAndSaveAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum, UINT32 value);

/*
 * set one AT channel config item value, but not write to flash, need call API: mwSaveNvmConfig()
 * used in case: if need to write several config values, in order to reduce times of write flash
*/
void mwSetAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum, UINT32 value, BOOL *bChanged);

/*
 * Get all csmp config value
*/
BOOL mwGetCsmpConfig(UINT8 chanId, MidWareCSMPParam *config);

/*
 *Restore gAtSmsMessage's value
*/
//void mwRestoreSmsInfo(void);

/*
 * Set and save all CSMP config value
*/
void mwSetAndSaveCsmpConfig(UINT8 chanId, MidWareSetCSMPParam *pSetCsmp);

/*
 * get all DM config item value
*/
void mwGetAllDMConfig(MidWareDmConfig* config);
/*
 * get DM config item value
*/
UINT8* mwGetDMConfigItemValue(MidWareDMCfgEnum cfgEnum);

/*
 * set and save DM config item value
*/
void mwSetAndSaveDMConfigItemValue(MidWareDMCfgEnum cfgEnum, UINT8* value);

UINT8 mwGetCmccAutoRegEnableFlag(void);

/*
 * set DM config item value, but not write to flash, need call API: mwSaveNvmConfig()
 * used in case: if need to write several config values, in order to reduce times of write flash
*/
void mwSetDMConfigItemValue(MidWareDMCfgEnum cfgEnum, UINT8* value, BOOL *bChanged);

UINT8 mwGetEcAutoRegEnableFlag(void);
void mwSetEcAutoRegEnableFlag(UINT8 autoReg);
UINT8 *mwGetEcAutoRegModel(void);
UINT8 mwSetEcAutoRegModel(UINT8 *model);
UINT8 *mwGetEcAutoRegSwver(void);
UINT8 mwSetEcAutoRegSwver(UINT8 *swver);
UINT8 *mwGetEcAutoRegAckPrint(void);
UINT8 mwSetEcAutoRegAckPrint(UINT8 *ack);
UINT8 mwGetCtccAutoRegEnableFlag(void);
void mwSetCtccAutoRegEnableFlag(UINT8 autoReg);
UINT8 mwGetCtccAutoRegFlag(void);
void mwSetCtccAutoRegFlag(UINT8 autoReg);

UINT8 mwGetCuccAutoRegEnableFlag(void);
void mwSetCuccAutoRegEnableFlag(UINT8 autoReg);
UINT8 mwGetCuccAutoRegFlag(void);
void mwSetCuccAutoRegFlag(UINT8 autoReg);
UINT32 mwGetCuccAutoRegLastRegTime(void);
void mwSetCuccAutoRegLastRegTime(UINT32 autoRegTime);
UINT32 mwGetCuccAutoRegPastTime(void);
void mwSetCuccAutoRegPastTime(UINT32 autoRegTime);
UINT32 mwGetCuccAutoRegRang(void);
void mwSetCuccAutoRegRang(UINT32 autoRegRangTime);
UINT32 mwGetTimeSyncFlag(void);
void mwSetTimeSyncFlag(UINT32 timeSyncTriggered);

/*
 * Set the default DNS config, and save to NVM
*/
void mwSetAndSaveDefaultDnsConfig(MidWareDefaultDnsCfg *pDnsCfg);

/*
 * Get the default DNS config from NVM
*/
void mwGetDefaultDnsConfig(MidWareDefaultDnsCfg *pDnsCfg);


#endif

