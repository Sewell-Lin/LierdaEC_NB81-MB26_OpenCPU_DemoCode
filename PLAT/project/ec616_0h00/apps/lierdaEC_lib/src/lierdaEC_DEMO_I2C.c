/******************************************************************************
 * File Name:        lierdaEC_DEMO_I2C.c
 * 
 * Content:	         I2C related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200519
*****************************************************************************/

#include "demo_app.h"
#if I2C_DEMO_TASK
void OPT3001_WriteReg(uint8_t addr, uint16_t value);
void OPT3001_Config(uint16_t configValue);
uint16_t OPT3001_ReadReg(uint8_t addr);
extern uint8_t CTsendFlag;     //Data transmission flag
extern CT_Send_DATA Send_DATA; //DATA send flag
UINT8 tempBuffer[REGISTER_LENGTH];
UINT8 ctsendbuffer[50] = {0};
UINT32 Lux = 0;

void lierdaEC_I2C_Test(void)
{
    osDelay(500); //Waiting for module initialization to complete
    uint16_t regVal, exponent, fraction, result;
    if (lierdaEC_i2c_init(ARM_I2C_BUS_SPEED_STANDARD) == ARM_DRIVER_OK)
    {
        // Check device id
        regVal = OPT3001_ReadReg(OPT3001_REG_DEVICE_ID);
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_I2C_Task_1, P_INFO, 1, "Device ID : 0x%x", regVal);
        OPT3001_Config(CONFIG_ENABLE_CONTINUOUS);
        regVal = OPT3001_ReadReg(OPT3001_REG_CONFIGURATION);
        if (regVal & CONFIG_CRF_Msk) // check if sensor data ready
        {
            ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_I2C_Task_2, P_INFO, 0, "DBG_INFO : I2C Sensor Data Ready");
        }
        else
        {
            do
            {
                ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_I2C_Task_3, P_INFO, 0, "DBG_INFO : Check I2C Sensor Data Ready?");
                regVal = OPT3001_ReadReg(OPT3001_REG_CONFIGURATION);
                osDelay(100);
            } while (!(regVal & CONFIG_CRF_Msk)); //Make sure the sensor is ready
        }
        // read result out
        fraction = 0;
        exponent = 0;
        result = 0;
        regVal = OPT3001_ReadReg(OPT3001_REG_RESULT);
        // convert result to LUX
        fraction = regVal & 0xFFF;
        exponent = 1 << (regVal >> 12);
        result = fraction * exponent / 100;
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_I2C_Task_4, P_INFO, 1, "Light : %d (lux)", result);
        if (CTsendFlag == 1) //Determine whether the network connection is successful and whether to send data
        {
            CT_Send_DATA I2C_DEND;
            I2C_DEND.I2CDATA_To_IoTPlatform = result;
            // CT_Send_DATA.I2CDATA_To_IoTPlatform = result;
        }
        osDelay(3000);
    }
}

void OPT3001_WriteReg(uint8_t addr, uint16_t value)
{
    lierdaEC_i2c_write_reg(OPT3001_DEVICE_ADDR, addr, value);
}

void OPT3001_Config(uint16_t configValue)
{
    OPT3001_WriteReg(OPT3001_REG_CONFIGURATION, configValue);
}

uint16_t OPT3001_ReadReg(uint8_t addr)
{
    uint8_t tempBuffer[REGISTER_LENGTH];
    lierdaEC_i2c_read_reg(OPT3001_DEVICE_ADDR, addr, tempBuffer, sizeof(tempBuffer));
    return (uint16_t)(tempBuffer[0] << 8 | tempBuffer[1]);
}
#endif
