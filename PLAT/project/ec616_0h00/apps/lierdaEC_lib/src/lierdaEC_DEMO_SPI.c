/******************************************************************************
 * File Name:        lierdaEC_DEMO_SPI.c
 * 
 * Content:	         SPI related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200523
*****************************************************************************/

#include "demo_app.h"
/*****************************Read the status register of W25QXX************
BIT7  6   5   4   3   2   1   0
SPR   RV  TB BP2 BP1 BP0 WEL BUSY
SPR:Default 0, status register protection bit, used with WP
TB,BP2,BP1,BP0:FLASH area write protection setting
WEL:Write enable lock
BUSY:Busy flag bit (1, busy; 0, idle)
默认:0x00
*************************************************************************/
#if SPI_DEMO_TASK
uint32_t SPI_ReadID(void);
uint8_t W25QXX_ReadSR(void);
uint16_t W25QXX_ReadID(void);
void lierdaEC_SPI_Test(void);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);
static void lierdaEC_SPIDEMO_Init(void);
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void SPI_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
uint8_t Tx_Buffer[] = "lierda SPI Test";
uint8_t Rx_Buffer[BufferSize];

SPI_HandleTypeDef spi_handle_t;
/*******************************************************************************
 * Function Name  : W25QXX_ReadSR
 * Description    : SPI initialization
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
uint8_t W25QXX_ReadSR(void)
{
    uint8_t byte = 0;
    SPI_CS_ENABLE();                             //Enable device
    lierdaEC_spi_write_byte(W25X_ReadStatusReg); //Send read status register command
    byte = lierdaEC_spi_read_byte();             //Read a byte
    SPI_CS_DISABLE();                            //DISABLE CS
    return byte;
}

/*******************************************************************************
 * Function Name  : SPI_ReadID
 * Description    : Read SPI device ID
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
uint32_t SPI_ReadID(void)
{
    uint32_t Temp = 0;
    uint8_t idbuff[4] = {0};
    uint8_t cmd_JedecDeviceID = W25X_JedecDeviceID;
    SPI_CS_ENABLE();                            //Enable device
    lierdaEC_spi_write_byte(cmd_JedecDeviceID); //Send a byte of data "Device ID" command
    idbuff[0] = lierdaEC_spi_read_byte();       //Read a byte of data
    idbuff[1] = lierdaEC_spi_read_byte();       //Read a byte of data
    idbuff[2] = lierdaEC_spi_read_byte();       //Read a byte of data
    SPI_CS_DISABLE();                           //DISABLE CS
    Temp = (uint32_t)(idbuff[0] << 16) | (idbuff[1] << 8) | idbuff[2];
    return Temp;
}

/*******************************************************************************
 * Function Name  : W25QXX_ReadID
 * Description    : 
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
uint16_t W25QXX_ReadID(void)
{
    uint16_t Temp = 0;
    SPI_CS_ENABLE();
    lierdaEC_spi_write_byte(0x90); //Send read ID command
    lierdaEC_spi_write_byte(0x00);
    lierdaEC_spi_write_byte(0x00);
    lierdaEC_spi_write_byte(0x00);
    Temp |= lierdaEC_spi_read_byte() << 8;
    Temp |= lierdaEC_spi_read_byte();
    SPI_CS_DISABLE();
    return Temp;
}

/*******************************************************************************
 * Function Name  : lierdaEC_SPIDEMO_Init
 * Description    : 
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
static void lierdaEC_SPIDEMO_Init(void)
{
    spi_handle_t.bps_speed = 200000; // 200K bps
    spi_handle_t.spi_mode = SPI_MODE_MASTER;
    spi_handle_t.clock_pol_pha = SPI_CPOL1_CPHA1;
    spi_handle_t.data_width = SPI_DATA_WIDTH_8;
    spi_handle_t.bit_trans_direction = SPI_MSB_LSB;
    lierdaEC_spi_init(&spi_handle_t);
}

/*******************************************************************************
 * Function Name  : SPI_FLASH_WriteEnable
 * Description    : 
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
void SPI_FLASH_WriteEnable(void)
{
    uint8_t cmd_WriteEnable = W25X_WriteEnable;
    /* Select serial FLASH: CS low level */
    SPI_CS_ENABLE();
    /* Send command: write enable */
    lierdaEC_spi_write_byte(cmd_WriteEnable);
    /* Disable serial Flash: CS high */
    SPI_CS_DISABLE();
}

