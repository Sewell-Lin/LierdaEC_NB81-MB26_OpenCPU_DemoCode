/******************************************************************************
 * File Name:        lierdaEC_DEMO_AT.c
 * 
 * Content:	         AT command related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200428
*****************************************************************************/

#include "demo_app.h"
CHAR *AT_Test_ret = NULL;

/*******************************************************************************
 * Function Name  : lierdaEC_AT_Test
 * Description    : AT Command test function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200516
 *******************************************************************************/
void lierdaEC_AT_Test(void)
{
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_ATTest_1, P_INFO, 0, "---------DBG_INFO : lierdaEC DEMO AT Test---------");
    AT_Test_ret = lierdaECATCall(AT_OK_Q, 3000);
    osDelay(500);
    if (AT_Test_ret == NULL)
    {
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_ATTest_2, P_INFO, 0, "DBG_INFO : AT DEMO Test Return Null!!!");
    }
    else if (strstr(AT_Test_ret, "OK"))
    {
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_ATTest_3, P_INFO, 0, "DBG_INFO : AT DEMO Test Pass!!!");
    }
    else
    {
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_ATTest_4, P_INFO, 0, "DBG_INFO : AT DEMO Test Fail!!!");
    }
    return;
}
