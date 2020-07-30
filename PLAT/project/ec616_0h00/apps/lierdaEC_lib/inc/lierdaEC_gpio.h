/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_gpio.h
 * Description:  API interface implementation header file for GPIO driver.
 * History:      Rev1.0   2020-04-14
 *
 ****************************************************************************/
#ifndef  LIERDAEC_GPIO_H
#define  LIERDAEC_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lierdaEC_pad.h"
#include "gpio_ec616.h"
#include "lierdaEC_ic_xic_irq.h"

/**  GPIO pin output logic level */
typedef enum _gpio_pin_output_logic_level
{
    GPIO_PIN_LOW  = 0U,  /**< 0: corresponding pin output low-logic  level */
    GPIO_PIN_HIGH = 1U,  /**< 1: corresponding pin output high-logic level */
} gpio_pin_output_level_t;


/**
 * 查看芯片数据手册，管脚复用目录，用Pin Name的序号GPIOx除以16，商是port，余数是pin
  \fn    void lierdaEC_GPIO_PinConfig(uint32_t port, uint16_t pin, const gpio_pin_config_t *config)
  \brief Configure a GPIO pin
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \param[in] config  Pointer to GPIO pin configuration
 */
void lierdaEC_GPIO_PinConfig(uint32_t port, uint16_t pin, const gpio_pin_config_t *config);

/**
  \fn    void lierdaEC_GPIO_PinWrite(uint32_t port, uint16_t pin, gpio_pin_output_level_t pin_level)
  \brief Sets output level of multiple GPIO pins to logic 1 or 0
  \param[in] port        GPIO number (0, 1, ...)
  \param[in] pin         GPIO pin number
  \param[in] pin_level   GPIO pin output logic level.
          - GPIO_PIN_LOW:  corresponding pin output low-logic level.
          - GPIO_PIN_HIGH: corresponding pin output high-logic level.
 */
void lierdaEC_GPIO_PinWrite(uint32_t port, uint16_t pin, gpio_pin_output_level_t pin_level);

/**
  \fn    uint32_t lierdaEC_GPIO_PinRead(uint32_t port, uint16_t pin)
  \brief Reads current input value of GPIO specific pin
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \return            GPIO corresponding pin input level value.
 */
uint32_t lierdaEC_GPIO_PinRead(uint32_t port, uint16_t pin);

/**
  \fn    uint16_t lierdaEC_GPIO_GetInterruptFlags(uint32_t port, uint16_t pin)
  \brief Reads GPIO port interrupt status flags
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \return     current GPIO interrupt status flag
 */
uint16_t lierdaEC_GPIO_GetInterruptFlags(uint32_t port, uint16_t pin);

/**
  \fn    void lierdaEC_GPIO_ClearInterruptFlags(uint32_t port, uint16_t pin)
  \brief Clears multiple GPIO pin interrupt status flags
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
 */
void lierdaEC_GPIO_ClearInterruptFlags(uint32_t port, uint16_t pin);




#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_GPIO_H */
