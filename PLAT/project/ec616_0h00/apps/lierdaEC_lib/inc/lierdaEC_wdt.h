/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_wdt.h
 * Description:  API interface implementation header file for WDT driver
 * History:      Rev1.0   2020-06-02
 *
 ****************************************************************************/
#ifndef LIERDAEC_WDT_H
#define LIERDAEC_WDT_H

#include "wdt_ec616.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  \fn    void lierdaEC_WDT_GetDefaultConfig(wdt_config_t *config)
  \brief Gets the WDT default configuartion.
         This function sets the configuration structure to default values as below:
  \code
         config->mode = WDT_InterruptOnlyMode;
         config->timeoutValue = 0xFFFF;
  \endcode
  \param[in] config      Pointer to WDT configuration structure
 */
void lierdaEC_WDT_GetDefaultConfig(wdt_config_t *config);

/**
  \fn    void lierdaEC_WDT_Init(const wdt_config_t *config)
  \brief Initialize WDT
  \param[in] config      Pointer to WDT configuration
 */
void lierdaEC_WDT_Init(const wdt_config_t *config);

/**
  \fn    void lierdaEC_WDT_DeInit(void)
  \brief Deinitialize WDT
 */
void lierdaEC_WDT_DeInit(void);

/**
  \fn    void lierdaEC_WDT_Kick(void)
  \brief Refreshes WDT counter
 */
void lierdaEC_WDT_Kick(void);

/**
  \fn    void lierdaEC_WDT_Start(void)
  \brief Starts WDT counter
 */
void lierdaEC_WDT_Start(void);

/**
  \fn    void lierdaEC_WDT_Stop(void)
  \brief Stops WDT counter
 */
void lierdaEC_WDT_Stop(void);

/**
  \fn    uint32_t lierdaEC_WDT_GetInterruptFlags(void)
  \brief Reads WDT interrupt status flags
  \return    Interrupt flags. This is the logical OR of members of the
             enumeration \ref wdt_interrupt_flags_t
 */
uint32_t lierdaEC_WDT_GetInterruptFlags(void);

/**
  \fn    void lierdaEC_WDT_ClearInterruptFlags(uint32_t mask)
  \brief Clears WDT interrupt flags
  \param[in] mask        Interrupt flags to clear. This is a logic OR of members of the
                         enumeration \ref wdt_interrupt_flags_t
 */
void lierdaEC_WDT_ClearInterruptFlags(uint32_t mask);

#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_WDT_H */
