/******************************************************************************
 * File Name:        lierdaEC_DEMO_TCPIP.c
 * 
 * Content:	         TCPIP related test functions
 * 
 * Design:	         Lierda NB-IoT Software Development Team
 * 
 * Revision History: 1.Create   SewellLin   200507
*****************************************************************************/

#include "demo_app.h"

#if TCPIP_DEMO_TASK
void TCPIP_RecvData_CallBack(INT32 socket, UINT8 *dataRecv, UINT16 dataLen);
static void udp_create_queue(void);

CHAR *at_ret = NULL; //The string returned by the AT command
INT32 Connection_Create_ret = -1;
UINT8 udpTestData[150] = {0};
UINT8 udpTestDataHex[150] = {0};
UINT8 tcpTestData[150] = {0};
UINT8 tcpTestDataHex[150] = {0};
UINT8 TCPIPRecvBuff[TCPIP_RECV_BUFF_LEN];
UINT16 user_buff_len = 0;
QueueHandle_t udp_recv_queue = NULL;

typedef struct lierdaECDEMO
{
	UINT8 NetConnetFlag; //Network connection flag 0: Not connected 1: Successful connection
	INT32 UDPSocketID;	 //UDP SOCKET
	INT32 TCPSocketID;	 //TCP SOCKET
} lierdaECTCPIPDemoValue;
lierdaECTCPIPDemoValue lierdaECTCPIPDemoSysValue;

/*******************************************************************************
 * Function Name  : lierdaEC_NB_Network
 * Description    : NB attached network
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
uint32_t lierdaEC_NB_Network()
{
	uint32_t temp = 0;
	/* Check if the SIM card is ready*/
	for (temp = 0; temp < 5; temp++)
	{
		at_ret = lierdaECATCall(AT_SIM_Q, 3000);
		if (strstr(at_ret, "+CPIN: READY"))
		{
			ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_NB_NetWork_1, P_INFO, 0, "DBG_INFO : CPIN PASS!!!"); //Check CPIN
			break;
		}

		else
		{
			osDelay(10000); //delay waiting
		}
	}
	ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_NB_NetWork_2, P_INFO, "CPIN Return = %s", (const uint8_t *)at_ret);
	if (temp >= 5)
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_NB_NetWork_3, P_INFO, 0, "DBG_INFO : CPIN Return False!!!");
		return false;
	}
	/*Check CEREG*/
	for (temp = 0; temp < 5; temp++)
	{
		at_ret = lierdaECATCall(AT_CEGEG_Q, 3000);
		if (strstr(at_ret, "+CEREG: 0,1"))
		{
			ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_NB_NetWork_4, P_INFO, 0, "DBG_INFO : CEREG PASS!!!"); //Check CEREG
			break;
		}

		else
		{
			osDelay(10000); //delay waiting
		}
	}
	ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_NB_NetWork_5, P_INFO, "CEREG Return = %s", (const uint8_t *)at_ret);
	if (temp >= 5)
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_NB_NetWork_6, P_INFO, 0, "DBG_INFO : CEREG Return False!!!");
		return false;
	}
	/* Check whether it is assigned to the core network IP*/
	for (temp = 0; temp < 5; temp++)
	{
		at_ret = lierdaECATCall(AT_CGPADDR_Q, 3000);
		osDelay(1000);
		if (strstr(at_ret, "+CGPADDR:"))
		{
			lierdaECTCPIPDemoSysValue.NetConnetFlag = 1;												 //Network access success sign
			ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_NB_NetWork_7, P_INFO, 0, "DBG_INFO : CGPADDR PASS!!!"); //Check CGPADDR
			ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_NB_NetWork_8, P_INFO, "CGPADDR Return = %s", (const uint8_t *)at_ret);
			break;
		}
		else
		{
			osDelay(1000);
			ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_NB_NetWork_9, P_INFO, "CGPADDR Return = %s", (const uint8_t *)at_ret);
		}

		if (temp >= 5)
		{
			ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_NB_NetWork_10, P_INFO, 0, "DBG_INFO : CGPADDR Return False!!!");
			return false;
		}
	}
	return 1;
}

