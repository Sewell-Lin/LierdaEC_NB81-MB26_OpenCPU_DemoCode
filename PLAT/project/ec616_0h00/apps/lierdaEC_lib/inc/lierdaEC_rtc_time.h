/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    lierdaEC_rtc_time.h
 * Description:  API interface implementation header file for RTC_TIME driver
 * History:      Rev1.0   2020-06-02
 *
 ****************************************************************************/
#ifndef LIERDAEC_RTC_TIME_H
#define LIERDAEC_RTC_TIME_H

#include "osasys.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UTC_TIME{
    uint16_t 		year;        //年
    uint8_t 		month;       //月
    uint8_t     day;	       //日
    uint8_t		  hour;        //时
    uint8_t		  minute;      //分
    uint8_t		  second;      //秒
    uint16_t		millisecond;    //毫秒  0~1000ms
}UTC_DATE_TIME_T;


/**
  \fn   int8_t lierdaEC_get_current_date_time(UTC_DATE_TIME_T *current_date_time, bool isUTC)
  \brief Get the current date and time.
  \param[out] current_date_time   Pointer to UTC_DATE_TIME_T structure.
  \param[in]  isUTC ---> true,  UTC time
                         false, Beijing time (GMT+8 time zone)
  \return  0 success,  -1, fail.                       
 */
int8_t lierdaEC_get_current_date_time(UTC_DATE_TIME_T *current_date_time, bool isUTC);

/**
  \fn    uint32_t lierdaEC_get_rtc_time_s(void)
  \brief Get the current system time (s).  unsigned int UTCsecs, UTC secs since 1970.
  \return    system time. 
 */
uint32_t lierdaEC_get_rtc_time_s(void);

/**
  \fn    uint32_t lierdaEC_get_rtc_time_ms(void)
  \brief Get the current system time (ms). unsigned int UTCms, 0 ~ 1000ms.
  \return    system time (ms). 
 */
uint32_t lierdaEC_get_rtc_time_ms(void);


#ifdef __cplusplus
}
#endif

#endif /* LIERDAEC_RTC_TIME_H */
