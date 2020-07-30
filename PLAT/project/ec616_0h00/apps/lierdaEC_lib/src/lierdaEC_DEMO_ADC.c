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
extern uint8_t CTsendFlag; //DATA send flag
extern CT_Send_DATA Send_DATA;

/*******************************************************************************
 * Function Name  : lierdaEC_ADC_Init
 * Description    : ADC initialization function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200603
 *******************************************************************************/
void lierdaEC_ADC_Init(void)
{
    lierdaEC_ADC_ChannelInit(ADC_ChannelAio2); //ADC0 initialization
    lierdaEC_ADC_ChannelInit(ADC_ChannelAio4); //ADC1 initialization
    // lierdaEC_ADC_ChannelInit(ADC_ChannelThermal);
    // lierdaEC_ADC_ChannelInit(ADC_ChannelVbat);
}

/*******************************************************************************
 * Function Name  : lierdaEC_ADC_DeInit
 * Description    : ADC anti-initialization function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200603
 *******************************************************************************/
void lierdaEC_ADC_DeInit(void)
{
    lierdaEC_ADC_ChannelDeInit(ADC_ChannelAio2); //ADC0 Deinitialization
    lierdaEC_ADC_ChannelDeInit(ADC_ChannelAio4); //ADC1 Deinitialization
    // lierdaEC_ADC_ChannelDeInit(ADC_ChannelThermal);
    // lierdaEC_ADC_ChannelDeInit(ADC_ChannelVbat);
}

/*******************************************************************************
 * Function Name  : lierdaEC_ADC_Test
 * Description    : ADC test function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200603
 *******************************************************************************/
void lierdaEC_ADC_Test(void)
{
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_DEMO_ADC_1, P_INFO, 0, "---------DBG_INFO : lierdaEC DEMO ADC Test---------");
    int32_t Vbat = -1, ADC0 = -1, ADC1 = -1, ret_Temp = -1, Temp = -1;
    Vbat = lierdaEC_HAL_ADC_SampleVbatVoltage(2000);                                      //ADC sampling Vbat voltage (original ADC sampling value)
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_DEMO_ADC_2, P_INFO, 1, "ADC : Vbat = %d", Vbat); //Print ADC sampling Vbat voltage through Log (original ADC sampling value)
    /************************************************************************************************************************/
    /*************************** ADC sampling external voltage range:0-4.8V *************************************************/
    lierdaEC_ADC_Init();
    lierdaEC_ADC_GetCalibrateValue(ADC_ChannelAio2, &ADC0); //lierdaEC_ADC_GetCalibrateValue()-Need to initialize and de-initialize
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_DEMO_ADC_3, P_INFO, 1, "ADC0 = %dmV", ADC0);
    lierdaEC_ADC_GetCalibrateValue(ADC_ChannelAio4, &ADC1); //lierdaEC_ADC_GetCalibrateValue()-Need to initialize and de-initialize
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_DEMO_ADC_4, P_INFO, 1, "ADC1 = %dmV", ADC1);
    lierdaEC_ADC_DeInit();
    /************************************************************************************************************************/
    ret_Temp = lierdaEC_HAL_ADC_GetThermalTemperature(2000, &Temp);
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_DEMO_ADC_5, P_INFO, 3, "ret_Temp = %dmV, Temp = %d", ret_Temp, Temp);
    /********************************************* Transfer the data to the IOT platform ***********************************/
    if (CTsendFlag == 1) //Determine whether the network connection is successful and whether to send data
    {
        CT_Send_DATA ADC_DEND;
        ADC_DEND.ADCDATA_To_IoTPlatform = Vbat;
    }
}
