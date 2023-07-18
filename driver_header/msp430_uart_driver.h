/*
 * msp430_uart_driver.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Casper
 */

#ifndef MSP430_DRIVER_DRIVER_HEADER_MSP430_UART_DRIVER_H_
#define MSP430_DRIVER_DRIVER_HEADER_MSP430_UART_DRIVER_H_

#include "main.h"

#define UART_ASYNCH_MODE             0x00
#define UART_SYNCH_MODE              0x01

#define UART_NON_PARITY              0x00
#define UART_ODD_PARITY              0x01
#define UART_EVEN_PARITY             0x02

#define UART_LSB_FIRST               0x00
#define UART_MSB_FIRST              0x01

#define UART_LENGTH_8                0x00
#define UART_LENGTH_7                0x01

#define UART_STOP_BIT_1              0x00
#define UART_STOP_BIT_2              0x01

#define UART_ASYNCH_MODE_UART        0x00
#define UART_ASYNCH_MODE_ILMM        0x01
#define UART_ASYNCH_MODE_AMM         0x02
#define UART_ASYNCH_MODE_AUTO_BR     0x03

#define UART_CLOCK_UCLK             0x00
#define UART_CLOCK_DEV_SPESIFIC     0x01
/* SMCLK'S ARE SAME CHOOSE ONE OF THEM */
#define UART_CLOCK_SMCLK1           0x02
#define UART_CLOCK_SMCLK2           0x03


//*****************************************************************************
#define UART_RECEIVE_INTERRUPT                                   UCRXIE
#define UART_TRANSMIT_INTERRUPT                                  UCTXIE
#define UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT                    UCRXEIE
#define UART_BREAKCHAR_INTERRUPT                                UCBRKIE
#define UART_STARTBIT_INTERRUPT                                 UCSTTIE
#define UART_TRANSMIT_COMPLETE_INTERRUPT                      UCTXCPTIE


typedef struct
{
    uint8_t PORT_PinNumber;         /*!<possible pins from  @GPIO_PIN_NUMBERS>*/
    uint8_t PORT_PinMode;           /*!< possible values from @GPIO_PIN_MODES >*/
    uint8_t PORT_PinPuPdControl;
    uint8_t PORT_PinAltFunMode;

}UART_PinConfig_t;


typedef struct
{
    uint8_t  UART_Mode;
    uint8_t  UART_LsbMsbSelect;
    uint16_t UART_ClockPrescalar; /* to specify baud rate */
    uint8_t  UART_NoOfStopBits;
    uint8_t  UART_CharLength;
    uint8_t  UART_ParityControl;
    uint8_t  UART_AsynchronousMode;
    uint8_t  UART_ClockSource;

}UART_Config_t;


typedef struct
{
    UART_RegDef_t *pUARTx;

    UART_Config_t UART_Config;

    UART_PinConfig_t UART_PinConfig;

}UART_Handle_t;

void MSP_UART_Init(UART_Handle_t *pUARTHandle);
void MSP_UART_Enable (UART_Handle_t *pUARTHandle);
void MSP_UART_Disable (UART_Handle_t *pUARTHandle);
void MSP_UART_TransmitData(UART_Handle_t *pUARTHandle, uint8_t transmitData);
uint8_t MSP_UART_ReceiveData(UART_Handle_t *pUARTHandle);

void MSP_UART_EnableInterrupt(UART_Handle_t *pUARTHandle, uint8_t interruptMode);
void MSP_UART_DisableInterrupt(UART_Handle_t *pUARTHandle, uint8_t interruptMode);
uint8_t MSP_UART_GetInterruptStatus(UART_Handle_t *pUARTHandle, uint8_t interruptMode);
void MSP_UART_ClearInterrupt(UART_Handle_t *pUARTHandle, uint8_t interruptMode);

void MSP_UART_PinSelect(void);

#endif /* MSP430_DRIVER_DRIVER_HEADER_MSP430_UART_DRIVER_H_ */
