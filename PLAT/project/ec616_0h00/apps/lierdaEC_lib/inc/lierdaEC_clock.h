/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_clock.h
 * Description:  API interface implementation header file for CLOCK driver.
 * History:      Rev1.0   2020-04-17
 *
 ****************************************************************************/
#ifndef  LIERDAEC_CLOCK_H
#define  LIERDAEC_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "clock_ec616.h"


/**
  \fn    int32_t lierdaEC_CLOCK_SetClockSrc(clock_ID_t id, clock_select_t select)
  \brief Set clock source for selected module
  \param[in] id          clock item to set
  \param[in] select      select one of clock sources \ref clock_select_t
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
             ARM_DRIVER_ERROR if specific clock has been enabled
 */
int32_t lierdaEC_CLOCK_SetClockSrc(clock_ID_t id, clock_select_t select);

/**
  \fn    int32_t lierdaEC_CLOCK_SetClockDiv(clock_ID_t id, uint32 div)
  \brief Set clock divider for selected module
  \param[in] id          clock item to set
  \param[in] div         divider value
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id or div value is set to 0)
             ARM_DRIVER_ERROR if specific clock has been enabled
 */
int32_t lierdaEC_CLOCK_SetClockDiv(clock_ID_t id, uint32_t div);


/**
  \fn    int32_t lierdaEC_CLOCK_SetClockDiv(clock_ID_t id, uint32 div)
  \brief Get clock frequency for selected module
  \param[in] id          clock item to set
  \return    ARM_DRIVER_OK if the setting is successful
  */
uint32_t lierdaEC_GPR_GetClockFreq(clock_ID_t id);



#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_CLOCK_H */
