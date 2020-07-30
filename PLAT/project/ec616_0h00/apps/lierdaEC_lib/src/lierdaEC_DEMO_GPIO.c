/******************************************************************************
 * File Name:        lierdaEC_DEMO_GPIO.c
 * 
 * Content:	         GPIO related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200515
*****************************************************************************/

#include "demo_app.h"

/** \brief BUTTON press count, LED is toggled on each button's press */
static volatile int ButtonInterruptCount = 0;

void GPIO_ISR_Func();
void lierdaEC_GPIO_Test(void);
void lierdaEC_GPIO_INIT(void);

/**
  \fn          void GPIO_ISR_Func()
  \brief       GPIO interrupt service routine
  \return
*/
void GPIO_ISR_Func()
{
    if (lierdaEC_GPIO_GetInterruptFlags(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN))
    {
        ButtonInterruptCount++;
        lierdaEC_GPIO_ClearInterruptFlags(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN);
    }
}

void lierdaEC_GPIO_INIT(void)
{
    // PAD mux function select
    pad_config_t padConfig;
    lierdaEC_PAD_GetDefaultConfig(&padConfig);

    padConfig.mux = BUTTON_PAD_MUX_ALT;
    lierdaEC_PAD_SetPinConfig(BUTTON_PAD_PADDR, &padConfig);
    lierdaEC_PAD_SetPinPullConfig(BUTTON_PAD_PADDR, PAD_InternalPullUp);

    padConfig.mux = LED_PAD_MUX_ALT;
    lierdaEC_PAD_SetPinConfig(LED_PAD_PADDR, &padConfig);

    // LED pin config
    gpio_pin_config_t config;
    config.pinDirection = GPIO_DirectionOutput;
    config.misc.initOutput = 1;
    lierdaEC_GPIO_PinConfig(LED_GPIO_PORT, LED_GPIO_PIN, &config);

    // Button pin config
    config.pinDirection = GPIO_DirectionInput;
    config.misc.interruptConfig = GPIO_InterruptRisingEdge;
    lierdaEC_GPIO_PinConfig(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN, &config);

    // Set ISR function
    lierdaEC_XIC_SetVector(PXIC_Gpio_IRQn, GPIO_ISR_Func);
    // Enable IRQ
    lierdaEC_XIC_EnableIRQ(PXIC_Gpio_IRQn);
}

void lierdaEC_GPIO_Test(void)
{
    if (ButtonInterruptCount & 0x1)
    {
        lierdaEC_GPIO_PinWrite(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_HIGH);
    }
    // lierdaEC_GPIO_PinRead(LED_GPIO_PORT, LED_GPIO_PIN);
    else
    {
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_GPIO_Test_1, P_INFO, 0, "---------DBG_INFO : lierdaEC DEMO GPIO Test---------");
        lierdaEC_GPIO_PinWrite(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_LOW);
    }
}
