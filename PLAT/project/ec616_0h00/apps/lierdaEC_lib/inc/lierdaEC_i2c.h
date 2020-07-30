/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_i2c.h
 * Description:  API interface implementation header file for I2C driver
 * History:      Rev1.0   2020-05-07
 *
 ****************************************************************************/
#ifndef LIERDAEC_I2C_H
#define LIERDAEC_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Driver_Common.h"


/******************************************************************************
 * lierdaEC_i2c_init
 * Description: initialize i2c interface. 
 * input:   bus_speed -> i2c bus speed  
 * Comment:
 * Return :
******************************************************************************/
int8_t lierdaEC_i2c_init(uint32_t bus_speed);

/******************************************************************************
 * lierdaEC_i2c_read_reg
 * Description: Start receiving data as I2C Master.
 * input: driver_addr(mandatory) -> Slave driver address (7-bit or 10-bit) 
 *        register_addr(mandatory) -> Register address  
 *        data_len(mandatory) -> Number of data bytes to receive
 * output: data -> Pointer to buffer for data to receive from I2C Slave 
 * Comment:
******************************************************************************/
void lierdaEC_i2c_read_reg(uint32_t driver_addr, uint8_t register_addr, uint8_t *data, uint32_t data_len);

/******************************************************************************
 * lierdaEC_i2c_read_reg
 * Description: Start transmitting data as I2C Master.
 * input: driver_addr(mandatory) -> Slave driver address (7-bit or 10-bit) 
 *        register_addr(mandatory) -> Register address  
 *        value(mandatory) -> Value with data to transmit to I2C Slave 
 * Comment:
******************************************************************************/
void lierdaEC_i2c_write_reg(uint32_t driver_addr, uint8_t register_addr, uint16_t value);

/******************************************************************************
 * lierdaEC_i2c_uninit
 * Description: un-initialize i2c interface   
 * Comment:
******************************************************************************/
int8_t lierdaEC_i2c_uninit(void);

#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_I2C_H */
