#ifndef __MW_AON_INFO_H__
#define __MW_AON_INFO_H__
/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of EigenComm Ltd.
 * File name:    mw_aon_info.h
 * Description:
 * History:      Rev1.0
 *
 ****************************************************************************/
#include "commontypedef.h"
#include "cms_sock_mgr.h"

#if defined CHIP_EC616 || defined CHIP_EC616_Z0
#include "ecpm_ec616_external.h"
#include "slpman_ec616.h"
#elif defined CHIP_EC617
#include "ecpm_ec617_external.h"
#include "slpman_ec617.h"
#endif


/******************************************************************************
 *****************************************************************************
 * MARCO/ENUM
 *****************************************************************************
******************************************************************************/
#define MID_WARE_AON_MAGIC_WORDS    0xA3B5C7D9


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/









typedef struct MidWareSockAonInfo_Tag
{
    CmsSockMgrHibContext sockContext;
}MidWareSockAonInfo;



/******************************************************************************
 *
 * Middleware info stored in AON memory, limited size: PMU_AON_MID_WARE_MEM_SIZE
 *
******************************************************************************/
typedef struct MidWareAonInfo_Tag
{
    UINT32  boolBitInfo;

    /*
     * socket aon info
    */
    MidWareSockAonInfo  mwSockAonInfo;

}MidWareAonInfo;



/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/

/*
 * INIT
*/
void mwAonInfoInit(void);

/*
 * used for SOCK task
*/
MidWareSockAonInfo* mwGetSockAonInfo(void);
void mwSetSockAonInfo(MidWareSockAonInfo *pSockAonInfo);
void mwSockAonInfoChanged(void);

void mwAonTaskRecovery(void);


#endif


