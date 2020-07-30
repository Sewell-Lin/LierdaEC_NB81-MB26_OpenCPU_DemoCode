/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_virtual_at.h
 * Description:  API interface implementation header file for virtual AT command
 * History:      Rev1.0   2020-04-09
 *
 ****************************************************************************/
#ifndef  LIERDAEC_VIRTUAL_AT_H
#define  LIERDAEC_VIRTUAL_AT_H

#ifdef __cplusplus
extern "C" {
#endif


/**
  \fn           CHAR *lierdaECATCall(CHAR *at_cmd_buf_param, UINT16 timeout)
  \brief        Virtual AT command API, request the AT command service. It a blocked API, and will returned in force in "timeout" milliseconds
  \param[in]    at_cmd_buf_param    AT command, should end with "\r\n"
  \param[in]    timeout       AT guard time, unit(ms)
  \returns      Returns the address of the pointer that response the AT command string.
*/
extern CHAR *lierdaECATCall(CHAR *at_cmd_buf_param, UINT16 timeout_ms);


#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_VIRTUAL_AT_H */