/*******************************************************************************
 * Function Name  : SPI_FLASH_WaitForWriteEnd
 * Description    : Wait for data to be written
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 * Note           ：Polls the status of the Write In Progress (WIP) flag in the FLASH's status register and loop until write opertaionhas completed.
 *******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
    uint8_t FLASH_Status = 0;
    uint8_t cmd_ReadStatusReg = W25X_ReadStatusReg;
    /* Select the FLASH: Chip Select low */
    SPI_CS_ENABLE();
    /* Send "Read Status Register" instruction */
    lierdaEC_spi_write_byte(cmd_ReadStatusReg);
    /* Loop as long as the memory is busy with a write cycle */
    do
    {
        /* Send a dummy byte to generate the clock needed by the FLASH
      and put the value of the status register in FLASH_Status variable */
        FLASH_Status = lierdaEC_spi_read_byte();
    } while ((FLASH_Status & WIP_Flag) == 1); /* Write in progress */
    /* Deselect the FLASH: Chip Select high */
    SPI_CS_DISABLE();
}

/*******************************************************************************
 * Function Name  : SPI_FLASH_SectorErase
 * Description    : Erase sector
 * Input          : SectorAddr：Sector address to be erased, required to be a multiple of 4096
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 *******************************************************************************/
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
    uint8_t setaddr[4] = {0};
    uint8_t cmd_SectorErase = W25X_SectorErase;
    setaddr[0] = (SectorAddr & 0xFF0000) >> 16;
    setaddr[1] = (SectorAddr & 0xFF00) >> 8;
    setaddr[2] = SectorAddr & 0xFF;
    /* Send FLASH write enable command */
    SPI_FLASH_WriteEnable();
    SPI_FLASH_WaitForWriteEnd();
    /* Erase sector */
    /* Select serial FLASH: CS low level */
    SPI_CS_ENABLE();
    /* Send sector erase command*/
    lierdaEC_spi_write_byte(cmd_SectorErase);
    /* Send the high-order bit of the erased sector address */
    lierdaEC_spi_write_byte(setaddr[0]);
    /* Send the median of the erased sector address */
    lierdaEC_spi_write_byte(setaddr[1]);
    /* Send the low bit of the erased sector address */
    lierdaEC_spi_write_byte(setaddr[2]);
    /* Disable serial FLASH: CS high */
    SPI_CS_DISABLE();
    /* Wait for erasure to finish */
    SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
 * Function Name  : SPI_FLASH_SectorErase
 * Description    : Write data to serial FLASH page by page, you need to erase the sector before calling this function to write data
 * Input          : pBuffer：Pointer to data to be written
 *                  WriteAddr：Write address
 *                  NumByteToWrite：Write data length, must be less than or equal to SPI_FLASH_PerWritePageSize
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 * Serial Flash has a size of 256 bytes per page
 *******************************************************************************/
void SPI_FLASH_PageWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t writaddr[5] = {0};
    uint8_t cmd_PageProgram = W25X_PageProgram;
    writaddr[0] = cmd_PageProgram;
    writaddr[1] = (WriteAddr & 0xFF0000) >> 16;
    writaddr[2] = (WriteAddr & 0xFF00) >> 8;
    writaddr[3] = WriteAddr & 0xFF;
    /* 发送FLASH写使能命令 */
    SPI_FLASH_WriteEnable();
    /* 寻找串行FLASH: CS低电平 */
    SPI_CS_ENABLE();
    /* 写送写指令*/
    lierdaEC_spi_write_byte(cmd_PageProgram);
    /*发送写地址的高位*/
    lierdaEC_spi_write_byte(writaddr[1]);
    /*发送写地址的中位*/
    lierdaEC_spi_write_byte(writaddr[2]);
    /*发送写地址的低位*/
    lierdaEC_spi_write_byte(writaddr[3]);
    if (NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
    }

    /* 写入数据*/
    while (NumByteToWrite--)
    {
        /* 发送当前要写入的字节数据 */
        lierdaEC_spi_write_byte(*pBuffer);
        /* 指向下一字节数据 */
        pBuffer++;
    }
    /* 禁用串行FLASH: CS 高电平 */
    SPI_CS_DISABLE();
    /* 等待写入完毕*/
    SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
 * Function Name  : SPI_FLASH_BufferWrite
 * Description    : Write data to serial FLASH, you need to erase the sector before calling this function to write data
 * Input          : Buffer：Pointer to data to be written
 *                  WriteAddr：Write address
 *                  NumByteToWrite：Write data length, must be less than or equal to SPI_FLASH_PerWritePageSize
 * Output         : None
 * History        : 1.Create--SewellLin--200501
 * Note           ：This function can set any write data length
 *******************************************************************************/