/*******************************************************************************
 * Function Name  : lierdaEC_UDP_Ready
 * Description    : UDP connection creation function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
uint32_t lierdaEC_UDP_Ready()
{
	uint32_t temp = 0;
	if (lierdaECTCPIPDemoSysValue.NetConnetFlag == 1) //Determine whether the network is successfully connected, and start to create SOCKET after the connection is successful
	{
		for (temp = 0; temp < 3; temp++)
		{
			Connection_Create_ret = lierdaEC_tcpip_Connection_Create(TCPIP_CONNECTION_PROTOCOL_UDP, 56660, UDP_Server_Add, UDP_Server_Port);
			ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_Ready_1, P_INFO, 1, "UDP Socket Create Success SocketID : %d", Connection_Create_ret);
			osDelay(3000);
			if (Connection_Create_ret >= 0)
			{
				lierdaECTCPIPDemoSysValue.UDPSocketID = Connection_Create_ret;
				break;
			}
			else
			{
				ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_Ready_2, P_INFO, 1, "Waiting For Creat Socket , SocketID : %d", Connection_Create_ret);
				osDelay(3000);
			}
			if (temp >= 3)
			{
				ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_Ready_3, P_INFO, 0, "DBG_INFO : Socket Creat Fail!!!");
				return false;
			}
		}
	}
	else
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_Ready_4, P_INFO, 0, "DBG_INFO : NB NET Disconnect!!!");
		return false;
	}
}

/*******************************************************************************
 * Function Name  : lierdaEC_TCP_Ready
 * Description    : TCP connection creation function
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
uint32_t lierdaEC_TCP_Ready()
{

	uint32_t temp = 0;
	if (lierdaECTCPIPDemoSysValue.NetConnetFlag == 1) //Determine whether the network is successfully connected, and start to create SOCKET after the connection is successful
	{
		for (temp = 0; temp < 3; temp++)
		{
			Connection_Create_ret = lierdaEC_tcpip_Connection_Create(TCPIP_CONNECTION_PROTOCOL_TCP, LocalPort, TCP_Server_Add, TCP_Server_Port);
			ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_TCP_Ready_1, P_INFO, 1, "TCP Socket Create Success SocketID : %d", Connection_Create_ret);
			osDelay(3000);
			if (Connection_Create_ret >= 0)
			{
				lierdaECTCPIPDemoSysValue.TCPSocketID = Connection_Create_ret;
				break;
			}
			else
			{
				ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_TCP_Ready_2, P_INFO, 1, "Waiting For Creat Socket,SocketID : %d", Connection_Create_ret);
				osDelay(3000);
			}
			if (temp >= 3)
			{
				ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_TCP_Ready_3, P_INFO, 0, "DBG_INFO : Socket Creat Fail!!!");
				return false;
			}
		}
	}
	else
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_TCP_Ready_4, P_INFO, 0, "DBG_INFO : NB NET Disconnect!!!");
		return false;
	}
}

/*******************************************************************************
 * Function Name  : udpDataSendTest
 * Description    : UDP data sending test
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
void udpDataSendTest(void)
{
	INT8 UDP_SENDLEN = -1;
	INT8 UDP_SENDHexLEN = 0;
	memcpy((char *)udpTestData, (char *)UDPTESTDATA, strlen((char *)UDPTESTDATA));
	ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_udpDataSendTest_1, P_INFO, "UDP SendTest Data : %s", (const uint8_t *)udpTestData);
	UDP_SENDLEN = strlen(udpTestData);
	UDP_SENDHexLEN = UDP_SENDLEN / 2;
	cmsHexStrToHex(udpTestDataHex, UDP_SENDHexLEN, udpTestData, UDP_SENDLEN); //Send data needs to be converted to hexadecimal
	UDP_SENDLEN = lierdaEC_tcpip_Connection_Send(lierdaECTCPIPDemoSysValue.UDPSocketID, udpTestDataHex, UDP_SENDHexLEN, 0);
	if (UDP_SENDLEN > 0)
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_udpDataSendTest_2, P_INFO, 1, "UDP Send Success,SendMsg Len : %d", UDP_SENDLEN);
	}
	else
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_udpDataSendTest_3, P_INFO, 0, "DBG_INFO : UDP Send Fail!!!");
	}
}

/*******************************************************************************
 * Function Name  : tcpFirstDataSendTest
 * Description    : TCP send data function for the first time
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
void tcpFirstDataSendTest(void)
{
	INT8 TCP_SENDLEN = -1;
	INT8 TCP_SENDHexLEN = 0;
	memcpy((char *)tcpTestData, (char *)TCPFIRSTTESTDATA, strlen((char *)TCPFIRSTTESTDATA));
	ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_tcpDataSendTest_1, P_INFO, "TCP SendTest Data : %s", (const uint8_t *)tcpTestData);
	TCP_SENDLEN = strlen(tcpTestData);
	TCP_SENDHexLEN = TCP_SENDLEN / 2;
	cmsHexStrToHex(tcpTestDataHex, TCP_SENDHexLEN, tcpTestData, TCP_SENDLEN); //Send data needs to be converted to hexadecimal
	TCP_SENDLEN = lierdaEC_tcpip_Connection_Send(lierdaECTCPIPDemoSysValue.TCPSocketID, tcpTestDataHex, TCP_SENDHexLEN, 0);
	if (TCP_SENDLEN > 0)
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_tcpDataSendTest_2, P_INFO, 1, "TCP First Send Success , SendMsg Len : %d", TCP_SENDLEN);
	}
	else
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_tcpDataSendTest_3, P_INFO, 0, "DBG_INFO : TCP First Send Fail!!!");
	}
}

/*******************************************************************************
 * Function Name  : lierdaEC_TCPIP_Task
 * Description    : UDP/TCP task thread
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
void lierdaEC_TCPIP_Task(void *arg)
{
	INT8 RETCP_SENDLEN = -1;
	osDelay(500);															 //Wait for module initialization to complete
	lierdaECTCPIPDemoSysValue.UDPSocketID = -1;								 //Assign initial value
	lierdaECTCPIPDemoSysValue.TCPSocketID = -1;								 //Assign initial value
	udp_create_queue();														 //Create queue
	lierdaEC_tcpip_RecvData_register_event_handler(TCPIP_RecvData_CallBack); //Register callback function
	if (lierdaEC_NB_Network() == false)
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_1, P_INFO, 0, "DBG_INFO : NB_NetWork False!!!");
		osDelay(2000);
	}
	else
	{
		if (Select_UDP_TCP > 0) //UDP Select_UDP_TCP=1 ;TCP Select_UDP_TCP=-1
		{
			if ((lierdaEC_tcpip_Connection_Status_Get() == TCPIP_CONNECTION_STATUS_CONNECTED) && lierdaECTCPIPDemoSysValue.UDPSocketID > 0)
			{
				udpDataSendTest();
				osDelay(2000);
			}
			else if ((lierdaEC_tcpip_Connection_Status_Get() == TCPIP_CONNECTION_STATUS_CONNECTED) && lierdaECTCPIPDemoSysValue.TCPSocketID > 0)
			{
				tcpFirstDataSendTest();
				osDelay(2000);
			}
			else
			{
				ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_2, P_INFO, 0, "DBG_INFO : lierdaEC UDP Not Ready!!!");
				lierdaEC_UDP_Ready();
				if (lierdaECTCPIPDemoSysValue.UDPSocketID > 0)
				{
					udpDataSendTest();
				}
				else
				{
					lierdaEC_UDP_Ready();
					//If socketID<0 is detected, the socket is not created successfully, to create socketID
				}
			}
		}

		if (Select_UDP_TCP < 0) //UDP Select_UDP_TCP = 1 ; TCP Select_UDP_TCP = -1 .
		{
			if (lierdaEC_tcpip_Connection_Status_Get() == TCPIP_CONNECTION_STATUS_CONNECTED)
			{
				tcpFirstDataSendTest();
			}
			else
			{
				ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_3, P_INFO, 0, "DBG_INFO : lierdaEC TCP Not Ready!!!");
				lierdaEC_TCP_Ready();
				//If socketID<0 is detected, the socket is not created successfully, to create socketID
				if (lierdaECTCPIPDemoSysValue.TCPSocketID > 0)
				{
					tcpFirstDataSendTest();
				}
				else
				{
					lierdaEC_TCP_Ready();
				}
			}
		}
	}

	msgqueue_obj_t msg;
	for (;;)
	{
		msg.recv_cnt = 0;
		user_buff_len = 0;
		if (xQueueReceive(udp_recv_queue, (void *)&msg, WAIT_FOREVER) == pdTRUE) //Queue received message
		{

			user_buff_len = msg.recv_cnt;
			CHAR *strBuf = NULL;
			strBuf = (CHAR *)malloc(user_buff_len * 2 + 1);
			memset(tcpTestData, 0, user_buff_len);
			memcpy(tcpTestData, TCPIPRecvBuff, user_buff_len); //Only TCP copies the received data to the sending buff
			if (strBuf == NULL)
			{
				ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task, P_INFO, 0, "DBG_INFO : malloc fail");
				return;
			}
			memset(strBuf, 0, (user_buff_len * 2 + 1));
			if (cmsHexToHexStr(strBuf, (user_buff_len * 2 + 1), TCPIPRecvBuff, user_buff_len) > 0) //ECOMM_STRING limit print length <100, the received data is hexadecimal
			{
				memset(TCPIPRecvBuff, 0, sizeof(TCPIPRecvBuff));
				if (lierdaECTCPIPDemoSysValue.UDPSocketID >= 0)
				{
					ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_5, P_INFO, 2, "ReceiveSocketID : %d ,Datalen: %d", lierdaECTCPIPDemoSysValue.UDPSocketID, user_buff_len);
					ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_6, P_INFO, "UDP Receive Data : %s", (const uint8_t *)strBuf);
					osDelay(10000);
					udpDataSendTest();
				}
				else if (lierdaECTCPIPDemoSysValue.TCPSocketID >= 0)
				{
					ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_7, P_INFO, 2, "ReceiveSocketID : %d ,Datalen: %d", lierdaECTCPIPDemoSysValue.TCPSocketID, user_buff_len);
					ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_8, P_INFO, "TCP Receive Data : %s", (const uint8_t *)strBuf);
					RETCP_SENDLEN = lierdaEC_tcpip_Connection_Send(lierdaECTCPIPDemoSysValue.TCPSocketID, tcpTestData, user_buff_len, 0);
					if (RETCP_SENDLEN > 0)
					{
						ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_9, P_INFO, "TCP SendTest Data : %s", (const uint8_t *)strBuf);
						ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_10, P_INFO, 1, "TCP Send Success,SendMsg Len : %d", RETCP_SENDLEN);
					}
					else
					{
						ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_11, P_INFO, 0, "DBG_INFO : TCP Send Fail!!!");
					}
					memset(tcpTestData, 0, sizeof(tcpTestData));
					osDelay(10000);
					// tcpDataSendTest();
				}
				else
				{
					ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_12, P_INFO, 2, "ReceiveSocketID: %d ,Datalen: %d", lierdaECTCPIPDemoSysValue.UDPSocketID, user_buff_len);
					ECOMM_STRING(UNILOG_PLA_APP, lierdaEC_UDP_TCP_Task_13, P_INFO, "UDP Receive Data : %s", (const uint8_t *)strBuf);
				}
			}
			free(strBuf);
			strBuf = NULL;
		}
	}
}

/*******************************************************************************
 * Function Name  : udp_create_queue
 * Description    : Create UDP message queue
 * Input          : None
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
static void udp_create_queue(void)
{
	msgqueue_obj_t msg;
	udp_recv_queue = xQueueCreate(5, sizeof(msgqueue_obj_t));
	if (udp_recv_queue == NULL)
	{
		ECOMM_TRACE(UNILOG_PLA_APP, lierdaEC_udp_create_queue_1, P_INFO, 0, "DBG_INFO : UDP Recv Queue Created Fail!!!");
	}
}

/*******************************************************************************
 * Function Name  : TCPIP_RecvData_CallBack
 * Description    : TCPIP accept message callback function
 * Input          : 
 * Output         : None
 * History        : 1.Create--SewellLin--200510
 *******************************************************************************/
void TCPIP_RecvData_CallBack(INT32 socket, UINT8 *dataRecv, UINT16 dataLen)
{
	msgqueue_obj_t msg;
	msg.recv_cnt = dataLen;
	// ECOMM_TRACE(UNILOG_PLA_APP, TCPIP_RecvData_CallBack_2, P_INFO, 1, "TCPIP_RecvData_CallBack socket:%d", socket);
	if (socket == lierdaECTCPIPDemoSysValue.UDPSocketID)
	{
		memcpy(TCPIPRecvBuff, dataRecv, dataLen);
		xQueueSend(udp_recv_queue, (void *)&msg, 0);
	}
	else if (socket == lierdaECTCPIPDemoSysValue.TCPSocketID)
	{
		memcpy(TCPIPRecvBuff, dataRecv, dataLen);
		xQueueSend(udp_recv_queue, (void *)&msg, 0);
	}
	else
	{
		ECOMM_TRACE(UNILOG_PLA_APP, TCPIP_RecvData_CallBack_1, P_INFO, 0, "DBG_INFO : Recv Socket Error!!!");
		memcpy(TCPIPRecvBuff, dataRecv, dataLen);
		xQueueSend(udp_recv_queue, (void *)&msg, 0);
	}
}
#endif
