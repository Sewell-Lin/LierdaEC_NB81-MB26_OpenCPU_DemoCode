#ifndef __PS_NVM_H__
#define __PS_NVM_H__
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of EigenComm Ltd.
 File name:      - psnvm.h
 Description:    - Protocol Stack NVM files
 History:        - 13/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/
#include "pssys.h"
#include "psnvmutil.h"
#include "pscommtype.h"

#ifdef WIN32
#define NV_MAX 10
#else
#include "nvram.h"
#endif

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/
typedef enum PsNvmFileIdEnum_Tag
{
    //PS_BASE_NVM = 0,
    PS_CCM_CONFIG_NVM = 0,  //NV1
    PS_CEMM_CONFIG_EMM_INFORMATION_NVM, //NV2
    PS_CEMM_CONFIG_UE_INFORMATION_NVM,  //NV3
    PS_CEMM_PLMN_CONFIG_NVM,    //NV4
    PS_CESM_CONFIG_NVM,         //NV5
    PS_UICCCTRL_CONFIG_NVM,     //NV6
    PS_CERRC_CONFIG_NVM,        //NV7

    PS_MAX_NVM = NV_MAX
}PsNvmFileIdEnum;



/******************************************************************************
 ******************************************************************************
 * DEFINE each NVM DATA structure, and related version here.
 ******************************************************************************
******************************************************************************/
/******************************************************************************
 * CCM NVM
******************************************************************************/

typedef struct PsNvmCcmConfig_Tag
{
    UINT8       srvType;    //UeService
    UINT8       nwMode;     //NwMode
    BOOL        bAutoApn;   //whether AUTO APN
    BOOL        bSIMTest;   //whether sim case test

    BOOL        bRohc;      //whether enable "header compression"
    BOOL        bIpv6RsForTestSim;
    BOOL        bUsimSimulator;//whether USIM simulator
    BOOL        bAutoBand;

    UINT8       powerOnCfun;    //default CFUN state (0/1/4), when power on/reboot; CMI_DEV_MIN_FUNC
    UINT16      powerOnMaxDelay;//default random delay value(seconds) before triggering PS power on in CCM
    UINT8       smsService;//MsgService


    BOOL        bEnableBip;      //whether enable BIP
    BOOL        bEnableSimPsm;      //whether enable USIM card power saving mode
    UINT16      ipv6GetPrefixTime; //the maximum time of getting IPv6 prefix Unit: second.

    BOOL        bSimSleep; //whether allowed SIM sleep, that means SIM deactivated
    UINT8       rsvd1;
    UINT16      rsvd2;
}PsNvmCcmConfig;    //12 bytes

#define CUR_CCM_CFG_VER 0x00


/******************************************************************************
 * CEMM EMM NVM
******************************************************************************/
typedef struct PsNvmCemmConfigEmmInformation_Tag
{
    UINT8           gutiContents[10];   /* GUTI */
    UINT8           epsUpdateStatus;    /* EpsUpdateStatus */
    Tai             lastRegisteredTai;  /* Last visited registered TAI */
    UINT8           asmeKsi;            /* KSIasme, if invalid, set to NO_KEY_IS_AVAILABLE :0x07 */
    AsmeKey         asmeKey;            /* Key Asme */
    UINT8           algorithmId;        /* Ciphering & Integrity protection algorithm ID */
    NasCount        ulNasCount;         /* Uplink NAS count */
    NasCount        dlNasCount;         /* Downlink NAS count */
    Imsi            imsi;               /* IMSI */
    DedicatedCoreNetworkId  dcnId[32];  /* DCN-ID list */
}PsNvmCemmConfigEmmInformation;

#define UE_NETWORK_CAPABILITY_MAX_LEN   13
typedef struct PsNvmCemmConfigUeNwCapability_Tag
{
    UINT8       networkCapabilityLength;
    UINT8       networkCapability[UE_NETWORK_CAPABILITY_MAX_LEN];   /* default value:{0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0xFC, 0x01} */
}PsNvmCemmConfigUeNwCapability;

typedef struct PsNvmCemmPsmEdrx_Tag
{
    UINT8                   t3324Mode;
    UINT8                   t3412ExtMode;
    UINT8                   edrxMode;
    GprsTimer2              t3324Value;
    GprsTimer3              t3412ExtendedValue;
    ExtendedDrxParameters   extendedDrxParameters;
}PsNvmCemmPsmEdrx;