void SPI_FLASH_BufferWrite(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % SPI_FLASH_PageSize;
    count = SPI_FLASH_PageSize - Addr;
    NumOfPage = NumByteToWrite / SPI_FLASH_PageSize;
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    if (Addr == 0) /* 若地址与 SPI_FLASH_PageSize 对齐  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
        {
            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr += SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /* 若地址与 SPI_FLASH_PageSize 不对齐 */
    {
        if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
        {
            if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
            {
                temp = NumOfSingle - count;

                SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;

                SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
            }
            else
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            NumByteToWrite -= count;
            NumOfPage = NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
            WriteAddr += count;
            pBuffer += count;

            while (NumOfPage--)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr += SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            if (NumOfSingle != 0)
            {
                SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/*******************************************************************************
 * Function Name  : SPI_FLASH_BufferRead
 * Description    : Read data from serial flash
 * Input          : pBuffer：Store pointer to read data
 *                  ReadAddr：Read data target address
 *                  NumByteToRead：Read data length
 * Output         : None
 * History        : 1.Create--SewellLin--200502
 * Note           : This function can set any read data length
 *******************************************************************************/
void SPI_FLASH_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t READADDE[5] = {0};
    uint8_t cmd_ReadData = W25X_ReadData;
    READADDE[0] = cmd_ReadData;
    READADDE[1] = (ReadAddr & 0xFF0000) >> 16;
    READADDE[2] = (ReadAddr & 0xFF00) >> 8;
    READADDE[3] = ReadAddr & 0xFF;
    /* Select serial FLASH: CS low level */
    SPI_CS_ENABLE();

    /* Send read command */
    lierdaEC_spi_write_byte(cmd_ReadData);
    /* Send read address high */
    lierdaEC_spi_write_byte(READADDE[1]);
    /* Send read address median */
    lierdaEC_spi_write_byte(READADDE[2]);
    /* Send Read Address Low */
    lierdaEC_spi_write_byte(READADDE[3]);

    while (NumByteToRead--) /* Read data */
    {
        /* Read a byte*/
        *pBuffer = lierdaEC_spi_read_byte();
        /* Point to the next byte buffer */
        pBuffer++;
    }

    /* Disable serial FLASH: CS high */
    SPI_CS_DISABLE();
}

/*******************************************************************************
 * Function Name  : lierdaEC_SPI_Test
 * Description    : SPI Demo Test
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200502
 *******************************************************************************/
void lierdaEC_SPI_Test(void)
{
    uint32_t ID = 0;
    uint16_t dev_id = 0;
    uint8_t status = 0;
    lierdaEC_SPIDEMO_Init();
    ID = 0;
    ID = SPI_ReadID(); // 0xc22018
    delay_us(100);
    dev_id = 0;
    dev_id = W25QXX_ReadID(); // 0xC213
    delay_us(100);
    status = 0;
    status = W25QXX_ReadSR();
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_SPI_Test_1, P_INFO, 1, "DBG_INFO : SPI Read ID = 0x%x ---", ID);
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_SPI_Test_2, P_INFO, 1, "-----SPI_test: REMS id = 0x%4x -----", dev_id);
    ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_SPI_Test_3, P_INFO, 1, "-----SPI_test: RDSR status = 0x%2x -----", status);
    if (ID == 0xc22018)
    {
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_SPI_Test_4, P_INFO, 1, "DBG_INFO : SFLASH_ReadID: = 0x%x", ID);
        SPI_FLASH_SectorErase(FLASH_SectorToErase);
        /* Write the data in the send buffer to flash */
        SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
        ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_SPI_Test_5, P_INFO, "DBG_INFO : The data written is = %s", Tx_Buffer);
        /* Read the data just written and put it in the receive buffer */
        SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
        ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_SPI_Test_6, P_INFO, "DBG_INFO : The data read is = %s", Rx_Buffer);
    }
    else
    {
        ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_SPI_Test_7, P_INFO, 1, "---Flash not recognized: RDID id = 0x%x ---", ID);
    }
    osDelay(3000);
}
#endif
