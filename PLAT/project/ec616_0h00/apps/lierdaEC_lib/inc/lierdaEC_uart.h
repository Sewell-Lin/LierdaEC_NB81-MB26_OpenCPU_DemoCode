/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_uart.h
 * Description:  API interface implementation header file for USART driver
 * History:      Rev1.0   2020-04-29
 *
 ****************************************************************************/
#ifndef LIERDAEC_UART_H
#define LIERDAEC_UART_H

#ifdef __cplusplus
extern "C" {
#endif


#include "Driver_USART.h"


/** Uart data bits available */
typedef enum
{
    UART_DATA_BITS_5         = ARM_USART_DATA_BITS_5, /*!< 5 Data bits */
    UART_DATA_BITS_6         = ARM_USART_DATA_BITS_6, /*!< 6 Data bits */
    UART_DATA_BITS_7         = ARM_USART_DATA_BITS_7, /*!< 7 Data bits */
    UART_DATA_BITS_8         = ARM_USART_DATA_BITS_8, /*!< 8 Data bits */
    UART_DATA_BITS_9         = ARM_USART_DATA_BITS_9, /*!< 9 Data bits */
} UART_DATA_BITS;

/** Uart parity modes available */
typedef enum
{
    UART_PARITY_NONE  = ARM_USART_PARITY_NONE, /*!< No parity enabled */
    UART_PARITY_ODD   = ARM_USART_PARITY_ODD,  /*!< Odd parity        */
    UART_PARITY_EVEN  = ARM_USART_PARITY_EVEN, /*!< Even parity       */
} UART_PARITY;

/** Uart stop bits modes available */
typedef enum
{
    UART_STOP_BITS_1 = ARM_USART_STOP_BITS_1, /*!< 1 Stop bit*/
    UART_STOP_BITS_2 = ARM_USART_STOP_BITS_2, /*!< 2 Stop bits */
} UART_STOP_BITS;

typedef struct
{
	UINT32 			baudrate;
	UART_DATA_BITS 	data_bits;
	UART_STOP_BITS  stop_bits;
	UART_PARITY  	parity;
}UART_HandleTypeDef;

/******************************************************************************
 * lierdaEC_usart_init
 * Description: initialize usart     
 * Comment:
******************************************************************************/
void lierdaEC_usart_init(UART_HandleTypeDef *usart_handle);

/******************************************************************************
 * lierdaEC_usart_receive_data
 * Description: Receive data message queue
 * input: UserDataPtr(mandatory) -> the data which need receive, 
 *        UserDataLen(mandatory) -> data length   
 *        WaitTimeOut(mandatory) -> the timeout time of the receiving message queue    
 *                                0xffffffff : Wait forever... 
 * Comment:
******************************************************************************/
void lierdaEC_usart_receive_data(UINT8 *UserDataPtr, UINT16 *UserDataLen, UINT32 WaitTimeOut);

/******************************************************************************
 * lierdaEC_usart_send_data
 * Description: send data by a usart
 * input: Sendbuff(mandatory) -> the data which need send, 
 *        Sendlen(mandatory) -> data length       
 * Comment:
******************************************************************************/
void lierdaEC_usart_send_data(UINT8 *Sendbuff, UINT16 Sendlen);

/******************************************************************************
 * lierdaEC_usart_close
 * Description: close usart     
 * Comment:
******************************************************************************/
void lierdaEC_usart_close(void);

#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_UART_H */