typedef struct PsNvmCemmCommInfo_Tag
{
    BOOL                    smsOnly;
    BOOL                    tauForSmsControl;
    BOOL                    attachWithoutPdn;
    UINT32                  userSetT3324Value;
    CemmCiotOptTypeEnum     ciotOptimization;
    CemmCiotOptTypeEnum     preferedCiotOptimization;
}PsNvmCemmCommInfo;

typedef struct PsNvmCemmConfigUeInformation_Tag
{
    PsNvmCemmConfigUeNwCapability   cemmUeNwCapability;
    PsNvmCemmPsmEdrx                cemmPsmEdrx;
    PsNvmCemmCommInfo               cemmCommInfo;
}PsNvmCemmConfigUeInformation;


#define CUR_CEMM_CFG_VER 0x00

/******************************************************************************
 * CEMM PLMN NVM
******************************************************************************/
typedef struct CePlmnNvmConfig_Tag
{
    UINT16  plmnSelectType : 3;         //CemmPlmnSelectTypeEnum
    UINT16  plmnSearchPowerLevel : 2;   //plmnSearchPowerLevel
    UINT16  bCellLock : 1;
    UINT16  reserved0 : 10;

    //BOOL    bCellLock;          //Be cell lock;
    //UINT16  lockPhyCellId;      //if "bCellLock" = TRUE, could lock to dedicated PHY CELL, 0xFFFF means invalid
    /*
     * Lock/Preferred PHY Cell ID, used in two cases:
     * 1> Cell lock, if phyCellId specified to lock;
     * 2> PhyCellId which need PHY prefer to find, last serving cell phyCellId
    */
    UINT16  phyCellId;   //range(0..503), 0xFFFF means invalid

    Plmn    manualPlmn;
    Plmn    rplmn;              //previous registered PLMN

    Imsi    preImsi;

    //PlmnSearchPowerLevel    plmnSearchPowerLevel;

    /*
     * 24.301 - 5.3.4
     * When the UE is switched off, it shall keep the stored list so that it can
     *  be used for PLMN selection after switch on. The UE shall delete the stored
     *  list if the USIM is removed,
     * The maximum number of possible entries in the stored list is 16
     * if plmn is set to 0, just means invalid PLMN
    */
    Plmn    eplmnList[CEMM_PLMN_LIST_MAX_NUM];  //64 bytes

    /*
     * 23.122 - 3.1
     * If a message with cause value "PLMN not allowed" is received by an MS in response to an LR request from a VPLMN,
     * that VPLMN is added to a list of "forbidden PLMNs" in the SIM and thereafter that VPLMN will not be accessed by
     * the MS when in automatic mode.
     * This list is retained when the MS is switched off or the SIM is removed. The HPLMN (if the EHPLMN list is not present or is empty)
     * or an EHPLMN (if the EHPLMN list is present) shall not be stored on the list of "forbidden PLMNs"
     * As the FPLMN should still remained, even if SIM removed, so need to store into NVM
     * if plmn is set to 0, just means invalid PLMN
    */
    Plmn    fPlmnList[CEMM_PLMN_LIST_MAX_NUM];  //64 bytes

    /*
     * if band is set to 0, just means invalid PLMN
    */
    UINT8   band[SUPPORT_MAX_BAND_NUM];   //UE BAND info, 16 bytes

    /* EARFCN locked by AT+ECFREQ=2,earfcn */
    UINT32  lockedFreq;
    /*
     * if no prefer Frequency, set to 0;
    */
    UINT32  preFreq[SUPPORT_MAX_FREQ_NUM];  //32 bytes
}CePlmnNvmConfig; //200 bytes

#define CUR_CEMM_PLMN_NVM_CFG_VER 0x00

/******************************************************************************
 * CESM NVM
******************************************************************************/
#define CUR_CEMM_ESM_NVM_CFG_VER 0x00
#define MAX_APN_LEN_NVM          100
#define MAX_AUTH_STR_LEN_NVM     20

typedef struct PdnPcoInfoNvm_Tag
{
    ConfigurationProtocol       protocol;
    UINT8                       ipcpReq;
    UINT8                       pCscfIpv6Req;
    UINT8                       dnsIpv6Req;

    UINT8                       ipAddrViaNas;
    UINT8                       ipv4AddrViaDhcp;
    UINT8                       pCscfIpv4Req;
    UINT8                       dnsIpv4AddrReq;

    UINT8                       ipv4MtuReq;
    UINT8                       nonIpMtuReq;
    UINT8                       apnRateCtrlInd;
    UINT8                       addApnRateCtrlInd;

    UINT8                       rdsReqInd;
    UINT8                       psDataOffInd;
    UINT8                       psDataOffStatus;
    UINT8                       imCnFlagReq;

    UINT8                       authProtocol;
    UINT8                       authUserNameLength;
    UINT8                       authUserName[MAX_AUTH_STR_LEN_NVM];
    UINT8                       authPasswordLength;
    UINT8                       authPassword[MAX_AUTH_STR_LEN_NVM];
    UINT8                       reserved1;
}
PdnPcoInfoNvm;


