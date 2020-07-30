/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_ic_xic_irq.h
 * Description:  API interface implementation header file for XIC IRQ driver.
 * History:      Rev1.0   2020-04-17
 *
 ****************************************************************************/
#ifndef  LIERDAEC_IC_XIC_IRQ_H
#define  LIERDAEC_IC_XIC_IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ic_ec616.h"


/**
  \fn        void lierdaEC_XIC_SetVector(IRQn_Type IRQn, ISRFunc_T vector)
  \brief     Sets an XIC interrupt vector in SRAM based interrupt vector table.
             Use this function to bind the XIC interrupt and application ISR.
  \param[in] IRQn    Interrupt number
  \param[in] vector  Address of interrupt handler function
  \note      The interrupt number must be positive
 */
void lierdaEC_XIC_SetVector(IRQn_Type IRQn, ISRFunc_T vector);

/**
  \fn        void lierdaEC_XIC_EnableIRQ(IRQn_Type IRQn)
  \brief     Enables a device specific interrupt in the XIC interrupt controller.
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void lierdaEC_XIC_EnableIRQ(IRQn_Type IRQn);

/**
  \fn        void lierdaEC_XIC_DisableIRQ(IRQn_Type IRQn)
  \brief     Disables a device specific interrupt in the XIC interrupt controller.
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void lierdaEC_XIC_DisableIRQ(IRQn_Type IRQn);


#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_IC_XIC_IRQ_H */
