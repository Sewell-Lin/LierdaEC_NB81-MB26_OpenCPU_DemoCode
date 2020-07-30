/******************************************************************************
 * File Name:        demo_app.c
 * 
 * Content:	         demo_app related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200428
*****************************************************************************/
#include "demo_app.h"

/*Task handle*/
TaskHandle_t APP_TaskHandle = NULL;
TaskHandle_t TCPIP_TaskHandle = NULL;
TaskHandle_t USART_TaskHandle = NULL;
TaskHandle_t UPdata_TaskHandle = NULL;
TaskHandle_t Downdata_TaskHandle = NULL;
CHAR *Testbuffer = "Lierda NB81/MB26 Module";
extern uint8_t CTsendFlag; //DATA send flag
static void App_IPC_Created(void)
{
    ;
}

static void App_SoftTimer_Created(void)
{
    ;
}
/*******************************************************************************
 * Function Name  : App_Resource_Created
 * Description    : Resource creation
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
// 锟�?鍙傝€冪▼搴忔牸锟�?
void lierdaEC_app_main(void)
{
    App_IPC_Created();       // 杩涚▼闂撮€氫俊(娑堟伅闃熷垪锛屼俊鍙烽噺锟�?) 鍒涘缓
    App_SoftTimer_Created(); // 锟�?浠跺畾鏃跺櫒 鍒涘缓
    App_Task_Created();
}

/*******************************************************************************
 * Function Name  : App_Task_Created
 * Description    : Task creation function
 ******    IMPORTANT(The TASK priority of all App application levels must be less than or equal to osPriorityNormal (24), the smaller the label, the lower the priority.)
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
static void App_Task_Created(void)
{
    lierdaEC_ct_task_init();                                                                                       //Initialization of network access tasks
    xTaskCreate(lierdaEC_APP_Task, "APP_Task", 512, NULL, osPriorityBelowNormal6, &APP_TaskHandle);                //Main APP task
    xTaskCreate(lierdaEC_USART_Task, "USART_Task", 300, NULL, osPriorityBelowNormal6, &USART_TaskHandle);          //USART Task
    xTaskCreate(lierdaEC_UPdata_Task, "UPdata_Task", 300, NULL, osPriorityBelowNormal6, &UPdata_TaskHandle);       //Uplink data task
    xTaskCreate(lierdaEC_Downdata_Task, "Downdata_Task", 300, NULL, osPriorityBelowNormal6, &Downdata_TaskHandle); //Downlink data task
#if TCPIP_DEMO_TASK
    xTaskCreate(lierdaEC_TCPIP_Task, "UDP_TCP_Task", 300, NULL, osPriorityBelowNormal6, &TCPIP_TaskHandle); //TCPIP task
#endif
}

/*******************************************************************************
 * Function Name  : lierdaEC_APP_Task
 * Description    : Main task function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
void lierdaEC_APP_Task(void *arg)
{
    osDelay(500);                                                                                                                                    //Wait for module initialization to complete
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_APP_Task_1, P_INFO, 0, "-------------DBG_INFO : lierdaEC NB81/MB26 OpenCPU DEMO V1.0.200703-------------"); //Test log print function ECOMM_TRACE( ), display DEMO program version number
    ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_APP_Task_2, P_INFO, "DBG_INFO : My name is : %s", (const uint8_t *)Testbuffer);                            //Test log print function ECOMM_STRING( )
    lierdaEC_PWM_TIMER_INIT();
    lierdaEC_GPIO_INIT();
    for (;;)
    {
        lierdaEC_ADC_Test();       //ADC test function
        lierdaEC_AT_Test();        //AT test function
        lierdaEC_PWM_TIMER_Test(); //PWM & TIMER test function
        lierdaEC_GPIO_Test();      //GPIO test function
#if I2C_DEMO_TASK
        lierdaEC_I2C_Test(); //I2C test function
#endif
#if SPI_DEMO_TASK
        lierdaEC_SPI_Test(); //SPI test function
#endif
        LierdaEC_time_get_Test(); //Time acquisition test function test function
        osDelay(1000);
    }
}

/*******************************************************************************
 * Function Name  : LierdaEC_time_get_Test
 * Description    : Time acquisition function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200603
 *******************************************************************************/
void LierdaEC_time_get_Test(void)
{
    UTC_DATE_TIME_T *LierdaTimeGet = NULL;
    CHAR *timebuff = NULL;
    timebuff = (char *)malloc(50 * sizeof(char));
    LierdaTimeGet = (UTC_DATE_TIME_T *)malloc(sizeof(UTC_DATE_TIME_T));
    //Only after connecting to the Net
    if ((timebuff != NULL) && (LierdaTimeGet != NULL))
    {
        if (CTsendFlag == 1)
        {
            memset(LierdaTimeGet, 0, sizeof(UTC_DATE_TIME_T));
            if (lierdaEC_get_current_date_time(LierdaTimeGet, true) == 0)
            {
                sprintf(timebuff, "UTC Time : %02d/%02d/%02d %02d:%02d:%02d+%03d", LierdaTimeGet->year, LierdaTimeGet->month,
                        LierdaTimeGet->day, LierdaTimeGet->hour, LierdaTimeGet->minute, LierdaTimeGet->second, LierdaTimeGet->millisecond);
                ECOMM_STRING(UNILOG_PLA_APP, LierdaEC_time_get_Test_1, P_INFO, "%s", (const uint8_t *)timebuff);
            }
            osDelay(1000);
            memset(LierdaTimeGet, 0, sizeof(UTC_DATE_TIME_T));
            if (lierdaEC_get_current_date_time(LierdaTimeGet, false) == 0)
            {
                sprintf(timebuff, "Beijing Time : %02d/%02d/%02d %02d:%02d:%02d+%03d", LierdaTimeGet->year, LierdaTimeGet->month,
                        LierdaTimeGet->day, LierdaTimeGet->hour, LierdaTimeGet->minute, LierdaTimeGet->second, LierdaTimeGet->millisecond);
                ECOMM_STRING(UNILOG_PLA_APP, LierdaEC_time_get_Test_2, P_INFO, "%s", (const uint8_t *)timebuff);
            }
        }
    }
    else
    {
        ECOMM_TRACE(UNILOG_PLA_APP, LierdaEC_time_get_Test_3, P_INFO, 0, "Failed to get Beijing time : Waiting for network connection");
    }
    free(LierdaTimeGet);
    free(timebuff);
}
