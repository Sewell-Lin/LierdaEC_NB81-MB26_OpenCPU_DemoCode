/****************************************************************************
 *
 * Copy right:   2020-, Copyrigths of EigenComm Ltd.
 * File name:    hal_uart_atcmd.h
 * Description:  EC616 uart at command header file
 * History:      Rev1.0   2020-02-24
 *
 ****************************************************************************/
/**
  \brief Register AT Channel
  \return
 */
void atCmdRegisterAtChannel(void);

/**
  \brief Init uart handler for AT CMD
  \return
 */
void atCmdInitUartHandler(ARM_DRIVER_USART * uartDriverHandler, uint32_t baudRate);

/**
  \brief Get IPR string for AT CMD AT+IPR print out
  \return pointer to IPR string
 */
uint8_t* atCmdGetIPRString(void);

/**
  \brief Get ECIPR string for AT CMD AT+ ECIPR print out
  \return pointer to ECIPR string
 */
uint8_t* atCmdGetECIPRString(void);

/**
  \brief Check if UART baud rate valid or not
  \param baudRate baud rate need to check
  \return true if pass otherwise false
 */
bool atCmdIsBaudRateValid(uint32_t baudRate);

/**
  \brief    Bypass SEND task and send string to uart directly
  \param[in] strPtr       pointer to string body
  \param[in] strLen       string length
  \return    void
  \note     Used only in specific cases, such as sleep entering procedure where we should not switch out from IDLE task
 */
void atCmdDirectSendStr(uint8_t* strPtr, uint16_t strLen);

