/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of EigenComm Ltd.
 * File name:    ps_sim_if.h
 * Description:  The header file for API interface for PS SIM module
 * History:      Rev1.0   2018-10-12
 *
 ****************************************************************************/
#ifndef __PS_SIM_IF_H__
#define __PS_SIM_IF_H__

#include "cms_util.h"

CmsRetId simGetImsi(UINT32 atHandle);
CmsRetId simGetPinState(UINT32 atHandle);
CmsRetId simEnterPin(UINT32 atHandle, UINT8* oldPasswd, UINT8* newPasswd);
CmsRetId simSetCRSM(UINT32 atHandle, INT32 cmd, INT32 iFileId, CHAR *valStr,  INT32 p1, INT32 p2, INT32 p3, CHAR *data, INT32 dataLen);
CmsRetId simSetCSIM(UINT32 atHandle, INT32 cmdLen, CHAR *cmdStr);
CmsRetId simGetIccid(UINT32 atHandle);
CmsRetId simSetCPWD(UINT32 atHandle, UINT8 no, UINT8 oper, UINT8* oldPasswd, UINT8* newPasswd);
CmsRetId simSetClck(UINT32 atHandle, UINT8 mode, UINT8 fac, UINT8* pinCode);
CmsRetId simSetCcho(UINT32 atHandle, UINT8 *dfName);
CmsRetId simSetCchc(UINT32 atHandle, UINT8 sessionId);
CmsRetId simSetCgla(UINT32 atHandle, UINT8 sessionId, UINT16 len, UINT8* command);
CmsRetId simSetSimSleep(UINT32 atHandle, UINT8 mode);
CmsRetId simGetSimSleepState(UINT32 atHandle);
CmsRetId simSetCpinr(UINT32 atHandle, UINT8 pinCode);
CmsRetId simSetECSWC(UINT32 atHandle, UINT8 mode);
CmsRetId simGetSWCSetting(UINT32 atHandle);


void simGetImsiSync(void *msg);
void simGetIccidSync(void *msg);
void simSetCchoSync(void *msg);
void simSetCchcSync(void *msg);
void simSetCglaSync(void *msg);
void simSetCrsmSync(void *msg);

#endif

