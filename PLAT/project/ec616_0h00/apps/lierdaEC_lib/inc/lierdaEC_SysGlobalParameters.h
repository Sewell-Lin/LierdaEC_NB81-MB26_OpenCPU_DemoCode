#ifndef _LIERDAEC_SYS_GLOBALPARAMETERS_H
#define _LIERDAEC_SYS_GLOBALPARAMETERS_H

#include "osasys.h"
#ifdef __cplusplus
extern "C"
{
#endif
  typedef struct Send_DATA
  {
    int32_t ADCDATA_To_IoTPlatform;
    uint16_t I2CDATA_To_IoTPlatform;
  } CT_Send_DATA;

#endif /* _LIERDAEC_SYS_GLOBALPARAMETERS_H */