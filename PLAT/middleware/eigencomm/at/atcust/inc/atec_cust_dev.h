/******************************************************************************

*(C) Copyright 2018 EIGENCOMM International Ltd.

* All Rights Reserved

******************************************************************************
*  Filename:
*
*  Description:
*
*  History:
*
*  Notes:
*
******************************************************************************/
#ifndef _ATEC_CUST_DEV_H_
#define _ATEC_CUST_DEV_H_

#include <stdint.h>
#include "at_def.h"
#include "debug_log.h"
#include "debug_trace.h"


#define  CC_CGSN_VALUE_MIN   0
#define  CC_CGSN_VALUE_MAX   3
#define  CC_CGSN_VALUE_DEF   1

CmsRetId ccCGMI(const AtCmdInputContext *pAtCmdReq);
CmsRetId ccCGMM(const AtCmdInputContext *pAtCmdReq);
CmsRetId ccCGMR(const AtCmdInputContext *pAtCmdReq);
CmsRetId ccCGSN(const AtCmdInputContext *pAtCmdReq);
CmsRetId ccATI(const AtCmdInputContext *pAtCmdReq);

#endif

/* END OF FILE */
