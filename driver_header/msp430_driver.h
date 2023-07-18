/*
 * msp430_driver.h
 *
 *  Created on: Jul 13, 2023
 *      Author: Casper
 */

#ifndef MSP430_DRIVER_H_
#define MSP430_DRIVER_H_

#include "main.h"



typedef enum
{
    STATE_OK = 0x01,
    STATE_ERROR = 0x11

}MSP_Status_t;

#define ENABLE                  1
#define DISABLE                 0

/* */
/*******************START:Processor Specific Details **************************/

#define SFR_BASEADDR            __MSP430_BASEADDRESS_SFR__

#define PMM_BASEADDR            __MSP430_BASEADDRESS_PMM_FRAM__

#define CS_BASEADDR             __MSP430_BASEADDRESS_SYS__

#define FRAM_BASEADDR           __MSP430_BASEADDRESS_FRAM__

#define CRC_BASEADDR            __MSP430_BASEADDRESS_CRC__

#define WDT_BASEADDR            __MSP430_BASEADDRESS_WDT_A__

#define PORT1_BASEADDR          __MSP430_BASEADDRESS_PORT1_R__
#define PORT2_BASEADDR          __MSP430_BASEADDRESS_PORT2_R__
#define PORT3_BASEADDR          __MSP430_BASEADDRESS_PORT3_R__

#define RTC_BASEADDR            __MSP430_BASEADDRESS_RTC__

#define TIMER0_A3_BASEADD       __MSP430_BASEADDRESS_T0A3__
#define TIMER1_A3_BASEADD       __MSP430_BASEADDRESS_T1A3__
#define TIMER2_A2_BASEADD       __MSP430_BASEADDRESS_T2A2__
#define TIMER3_A2_BASEADD       __MSP430_BASEADDRESS_T3A2__

#define MPY32_BASEADDR          __MSP430_BASEADDRESS_MPY32__

#define EUSCI_A0_BASEADDR       __MSP430_BASEADDRESS_EUSCI_A0__
#define EUSCI_A1_BASEADDR       __MSP430_BASEADDRESS_EUSCI_A1__
#define EUSCI_B0_BASEADDR       __MSP430_BASEADDRESS_EUSCI_B0__

#define BACKUP_MEM_BASEADDR     __MSP430_BASEADDRESS_BKMEM__

#define ADC_BASEADDR            __MSP430_BASEADDRESS_ADC__

/* */

#define PORT2_OFFSET            (0x01)

#define PORT1                   ((PORT_RegDef_t*)__MSP430_BASEADDRESS_PORT1_R__)
#define PORT2                   ((PORT_RegDef_t*)(__MSP430_BASEADDRESS_PORT2_R__ + 0x0001))
#define PORT3                   ((PORT_RegDef_t*)__MSP430_BASEADDRESS_PORT3_R__)

#define UART_A0                 ((UART_RegDef_t *)EUSCI_A0_BASEADDR)
#define UART_A1                 ((UART_RegDef_t *)EUSCI_A1_BASEADDR)
#define UART_B0                 ((UART_RegDef_t *)EUSCI_B0_BASEADDR)

/* */



/* */

/* */
#define FALLING_EDGE            (0x00)
#define RISING_EDGE             (0x01)
/* */


/* */
#define __vo                    volatile
/* */


/* */

/* */

typedef struct
{
  __vo uint8_t PIN;      /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode_define */
  uint8_t RESERVED0;

  __vo uint8_t POUT;       /*!< Specifies the PORT pins to be configured.
                           This parameter can be any value of @ref port_pins_define */
  uint8_t RESERVED1;

  __vo uint8_t PDIR;  /*!< Peripheral to be connected to the selected Port.
                           This parameter can be a value of @ref MSP_Port_selection */
  uint8_t RESERVED2;

  __vo uint8_t PREN;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull_define */
  uint8_t RESERVED3;

  uint16_t RESERVED4;

  __vo uint8_t PSEL0;  /*!< Peripheral to be connected to the selected pins.*/

  uint8_t RESERVED5;

  __vo uint8_t PSEL1; //0C

  uint8_t RESERVED6; //0D

//  uint8_t PIV_L; // 0e 1e
//
//  uint8_t PIV_H; // 0e 1e

  uint32_t RESERVED7; // 0E 0F 10 11

  uint32_t RESERVED8; // 12 13 14 15

  __vo uint8_t PSELC; // 16

  uint8_t RESERVED9;

  __vo uint8_t PIES; // 18

  uint8_t RESERVED10;

  __vo uint8_t PIE; // 1A

  uint8_t RESERVED11;

  __vo uint8_t PIFG; // 1C

}PORT_RegDef_t;

typedef struct
{
    __vo uint16_t UCCTLW0;
    __vo uint16_t UCCTLW1;
    uint16_t RESERVED0;
    __vo uint16_t  UCBR;
//    __vo uint8_t  UCBR0;
//    __vo uint8_t  UCBR1;
    __vo uint16_t UCMCTLW;
    __vo uint16_t UCSTAT;
    __vo uint16_t UCRXBUF;
    __vo uint16_t UCTXBUF;
    __vo uint16_t UCABCTL;
    __vo uint8_t  lUCIRTCTL;
    __vo uint8_t IUCIRRCTL;
    uint32_t RESERVED1;
    uint16_t RESERVED2;
    __vo uint16_t UCIE;
    __vo uint16_t UCIFG;
    __vo uint16_t UCIV;
} UART_RegDef_t;


#endif /* MSP430_DRIVER_H_ */
