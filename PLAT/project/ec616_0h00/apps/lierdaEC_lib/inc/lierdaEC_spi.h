/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_spi.h
 * Description:  API interface implementation header file for SPI driver
 * History:      Rev1.0   2020-05-12
 *
 ****************************************************************************/
#ifndef LIERDAEC_SPI_H
#define LIERDAEC_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Driver_Common.h"
#include "Driver_SPI.h"
#include "RTE_Device.h"

/** The SPI Chip Select (/CS) pin enables and disables device operation. 
 *  When /CS is brought low the device will beselected. (GPIO16) */
#define  SPI0_SSN_GPIO_PORT  RTE_SPI0_SSN_GPIO_INSTANCE
#define  SPI0_SSN_GPIO_PIN   RTE_SPI0_SSN_GPIO_INDEX

/** SPI mode, master or slave */
typedef enum
{
    SPI_MODE_MASTER = ARM_SPI_MODE_MASTER,
    SPI_MODE_SLAVE  = ARM_SPI_MODE_SLAVE,
}SPI_MODE; 

/** Clock Polarity , Clock Phase */
typedef enum
{
    SPI_CPOL0_CPHA0 = ARM_SPI_CPOL0_CPHA0,
    SPI_CPOL0_CPHA1 = ARM_SPI_CPOL0_CPHA1,
    SPI_CPOL1_CPHA0 = ARM_SPI_CPOL1_CPHA0,
    SPI_CPOL1_CPHA1 = ARM_SPI_CPOL1_CPHA1,
}SPI_CLOCK_POL_PHA;

/** SPI data width */
typedef enum
{
    SPI_DATA_WIDTH_8  = 8,   // 8  bits  
    SPI_DATA_WIDTH_16 = 16,  // 16 bits
}SPI_DATA_WIDTH;

/** SPI bit transion direction */
typedef enum
{
    SPI_MSB_LSB = ARM_SPI_MSB_LSB,
    SPI_LSB_MSB = ARM_SPI_LSB_MSB,
}SPI_BIT_TRANS_DIRECTION;   

typedef struct 
{
    UINT32             bps_speed;
    SPI_MODE           spi_mode;
    SPI_CLOCK_POL_PHA  clock_pol_pha;
    SPI_DATA_WIDTH     data_width;
    SPI_BIT_TRANS_DIRECTION  bit_trans_direction;
}SPI_HandleTypeDef;


/******************************************************************************
 * lierdaEC_spi_init
 * Description: initialize spi interface. 
 * input:     
 * Comment:
 * Return :  error code (0, success;  not 0, fail)
******************************************************************************/
int32_t lierdaEC_spi_init(SPI_HandleTypeDef *spi_handle);

/******************************************************************************
 * lierdaEC_spi_uninit
 * Description: un-initialize spi interface.
 * Comment:
 * Return :  error code (0, success;  not 0, fail)
******************************************************************************/
int32_t lierdaEC_spi_uninit(void);

/******************************************************************************
 * lierdaEC_spi_write_byte
 * Description: Start sending data to SPI transmitter.
 * input: data(mandatory) -> sending data
 * Comment:
******************************************************************************/
void lierdaEC_spi_write_byte(uint8_t data);

/******************************************************************************
 * lierdaEC_spi_read_byte
 * Description: Start receiving data from SPI receiver.
 * Comment:
 * Return : receiving data
******************************************************************************/
uint8_t lierdaEC_spi_read_byte(void);

/******************************************************************************
 * lierdaEC_spi_read_write_byte
 * Description: sending data to SPI transmitter, receiving data from SPI receiver.
 * input: TxData(mandatory) -> sending data
 * Comment:
 * Return : receiving data
******************************************************************************/
uint8_t lierdaEC_spi_read_write_byte(uint8_t TxData);

#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_SPI_H */

