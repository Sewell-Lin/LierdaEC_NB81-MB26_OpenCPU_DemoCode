/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_adc.h
 * Description:  API interface implementation header file for ADC driver.  
 * History:      Rev1.0   2020-04-15
 *
 ****************************************************************************/
#ifndef  LIERDAEC_ADC_H
#define  LIERDAEC_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "adc_ec616.h"
#include "hal_adc.h"
#include "ic_ec616.h"

/**
  \fn        void lierdaEC_ADC_ChannelInit(adc_channel_t channel)
  \brief     Initialize ADC specific channel
  \param[in] channel     ADC physical channel to be configured
 */
void lierdaEC_ADC_ChannelInit(adc_channel_t channel);

/**
  \fn        void ADC_ChannelDeInit(adc_channel_t channel)
  \brief     Deinitialize ADC channel
  \param[in] channel     physical channel to be de-initialized, configuration of specific logical channel is invalid after this API call.
 */
void lierdaEC_ADC_ChannelDeInit(adc_channel_t channel);

/**
  \fn        int32_t lierdaEC_ADC_GetCalibrateValue(adc_channel_t channel, int32_t *value)
  \brief     Starts ADC conversion. Conversion is performed imediately when ADC is free, otherwise, the start request is put into a request queue and will be serviced later.
             Then, calibarte ADC raw sample to voltage(mV). or convert ADC thermal channel raw sample to temperature(°C, centidegree).
  \param[in] channel    ADC physical channel to converse
  \param[in,out] *value    Pointer to ADC calibrate value(Vbat, temperature, or AIO_voltage)
  \return     ADC conversion status or error code
              0 on success, 
             -1 if request queue is full, 
             -2 if channel has not been initialized yet
             -3 if channel conversion wait timeout  
  \note   Delay Waiting for channels conversion completes       
 */
int32_t lierdaEC_ADC_GetCalibrateValue(adc_channel_t channel, int32_t *value);

/**
  \fn    int32_t lierdaEC_HAL_ADC_SampleVbatVoltage(uint32_t timeout_ms)
  \brief Get Vbat voltage in unit of mV in given time
  \param[in] timeout_ms  timeout value in unit of ms
  \return                error code or calibrated Vbat voltage
                          -2  : timeout
                          -1  : other errors
                          > 0 : calibrated Vbat voltage in unit of mV
  \note  This API shall only be used in task context since semphore is used for synchronization
 */
int32_t lierdaEC_HAL_ADC_SampleVbatVoltage(uint32_t timeout_ms);

/**
  \fn    lierdaEC_HAL_ADC_GetThermalTemperature(uint32_t timeout_ms, int32_t* temperatruePtr)
  \brief Get ADC thermal temperature in unit of degree centigrade in given time
  \param[in]     timeout_ms      timeout value in unit of ms
  \param[in,out] temperatruePtr  pointer to temperature
  \return                error code
                          -2  : timeout
                          -1  : other errors
  \note  This API shall only be used in task context since semphore is used for synchronization
 */
int32_t lierdaEC_HAL_ADC_GetThermalTemperature(uint32_t timeout_ms, int32_t* temperatruePtr);


#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_ADC_H */
