/******************************************************************************

*(C) Copyright 2018 EIGENCOMM International Ltd.

* All Rights Reserved

******************************************************************************
*  Filename: atec_ctiot_cnf_ind_api.h
*
*  Description: Process ctiot related AT commands header
*
*  History:
*
*  Notes:
*
******************************************************************************/
#ifndef _ATEC_CTIOT_CNF_IND_API_H
#define _ATEC_CTIOT_CNF_IND_API_H

#include <stdio.h>
#include <string.h>
#include "at_util.h"
#include "ctiot_lwm2m_sdk.h"

#define ctiot_at_get_mod             ctiot_funcv1_get_mod
#define ctiot_at_set_pm              ctiot_funcv1_set_pm
#define ctiot_at_get_pm              ctiot_funcv1_get_pm
#define ctiot_at_get_reg_status      ctiot_funcv1_get_reg_status
#define ctiot_at_get_status          ctiot_funcv1_get_status
#define ctiot_at_clean_context       ctiot_funcv1_clean_context
#define ctiot_at_clean_params        ctiot_funcv1_clean_params
#define ctiot_at_set_psk             ctiot_funcv1_set_psk
#define ctiot_at_get_psk             ctiot_funcv1_get_psk
#define ctiot_at_set_idauth_pm       ctiot_funcv1_set_idauth_pm


uint16_t ctiot_at_set_mod(ctiot_funcv1_context_t* pContext,uint8_t modeId,uint8_t modeValue);
uint16_t ctiot_at_reg(ctiot_funcv1_context_t* pTContext);
uint16_t ctiot_at_dereg(ctiot_funcv1_context_t* pContext);
uint16_t ctiot_at_send(ctiot_funcv1_context_t* pTContext,char* data,ctiot_funcv1_send_mode_e sendMode, UINT8 seqNum);
uint16_t ctiot_at_update_bindmode(ctiot_funcv1_context_t* pContext,uint8_t bindMode,uint16_t* msgId,uint8_t* newObjList);
uint16_t ctiot_at_update_reg(ctiot_funcv1_context_t* pTContext,uint16_t*msgId,bool withObjects);
uint16_t ctiot_at_cmdrsp(ctiot_funcv1_context_t* pTContext,uint16_t msgId,char* token,uint16_t responseCode,char* uriStr,uint8_t observe,uint8_t dataFormat,char* dataS);
uint16_t ctiot_at_notify(ctiot_funcv1_context_t* pTContext,char* token,char* uriStr,uint8_t dataFormat,char* dataS,uint8_t sendMode);
uint16_t ctiot_at_dfota_mode(uint8_t mode);
uint16_t ctiot_at_regswt_mode(ctiot_funcv1_context_t* pTContext, uint8_t mode);
uint16_t ctiot_at_nsmi_mode(ctiot_funcv1_context_t* pTContext, uint8_t mode);
uint16_t ctiot_at_nnmi_mode(ctiot_funcv1_context_t* pTContext, uint8_t mode);
uint16_t ctiot_at_get_recvData(ctiot_funcv1_context_t* pTContext, uint8_t* datalen, uint8_t** dataStr);
uint16_t ctiot_at_free_recvData(ctiot_funcv1_context_t* pTContext);
ctiot_funcv1_boot_flag_e ctiot_at_get_bootflag(void);

void  ctiotEngineInit(void);
void atApplCtProcCmsCnf(CmsApplCnf *pCmsCnf);
void atApplCtProcCmsInd(CmsApplInd *pCmsInd);

#endif

