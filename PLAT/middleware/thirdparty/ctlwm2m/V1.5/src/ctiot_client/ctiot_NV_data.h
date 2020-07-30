#ifndef __CTIOT_NV_DATA_H__
#define __CTIOT_NV_DATA_H__

#include "ctiot_lwm2m_sdk.h"


#define NV_OK                  0
#define NV_ERR_PARAMS         -1
#define NV_ERR_NOT_SAVE       -2
#define NV_ERR_MALLOC         -3
#define NV_ERR_CACHE_INVALID  -4


int32_t c2f_encode_params(ctiot_funcv1_context_t *pContext);
int32_t c2f_encode_context(ctiot_funcv1_context_t *pContext);
int32_t c2f_clean_params(ctiot_funcv1_context_t *pContext);
int32_t c2f_clean_context(ctiot_funcv1_context_t *pContext);

int32_t cache_get_bootflag(uint8_t *bootflag);

int32_t f2c_encode_context(ctiot_funcv1_context_t* pContext);
int32_t f2c_encode_params(ctiot_funcv1_context_t* pContext);

void print_cache(void);




#endif

