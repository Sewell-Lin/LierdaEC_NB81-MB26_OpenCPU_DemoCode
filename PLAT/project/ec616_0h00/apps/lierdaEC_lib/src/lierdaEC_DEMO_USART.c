/******************************************************************************
 * File Name:        lierdaEC_DEMO_USART.c
 * 
 * Content:	         USART related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200515
*****************************************************************************/

#include "demo_app.h"

static void lierdaEC_USART_INIT(void);

UINT8 USART_RCV_Buff[512];     //Test buff length
UINT16 USART_RCV_Buff_LEN = 0; //USART data reception length
UART_HandleTypeDef Lusart_handle;

static void lierdaEC_USART_INIT(void)
{
    Lusart_handle.baudrate = 115200;
    Lusart_handle.data_bits = UART_DATA_BITS_8;
    Lusart_handle.parity = UART_PARITY_NONE;
    Lusart_handle.stop_bits = UART_STOP_BITS_1;
    lierdaEC_usart_init(&Lusart_handle);
}

/*******************************************************************************
 * Function Name  : lierdaEC_USART_Task
 * Description    : Usart task function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200426
 *******************************************************************************/
void lierdaEC_USART_Task(void *arg)
{
    osDelay(500);
    lierdaEC_USART_INIT(); //USART2 initialization
    for (;;)
    {
        lierdaEC_usart_receive_data(USART_RCV_Buff, &USART_RCV_Buff_LEN, WAIT_FOREVER); //USART data reception
        if (USART_RCV_Buff_LEN > 5)
        {
            ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_USART_Task_1, P_INFO, 1, "USART_RECV: Lenth= %d", USART_RCV_Buff_LEN);
            ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_USART_Task_2, P_INFO, "USART_RECV: %s", (const uint8_t *)&USART_RCV_Buff);
            lierdaEC_usart_send_data(USART_RCV_Buff, USART_RCV_Buff_LEN); //USART sending test
            memset(USART_RCV_Buff, 0, USART_RCV_Buff_LEN);
            USART_RCV_Buff_LEN = 0;
        }
        osDelay(1);
    }
}
