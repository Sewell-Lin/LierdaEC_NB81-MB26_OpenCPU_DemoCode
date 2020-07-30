/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_tcpip.h
 * Description:  API interface implementation header file for socket/tcpip service
 * History:      Rev1.0   2020-04-10
 *
 ****************************************************************************/
#ifndef __LIERDAEC_TCPIP_H__
#define __LIERDAEC_TCPIP_H__

#include "ec_tcpip_api.h"


/******************************************************************************
 *****************************************************************************
 * FUNCTION
 *****************************************************************************
******************************************************************************/

/******************************************************************************
 * tcpip_RecvData_handler_t
 * Description: Pointer to callback function to receive data by a tcpip connection
 * input: socket(mandatory)
 *        dataRecv(mandatory) -> the data which need receive, hex raw data
 *        dataLen(mandatory) -> data length          
 * Comment:
******************************************************************************/
typedef void (*tcpip_RecvData_handler_t)(INT32 socket, UINT8 *dataRecv, UINT16 dataLen);

/******************************************************************************
 * lierdaEC_tcpip_RecvData_register_event_handler
 * Description: tcpip receive data related event registration
 * input: 
 *        callBack -> the tcpip receive data related event(tcpip_RecvData_handler_t) callback handler
 * Comment:
******************************************************************************/
void lierdaEC_tcpip_RecvData_register_event_handler(tcpip_RecvData_handler_t callback);

/******************************************************************************
 * lierdaEC_tcpip_RecvData_deregister_event_handler
 * Description: tcpip receive data related event deregistration
 * Comment:
******************************************************************************/
void lierdaEC_tcpip_RecvData_deregister_event_handler(void);

/******************************************************************************
 * lierdaEC_tcpip_Connection_Create
 * Description: create a tcpip connection
 * input: protocol(mandatory)  TCP or UDP type
 *        localPort(mandatory)  10240 < localPort < 60000
 *        destIp(mandatory)"183.100.1.123" or"2001::2"   
 *        destPort(mandatory)
 * return: >=0 socket, <0 fail
 * Comment:
******************************************************************************/
INT32 lierdaEC_tcpip_Connection_Create(TcpipConnectionProtocol protocol, UINT16 localPort, char *destIp, UINT16 destPort);

/******************************************************************************
 * lierdaEC_tcpip_Connection_Send
 * Description: send data by a tcpip connection
 * input: socket(mandatory)
 *        data(mandatory) -> the data which need send, hex raw data
 *        dataLen(mandatory) -> data length       
 *        sequence(option) -> the sequence number of the UL data. 1~255: a UL status event will be indicate with the socket event callback 0:no UL status event
 *        
 * return:< 0 fail;  > 0 send Len
 * Comment:
******************************************************************************/
INT32 lierdaEC_tcpip_Connection_Send(INT32 socket, UINT8 *data, UINT16 dataLen, UINT8 sequence);

/******************************************************************************
 * lierdaEC_tcpip_Connection_Close
 * Description: close a tcpip connection
 * input: socket(mandatory) 
 * return: < 0 fail
 * Comment: 
******************************************************************************/
INT32 lierdaEC_tcpip_Connection_Close(INT32 socket);

/******************************************************************************
 * lierdaEC_tcpip_Connection_Status_Get
 * Description: get a tcpip connection status
 * return: connection status
 * Comment: 
******************************************************************************/
TcpipConnectionStatus lierdaEC_tcpip_Connection_Status_Get(void);

#endif


