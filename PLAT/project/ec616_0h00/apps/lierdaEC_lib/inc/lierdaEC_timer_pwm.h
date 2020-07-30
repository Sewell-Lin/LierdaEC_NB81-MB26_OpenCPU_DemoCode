/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_timer_pwm.h
 * Description:  API interface implementation header file for TIMER and PWM driver.
 * History:      Rev1.0   2020-04-16
 *
 ****************************************************************************/
#ifndef  LIERDAEC_TIMER_PWM_H
#define  LIERDAEC_TIMER_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timer_ec616.h"
#include "lierdaEC_clock.h"


/**
  \fn    int32_t lierdaEC_TIMER_SetupPwm(uint32_t instance, const timer_pwm_config_t *config)
  \brief Configures the PWM signals period, mode, etc.
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] config      Pointer to PWM parameter
  \return    ARM_DRIVER_OK if the PWM setup is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure
 */
int32_t lierdaEC_TIMER_SetupPwm(uint32_t instance, const timer_pwm_config_t *config);

/**
  \fn    void lierdaEC_TIMER_UpdatePwmDutyCycle(uint32_t instance, uint32_t dutyCyclePercent)
  \brief Updates the duty cycle of PWM signal
  \param[in] instance              TIMER instance number (0, 1, ...)
  \param[in] dutyCyclePercent      New PWM pulse width, value shall be between 0 to 100,
                                   if the value exceeds 100, dutyCyclePercent is set to 100.
 */
void lierdaEC_TIMER_UpdatePwmDutyCycle(uint32_t instance, uint32_t dutyCyclePercent);

/**
  \fn    void lierdaEC_TIMER_Init(uint32_t instance, const timer_config_t *config)
  \brief Intialize TIMER
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] config      Pointer to TIMER configuration
  \note      PWM out is disabled after this function's call, use \ref TIMER_SetupPwm function to eable PWM
 */
void lierdaEC_TIMER_Init(uint32_t instance, const timer_config_t *config);

/**
  \fn    void lierdaEC_TIMER_DriverInit(void);
  \brief Intialize TIMER driver internal data, must be called before any other APIs
 */
void lierdaEC_TIMER_DriverInit(void);

/**
  \fn    void lierdaEC_TIMER_GetDefaultConfig(timer_config_t *config)
  \brief Gets the TIMER default configuartion.
         This function sets the configuration structure to default values as below:
  \code
         config->clockSource = TIMER_InternalClock;
         config->reloadOption = TIMER_ReloadOnMatch1;
         config->initValue = 0;
         config->match0 = 0x10000 >> 1;
         config->match1 = 0x10000;
         config->match2 = 0xFFFFFFFF;
  \endcode

  \param[in] config      Pointer to TIMER configuration structure
 */
void lierdaEC_TIMER_GetDefaultConfig(timer_config_t *config);

/**
  \fn    void lierdaEC_TIMER_InterruptConfig(uint32_t instance, TIMER_match_select_t match, timer_interrupt_config_t config)
  \brief Configures the selected TIMER interrupt
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] match       TIMER match select
  \param[in] config      TIMER interrupt configuration
  */
void lierdaEC_TIMER_InterruptConfig(uint32_t instance, timer_match_select_t match, timer_interrupt_config_t config);

/**
  \fn    timer_interrupt_config_t lierdaEC_TIMER_GetInterruptConfig(uint32_t instance, timer_match_select_t match)
  \brief Gets current configuration of the selected TIMER interrupt
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] match       TIMER match select
  \return                Current TIMER interrupt configuration
  */
timer_interrupt_config_t lierdaEC_TIMER_GetInterruptConfig(uint32_t instance, timer_match_select_t match);

/**
  \fn    uint32_t lierdaEC_TIMER_GetInterruptFlags(uint32_t instance, timer_interrupt_flags_t irp_flag)
  \brief Reads TIMER interrupt status flags
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] irp_flag    TIMER interrupt flags 
  \return    Interrupt flags. This is the logical OR of members of the
             enumeration \ref timer_interrupt_flags_t
 */
uint32_t lierdaEC_TIMER_GetInterruptFlags(uint32_t instance, timer_interrupt_flags_t irp_flag);

/**
  \fn    void lierdaEC_TIMER_ClearInterruptFlags(uint32_t instance, timer_interrupt_flags_t irp_flag)
  \brief Clears TIMER interrupt flags
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] irp_flag    TIMER Interrupt flags to clear. This is a logic OR of members of the
                         enumeration \ref timer_interrupt_flags_t
 */
void lierdaEC_TIMER_ClearInterruptFlags(uint32_t instance, timer_interrupt_flags_t irp_flag);

/**
  \fn    void lierdaEC_TIMER_Start(uint32_t instance)
  \brief Starts TIMER counter
  \param[in] instance    TIMER instance number (0, 1, ...)
 */
void lierdaEC_TIMER_Start(uint32_t instance);



#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_TIMER_PWM_H */
