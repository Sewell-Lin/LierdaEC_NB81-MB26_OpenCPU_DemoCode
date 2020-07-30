/****************************************************************************
 *
 * Copy right:   LIERDA.
 * File name:    damo_app.h
 * Description:  
 * History:      Rev1.0   2020-04-08
 *
 ****************************************************************************/
#ifndef _DEMO_APP_H
#define _DEMO_APP_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "stdio.h"
#include "bsp.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "string.h"
#include "stdarg.h"
#include "ostask.h"
#include "osasys.h"
#include "cms_util.h"
#include "debug_log.h"
#include "lierdaEC_pad.h"
#include "lierdaEC_uart.h"
#include "lierdaEC_gpio.h"
#include "lierdaEC_adc.h"
#include "lierdaEC_spi.h"
#include "lierdaEC_i2c.h"
#include "lierdaEC_tcpip.h"
#include "lierdaEC_virtual_at.h"
#include "lierdaEC_timer_pwm.h"
#include "lierdaEC_ct_api.h"
#include "lierdaEC_rtc_time.h"
#include "lierdaEC_wdt.h"
#include "lierdaEC_ctiot.h"
#include "lierdaEC_SysGlobalParameters.h"

#define WAIT_FOREVER 0xffffffff

#define TCPIP_DEMO_TASK 0 //Define whether to open UDPTCP task,0-close ,1-open
#define I2C_DEMO_TASK 1   //Define whether to start I2C task,0-close ,1-open
#define SPI_DEMO_TASK 1   //Define whether to start SPI task,0-close ,1-open

#define IMEI_LEN 15  //IMEI number length
#define IMSI_LEN 15  //IMSI number length
#define ICCID_LEN 20 //ICCID number length

#define AT_SIM_Q "AT+CPIN?\r\n"       //Check sim card
#define AT_CEGEG_Q "AT+CEREG?\r\n"    //Query core network registration
#define AT_CGPADDR_Q "AT+CGPADDR\r\n" //Query the core network to assign an IP address
#define AT_OK_Q "AT\r\n"              //Check AT function

/** \brief Button location 按键 */
#define BUTTON_GPIO_PORT (0)
#define BUTTON_GPIO_PIN (1)
#define BUTTON_PAD_PADDR (12)
#define BUTTON_PAD_MUX_ALT (PAD_MuxAlt0)

/** \brief TCPIP */
#if TCPIP_DEMO_TASK
#define LocalPort 56600                                                                                                                        //Local address range: 10240 <localPort <60000
#define Select_UDP_TCP -1                                                                                                                      //UDP = 1 ;TCP = -1
#define UDP_Server_Add "52.80.71.189"                                                                                                          //UDP server address
#define UDP_Server_Port 7400                                                                                                                   //UDP server port
#define TCP_Server_Add "52.80.71.189"                                                                                                          //TCP server address
#define TCP_Server_Port 31001                                                                                                                  //TCP server port
#define TCPFIRSTTESTDATA "FFAAD3D20000190F3836393032393033353833383036380100E9"                                                                //Data sent by TCP for the first time
#define TCPIP_RECV_BUFF_LEN 300                                                                                                                //TCP receive data buffer length
#define UDPTESTDATA "FFAAD3D100003C0F3836393032393033353833383036380F34363030343236393639303731393013000000000000000000000000000000000000003B" //UDP circularly sent data
#endif

/** \brief LED location */
/** LED location 查看EC616 数据手册 <5.2.1 管脚复用> */
#define LED_GPIO_PORT (0)             // port   PORT0, 0--15 // PORT1, 16-30
#define LED_GPIO_PIN (7)              // pin    GPIO7  用Pin Name的序号(例 GPIO19)除以16，商0是port，余数7是pin
#define LED_PAD_PADDR (18)            // paddr  查看芯片手册管脚paddr
#define LED_PAD_MUX_ALT (PAD_MuxAlt0) // 作为普通GPIO使用是PAD_MuxAlt0，作其他复用功能使用配置不一样

