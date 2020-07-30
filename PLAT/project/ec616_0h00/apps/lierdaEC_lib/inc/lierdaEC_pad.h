/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_pad.h
 * Description:  API interface implementation header file for PAD driver.
 * History:      Rev1.0   2020-04-17
 *
 ****************************************************************************/
#ifndef  LIERDAEC_PAD_H
#define  LIERDAEC_PAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pad_ec616.h"

/**
  \fn    void lierdaEC_PAD_GetDefaultConfig(pad_config_t *config)
  \brief Gets the PAD default configuartion
         This function sets the configuration structure to default values as below:
  \code
         config->mux = PAD_MuxAlt0;
         config->inputBufferEnable = PAD_InputBufferDisable;
         config->pullSelect = PAD_PullAuto;
         config->pullUpEnable = PAD_PullUpDisable;
         config->pullDownEnable = PAD_PullDownDisable;
  \endcode
  \param config Pointer to PAD configuration structure
 */
void lierdaEC_PAD_GetDefaultConfig(pad_config_t *config);

/**
  \fn    void lierdaEC_PAD_SetPinConfig(uint32_t paddr, const pad_config_t *config)
  \brief Sets the pad PCR register
  \param paddr       PAD paddr number
  \param config    Pointer to PAD configuration structure
 */
void lierdaEC_PAD_SetPinConfig(uint32_t paddr, const pad_config_t *config);

/**
  \fn    void lierdaEC_PAD_SetPinPullConfig(uint32_t paddr, pad_pull_config_t pull_config)
  \brief Configures pin's pull feature
  \param paddr  PAD paddr number
  \param pull_config  PAD pin pull configuration
 */
void lierdaEC_PAD_SetPinPullConfig(uint32_t paddr, pad_pull_config_t pull_config);


#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_PAD_H */
