#ifndef __IPERF_API_H_
#define __IPERF_API_H_

//#include "lwip/ip_addr.h"
#include "commontypedef.h"
#include "netmgr.h"


/******************************************************
 *                      Macros
 ******************************************************/



/******************************************************
 *                    structure
 ******************************************************/

typedef enum {
  IPERF_STREAM_PROTOCOL_UDP = 0,
  IPERF_STREAM_PROTOCOL_TCP = 1,  
}IPERF_STREAM_PROTOCOL;

typedef enum {
  IPERF_STREAM_DOMAIN_IP4 = 0,
  IPERF_STREAM_DOMAIN_IP6 = 1,  
}IPERF_STREAM_DOMAIN;

/*iperf init/terminate API*/

BOOL IperfInit(NmIperfReq *pIperfReq);

void IperfTerminate(NmIperfReq *pIperfReq);

#endif