/** \brief About I2C */
#if I2C_DEMO_TASK
#define OPT3001_DEVICE_ADDR 0x44 // OPT3001 device addr
#define OPT3001_REG_RESULT 0x00
#define OPT3001_REG_CONFIGURATION 0x01
#define OPT3001_REG_LOW_LIMIT 0x02
#define OPT3001_REG_HIGH_LIMIT 0x03
#define OPT3001_REG_MANUFACTURE_ID 0x7E
#define OPT3001_REG_DEVICE_ID 0x7F
// OPT3001 CONFIG resister bit map
#define CONFIG_RN_Pos (12)
#define CONFIG_RN_Msk (0xF << CONFIG_RN_Pos)
#define CONFIG_CT_Pos (11)
#define CONFIG_CT_Msk (0x1 << CONFIG_CT_Pos)
#define CONFIG_M_Pos (9)
#define CONFIG_M_Msk (0x3 << CONFIG_M_Pos)
#define CONFIG_OVF_Pos (8)
#define CONFIG_OVF_Msk (0x1 << CONFIG_OVF_Pos)
#define CONFIG_CRF_Pos (7)
#define CONFIG_CRF_Msk (0x1 << CONFIG_CRF_Pos)
#define CONFIG_FH_Pos (6)
#define CONFIG_FH_Msk (0x1 << CONFIG_FH_Pos)
#define CONFIG_FL_Pos (5)
#define CONFIG_FL_Msk (0x1 << CONFIG_FL_Pos)
#define CONFIG_L_Pos (4)
#define CONFIG_L_Msk (0x1 << CONFIG_L_Pos)
#define CONFIG_POL_Pos (3)
#define CONFIG_POL_Msk (0x1 << CONFIG_POL_Pos)
#define CONFIG_ME_Pos (2)
#define CONFIG_ME_Msk (0x1 << CONFIG_ME_Pos)
#define CONFIG_FC_Pos (0)
#define CONFIG_FC_Msk (0x3 << CONFIG_L_Pos)
// OPT3001 CONFIG setting macro
#define CONFIG_CT_100 0x0000                  // conversion time set to 100ms
#define CONFIG_CT_800 CONFIG_CT_Msk           // conversion time set to 800ms
#define CONFIG_M_CONTI (0x2 << CONFIG_M_Pos)  // continuous conversions
#define CONFIG_M_SINGLE (0x1 << CONFIG_M_Pos) // single-shot
#define CONFIG_M_SHUTDOWN 0x0000              // shutdown
#define CONFIG_RN_RESET (0xC << CONFIG_RN_Pos)
#define CONFIG_CT_RESET CONFIG_CT_800
#define CONFIG_L_RESET CONFIG_L_Msk
#define CONFIG_DEFAULTS (CONFIG_RN_RESET | CONFIG_CT_RESET | CONFIG_L_RESET)
#define CONFIG_ENABLE_CONTINUOUS (CONFIG_M_CONTI | CONFIG_DEFAULTS)
#define CONFIG_ENABLE_SINGLE_SHOT (CONFIG_M_SINGLE | CONFIG_DEFAULTS)
#define CONFIG_DISABLE CONFIG_DEFAULTS
#define REGISTER_LENGTH 2
#endif

/***************** \brief SPI *****************/
#if SPI_DEMO_TASK

#define SPI_FLASH_PageSize 256
#define SPI_FLASH_PerWritePageSize 256
#define W25X_WriteEnable 0x06
#define W25X_WriteDisable 0x04
#define W25X_ReadStatusReg 0x05
#define W25X_WriteStatusReg 0x01
#define W25X_ReadData 0x03
#define W25X_FastReadData 0x0B
#define W25X_FastReadDual 0x3B
#define W25X_PageProgram 0x02
#define W25X_BlockErase 0xD8
#define W25X_SectorErase 0x20
#define W25X_ChipErase 0xC7
#define W25X_PowerDown 0xB9
#define W25X_ReleasePowerDown 0xAB
#define W25X_DeviceID 0xAB
#define W25X_ManufactDeviceID 0x90
#define W25X_JedecDeviceID 0x9F
#define WIP_Flag 0x01 /* Write In Progress (WIP) flag */

#define Dummy_Byte 0xFF

#define FLASH_SectorToErase 0x000000
#define FLASH_WriteAddress FLASH_SectorToErase
#define FLASH_ReadAddress FLASH_SectorToErase

#define countof(a) (sizeof(a) / sizeof(*(a)))
#define TxBufferSize1 (countof(TxBuffer1) - 1)
#define RxBufferSize1 (countof(TxBuffer1) - 1)
#define BufferSize (countof(Tx_Buffer) - 1)
#define SPI_CS_ENABLE() lierdaEC_GPIO_PinWrite(SPI0_SSN_GPIO_PORT, SPI0_SSN_GPIO_PIN, GPIO_PIN_LOW)
#define SPI_CS_DISABLE() lierdaEC_GPIO_PinWrite(SPI0_SSN_GPIO_PORT, SPI0_SSN_GPIO_PIN, GPIO_PIN_HIGH)
#endif
  void lierdaEC_app_main(void);
  void LierdaEC_time_get_Test(void);
  void lierdaEC_APP_Task(void *arg);
  static void App_Task_Created(void);
  extern void lierdaEC_TCPIP_Task(void *arg);
  extern void lierdaEC_USART_Task(void *arg);
  extern void lierdaEC_UPdata_Task(void *arg);
  extern void lierdaEC_Downdata_Task(void *arg);
  extern void lierdaEC_I2C_Test(void);
  extern void App_Resource_Created(void);
  extern void lierdaEC_ADC_Test(void);
  extern void lierdaEC_AT_Test(void);
  extern void lierdaEC_PWM_TIMER_Test(void);
  extern void lierdaEC_PWM_TIMER_INIT(void);
  extern void lierdaEC_GPIO_Test(void);
  extern void lierdaEC_GPIO_INIT(void);
  extern void lierdaEC_USART_INIT(void);
  extern void lierdaEC_SPI_Test(void);

#ifdef __cplusplus
}
#endif

#endif /* _DEMO_APP_H */
