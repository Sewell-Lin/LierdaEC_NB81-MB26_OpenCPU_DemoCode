/******************************************************************************
 * File Name:        lierdaEC_DEMO_ADC.c
 * 
 * Content:	         ADC related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200428
*****************************************************************************/
#include "demo_app.h"
UINT8 CT_RCV_Buff[216];     //Test buff length
UINT16 CT_RCV_Buff_LEN = 0; //USART data reception length
uint8_t sendbuffer[150] = {0};
uint8_t a[4] = "123";
extern uint8_t CTsendFlag; //Data transmission flag
extern CT_Send_DATA Send_DATA;

#define UPLINK_MAX_LENGTH 100
int8_t UplinkBuffer[UPLINK_MAX_LENGTH];

uint8_t testData1[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
/*******************************************************************************
 * Function Name  : lierdaEC_UPdata_Task
 * Description    : AT Command test function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200516
 *******************************************************************************/
void lierdaEC_UPdata_Task(void *arg)
{
    osDelay(500); //Wait for module initialization to complete
    for (;;)
    {

        if (CTsendFlag == 1) //Determine whether the network connection is successful and whether to send data
        {
            CT_Send_DATA I2C_SEND_Test;
            memset(UplinkBuffer, 0, sizeof(UplinkBuffer));
            sprintf(UplinkBuffer, "ADC:%d,Light:%d", I2C_SEND_Test.ADCDATA_To_IoTPlatform, I2C_SEND_Test.I2CDATA_To_IoTPlatform);
            ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UPdata_Task_11, P_INFO, 1, "Light : %d (lux)", I2C_SEND_Test.I2CDATA_To_IoTPlatform);
            lierdaEC_ctiot_data_send(testData1, sizeof(testData1), SENDMODE_CON_REL, 0, 1);
            lierdaEC_ctiot_data_send(UplinkBuffer, sizeof(UplinkBuffer), SENDMODE_CON_REL, 0, 1);
            ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UPdata_Task_2, P_INFO, 0, "SEND OK");
        }
        osDelay(10000);
    }
}

/*******************************************************************************
 * Function Name  : lierdaEC_AT_Test
 * Description    : AT Command test function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200516
 *******************************************************************************/
void lierdaEC_Downdata_Task(void *arg)
{
    lierdaEC_ctiot_recv_queue_init();
    for (;;)
    {
        lierdaEC_ctiot_data_receive(CT_RCV_Buff, &CT_RCV_Buff_LEN, WAIT_FOREVER);
        if (CT_RCV_Buff_LEN > 0)
        {
            ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_Downdata_Task_1, P_INFO, 1, "IoT_RECV: Lenth= %d", CT_RCV_Buff_LEN);
            ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_Downdata_Task_2, P_INFO, "IoT_RECV: %s", (const uint8_t *)&CT_RCV_Buff);
            memset(CT_RCV_Buff, 0, CT_RCV_Buff_LEN);
            CT_RCV_Buff_LEN = 0;
        }
        osDelay(1);
    }
}
