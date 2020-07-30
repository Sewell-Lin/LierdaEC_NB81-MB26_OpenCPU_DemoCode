/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_ctiot.h
 * Description:  API interface implementation header file for CTIOT driver
 * History:      Rev1.0   2020-06-05
 *
 ****************************************************************************/
#ifndef LIERDAEC_CTIOT_H
#define LIERDAEC_CTIOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ctiot_lwm2m_sdk.h"
#include "ec_ctlwm2m_api.h"


/******************************************************************************
 * lierdaEC_ct_task_init
 * Description: initialize ctiot task      
 * Comment:
******************************************************************************/
void lierdaEC_ct_task_init(void);

/******************************************************************************
 * lierdaEC_ctiot_recv_queue_init
 * Description: create receive queue     
 * Comment:
******************************************************************************/
void lierdaEC_ctiot_recv_queue_init(void);

/******************************************************************************
 * lierdaEC_ctiot_data_receive
 * Description: Receive data message queue
 * input: CTDataPtr(mandatory) -> the data which need receive, 
 *        CTDataLen(mandatory) -> data length   
 *        WaitTimeOut(mandatory) -> the timeout time of the receiving message queue    
 *                                0xffffffff : Wait forever... 
 * Comment:
******************************************************************************/
void lierdaEC_ctiot_data_receive(uint8_t *CTDataPtr, uint16_t *CTDataLen, uint32_t WaitTimeOut);

/******************************************************************************
 * lierdaEC_ctiot_data_send
 * Description: Send data to CTIoT platform
 * input: data(mandatory) -> the data which need send
 *        dataLen(mandatory) -> data length   
 *        sendMode(mandatory) -> send message mode, CON or NON mode
 *        seqNum(mandatory) ->  0 ~ 255, default 0
 *        isHex(mandatory) -> 0 means the incoming hex string, 
 *                            1 means the incoming hex array or pointer (the program will automatically convert the hex data to hex string)
 * Comment:
 * Return : receiving data
******************************************************************************/
uint16_t lierdaEC_ctiot_data_send(uint8_t *data, uint16_t dataLen, ctiot_funcv1_send_mode_e sendMode, uint8_t seqNum, uint8_t isHex);

/******************************************************************************
 * lierdaEC_usart_close
 * Description: close ctiot receive      
 * Comment:
******************************************************************************/
void lierdaEC_ctiot_recv_queue_close(void);

#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_CTIOT_H */
