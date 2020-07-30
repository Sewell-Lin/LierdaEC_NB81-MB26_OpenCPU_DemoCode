/******************************************************************************

*(C) Copyright 2018 EIGENCOMM International Ltd.

* All Rights Reserved

******************************************************************************
*  Filename: at_http_task.h
*
*  Description: Process http(s) client related AT commands
*
*  History:
*
*  Notes:
*
******************************************************************************/
#ifndef _AT_HTTP_TASK_H_
#define _AT_HTTP_TASK_H_

#include "at_util.h"
#include "httpclient.h"

/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/


#define HTTPCLIENT_ATCMD_MAX_NUM   5
#define MAX_BASIC_AUTHUSER_SIZE 128
#define MAX_BASIC_AUTHPASSWD_SIZE 128
#define MAX_HEAD_BUFFER_SIZE 800
#define MAX_RSP_BUFFER_SIZE 400
#define MAX_ATCMD_SIZE (MAX_HEAD_BUFFER_SIZE+MAX_RSP_BUFFER_SIZE)
#define MAX_CONTENT_TYPE_SIZE 64


enum HTTP_MSG_CMD
{
    HTTP_CONNECT_COMMAND,
    HTTP_SEND_COMMAND,
    HTTP_DESTROY_COMMAND
};


/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/

/*
 * APPL SGID: APPL_HTTP, related PRIM ID
*/
typedef enum applHttpPrimId_Enum
{
    APPL_HTTP_PRIM_ID_BASE = 0,

    APPL_HTTP_CONNECT_CNF,
    APPL_HTTP_SEND_CNF,
    APPL_HTTP_DESTORY_CNF,
	APPL_HTTP_IND,

    APPL_HTTP_PRIM_ID_END = 0xFF
}applHttpPrimId;


typedef enum {
    URL_OK = 0,         ///<Success
    URL_FORMAT = 3,     ///<url format error
    URL_NETWORK = 4,    ///<url Parse error
    URL_HTTPS = 14,
}URLError;

typedef enum {
    HTTPSTAT_CLOSED,
    HTTPSTAT_CONNECTED,
    HTTPSTAT_RECEDATA,
}HTTPStatus;

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/
typedef struct {
    BOOL isUsed;
    HTTPStatus status;
    UINT8 httpclientId;
    CHAR* host;
    HttpClientContext* clientContext;
    HttpClientData* clientData;
} httpAtCmd;



// http message queue element typedef
typedef struct
{
    uint32_t cmd_type;
    uint32_t method;
    uint32_t clinetId;
	//void * client_context;
    //void * client_data;
    void * httpcmd;
    char * url;
    uint32_t reqhandle;
} http_queue_obj_t;

URLError httpAtIsUrlValid(char* url);
CmsRetId httpConnectReq(UINT32 atHandle,httpAtCmd* httpCmd );
CmsRetId httpSendReq(UINT32 atHandle,httpAtCmd* httpCmd,char* url, HTTP_METH method );
CmsRetId httpDestroyReq(UINT32 atHandle, httpAtCmd* httpCmd,int httpclientId);

BOOL httpMutexCreate(void);
BOOL httpMutexAcquire(void);
void httpMutexRelease(void);
httpAtCmd* httpGetFreeClient(void);
void httpCreateClientData(httpAtCmd* httpCmd);
void httpReleaseClientData(httpAtCmd* httpCmd);
httpAtCmd* httpFindClient(int httpclientId);
void httpFreeClient(int httpclientId);
int httpGetMaxSocketId(void);
void httpRecvInd(httpAtCmd* httpCmd, UINT8 flag);
void httpErrInd(UINT8 httpClientId, HTTPResult errorCode);
BOOL httpRecvTaskInit(void);
BOOL httpSendTaskInit(void);
//BOOL checkHttpRecvTaskDeleted();
void httpClientRecvTask(void* arg);
void httpClientSendTask(void* arg);

BOOL httpIsConnectExist(void);

#endif