typedef struct CemmEsmNvmConfig_Tag
{
    BOOL                eitfPresent;
    UINT8               eitf;
    BOOL                NSLPIPresent;
    UINT8               NSLPI;
    UINT8               pdnType;    //PdnType
    BOOL                epcoFlag;
    BOOL                ipv4DnsToBeRead;
    BOOL                ipv6DnsToBeRead;

    UINT8               apnLen;
    UINT8               apnData[MAX_APN_LEN_NVM];
    PdnPcoInfoNvm       pdnPcoInfo;
}
CemmEsmNvmConfig;

/******************************************************************************
 * UICCCTRL NVM
******************************************************************************/
#define CUR_UICCCTRL_NVM_CFG_VER 0x00
#define MAX_TP_LEN_NVM   32//64
#define MAX_SWC_EF_LIST_NUM_NVM    20

typedef struct SimWriteCntNvm_Tag
{
    UINT16      fileId;
    UINT16      reserved;
    UINT32      writeCnt;//SIM write counter
}
SimWriteCntNvm;

typedef struct UiccCtrlNvmConfig_tag
{
    UINT8                   tpLen;//the length of terminal profile
    BOOL                    swcEnable;//sim write counter enable or not
    UINT8                   swcNum;//the number of writed EF counter
    UINT8                   reserved;
    UINT8                   tpData[MAX_TP_LEN_NVM];//the content of the terminal profile
    SimWriteCntNvm          swcList[MAX_SWC_EF_LIST_NUM_NVM];
}
UiccCtrlNvmConfig;

/******************************************************************************
 * CERRC NVM
******************************************************************************/
#define CUR_CERRC_NVM_CFG_VER 0x00

/*
 * As Release, start from Rel-13
*/
typedef UINT8 AsReleaseType_t;
typedef enum AsReleaseType_Tag
{
    AsRelease_13 = 13,
    AsRelease_14,
    AsRelease_15,
}AsReleaseType;

/*
 * UE category, ref to 36.306
*/
typedef UINT8 UeCategoryType_t;
typedef enum UeCategoryType_Tag
{
    UeCategory_NB1 = 0x01,
    UeCategory_NB2 = 0x02,
    UeCategory_M1 = 0x11,
    UeCategory_M2 = 0x12,
    UeCategory_1bis = 0x21,
}UeCategoryType;

typedef struct CerrcNvmConfig_Tag
{
    AsReleaseType_t     asRelease;
    UeCategoryType_t    ueCategory;

    //indicate the value of rai_Support_r14 in UeCapabilityInfomation
    BOOL                bRaiSupport;
    //indicate the value of multiCarrier_r13 in UeCapabilityInfomation
    BOOL                bMultiCarrierSupport;
    //indicate the value of multiTone_r13 in UeCapabilityInfomation
    BOOL                bMultiToneSupport;
    //Enable/Disable RRC cell reselection
    BOOL                bEnableCellResel;
    //Enable/Disable RRC connection re-establishment
    BOOL                bEnableConnReEst;
    //Disable intra/inter cell's measurements when criterion S fulfilled
    BOOL                bDisableNCellMeas;

    //range [0..15], value in dB, 0 means relaxed monitoring(36.304, 5.2.4.12) in is not used
    UINT8               sSearchDeltaP;
    //The DataInactivityTimer is used to control Data inactivity operation. Corresponds to the timer for data inactivity monitoring in TS 36.321 [6].
    //Value range:{1,2,3,5,7,10,15,20,40,50,60,80,100,120,150,180}, in seconds
    UINT8               dataInactivityTimer; //DataInactivityTimer
    UINT8               rsvd[3];
    //3 temp for relaxed monitoring test
    //UINT16              tSearchDeltaP;
}
CerrcNvmConfig;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
BOOL PsNvmRead(PsNvmFileIdEnum fileId, void *dataBuf, UINT16 bufSize);
BOOL PsNvmWrite(PsNvmFileIdEnum fileId, void *dataBuf, UINT16 bufSize);
#define PsNvmUpdate(fileId, dataBuf, bufSize) \
    PsNvmWrite(fileId, dataBuf, bufSize)
void PsNvmSaveAll(void);
BOOL PsNvmSave(PsNvmFileIdEnum fileId);

#endif

