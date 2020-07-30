/******************************************************************************
 * File Name:        lierdaEC_DEMO_Timer_PWM.c
 * 
 * Content:	         Timer_PWM related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200507
*****************************************************************************/

#include "stdio.h"
#include "lierdaEC_timer_pwm.h"
#include "lierdaEC_pad.h"
#include "lierdaEC_ic_xic_irq.h"
#include "debug_log.h"
/*
   This project demos PWM feature of TIMER, in this example, we'll use 2 instance of TIMER,
   one is used to output pwm, and its frequency is configure as 1KHz while duty cycle
   is controlled by another TIMER, the duty cycle is updated in interval of 5 from 0 to 100 periodically,
   the period is achieved with aid of another instance of timer whose interrupt is triggered every 500ms.
 */

/** \brief TIMER instance for PWM output */
#define PWM_INSTANCE (3) // TIMER3

/** \brief PWM clock id for clock configuration */
#define PWM_CLOCK_ID (GPR_TIMER3FuncClk)

/** \brief PWM clock source select */
#define PWM_CLOCK_SOURCE (GPR_TIMER3ClkSel_26M)

/** \brief PWM initial duty cycle percent */
#define PWM_INIT_DUTY_CYCLE_PERCENT (50)

/** \brief TIMER/PWM out pin (paddr) */
#define PWM_OUT_PAD_PADDR (14) // paddr = 14, GPIO3, PWM1, Alt Func5

/** \brief TIMER/PWM Alt function select */
#define PWM_OUT_PAD_MUX_ALT (PAD_MuxAlt5)

/** \brief TIMER instance for PWM duty cycle control */
#define TIMER_INSTANCE (1) // TIMER1

/** \brief TIMER clock id for clock configuration */
#define TIMER_CLOCK_ID (GPR_TIMER1FuncClk)

/** \brief TIMER clock source select */
#define TIMER_CLOCK_SOURCE (GPR_TIMER1ClkSel_32K)

/** \brief TIMER instance IRQ number */
#define TIMER_INSTANCE_IRQ (PXIC_Timer1_IRQn)
unsigned int dutyCycle = PWM_INIT_DUTY_CYCLE_PERCENT;
volatile static int update = 0;
void lierdaEC_PWM_TIMER_Test(void);
void lierdaEC_PWM_TIMER_INIT(void);

/**
  \fn          void Timer_ISR()
  \brief       Timer1 interrupt service routine
  \return
*/
void Timer_ISR()
{
    if (lierdaEC_TIMER_GetInterruptFlags(TIMER_INSTANCE, TIMER_Match0InterruptFlag))
    {
        update = 1;
        lierdaEC_TIMER_ClearInterruptFlags(TIMER_INSTANCE, TIMER_Match0InterruptFlag);
    }
}

void lierdaEC_PWM_TIMER_INIT(void)
{
    // PWM out pin config
    pad_config_t config;

    lierdaEC_PAD_GetDefaultConfig(&config);
    config.mux = PWM_OUT_PAD_MUX_ALT;
    lierdaEC_PAD_SetPinConfig(PWM_OUT_PAD_PADDR, &config);

    // Config PWM clock, source from 26MHz and divide by 1
    lierdaEC_CLOCK_SetClockSrc(PWM_CLOCK_ID, PWM_CLOCK_SOURCE);
    lierdaEC_CLOCK_SetClockDiv(PWM_CLOCK_ID, 1);

    lierdaEC_TIMER_DriverInit();

    timer_pwm_config_t pwmConfig;
    pwmConfig.pwmFreq_HZ = 1000;
    pwmConfig.srcClock_HZ = lierdaEC_GPR_GetClockFreq(PWM_CLOCK_ID); // 26MHz
    pwmConfig.dutyCyclePercent = PWM_INIT_DUTY_CYCLE_PERCENT;

    lierdaEC_TIMER_SetupPwm(PWM_INSTANCE, &pwmConfig);

    // TIMER config
    // Config TIMER clock, source from 32.768KHz and divide by 1
    lierdaEC_CLOCK_SetClockSrc(TIMER_CLOCK_ID, TIMER_CLOCK_SOURCE);
    lierdaEC_CLOCK_SetClockDiv(TIMER_CLOCK_ID, 1);

    // Config TIMER period as 500ms, match0 value is 16384 = 0x4000
    timer_config_t timerConfig;
    lierdaEC_TIMER_GetDefaultConfig(&timerConfig);
    timerConfig.reloadOption = TIMER_ReloadOnMatch0;
    timerConfig.match0 = 0x4000;

    lierdaEC_TIMER_Init(TIMER_INSTANCE, &timerConfig);

    lierdaEC_TIMER_InterruptConfig(TIMER_INSTANCE, TIMER_Match0Select, TIMER_InterruptLevel);
    lierdaEC_TIMER_InterruptConfig(TIMER_INSTANCE, TIMER_Match1Select, TIMER_InterruptDisabled);
    lierdaEC_TIMER_InterruptConfig(TIMER_INSTANCE, TIMER_Match2Select, TIMER_InterruptDisabled);

    // Enable TIMER IRQ
    lierdaEC_XIC_SetVector(TIMER_INSTANCE_IRQ, Timer_ISR);
    lierdaEC_XIC_EnableIRQ(TIMER_INSTANCE_IRQ);

    lierdaEC_TIMER_Start(PWM_INSTANCE);
    lierdaEC_TIMER_Start(TIMER_INSTANCE);
}

void lierdaEC_PWM_TIMER_Test(void)
{
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_PWM_TIMER_Test_1, P_INFO, 0, "---------DBG_INFO : lierdaEC DEMO TIMER PWM Test---------");
    if (update == 1)
    {
        update = 0;
        if (dutyCycle > 100)
            dutyCycle = 0;
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_PWM_TIMER_Test_2, P_INFO, 1, "TIMER_Test : dutyCycle = %d", dutyCycle);
        dutyCycle += 5;
        lierdaEC_TIMER_UpdatePwmDutyCycle(PWM_INSTANCE, dutyCycle);
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_PWM_TIMER_Test_3, P_INFO, 0, "DBG_INFO : lierdaEC DEMO TIMER PWM Test End.");
    }
}
