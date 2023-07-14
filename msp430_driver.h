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

/* */

#define EnorDiGPIO(EN) ((EN==ENABLE) ? (PM5CTL0 &= ~LOCKLPM5) : (PM5CTL0 |= LOCKLPM5))

/* */

/* */
#define FALLING_EDGE            (0x00)
#define RISING_EDGE             (0x01)
/* */

//typedef struct
//{
//  uint16_t PIN;      /*!< Specifies the operating mode for the selected pins.
//                           This parameter can be a value of @ref GPIO_mode_define */
//  uint16_t POUT;       /*!< Specifies the PORT pins to be configured.
//                           This parameter can be any value of @ref port_pins_define */
//  uint16_t PDIR;  /*!< Peripheral to be connected to the selected Port.
//                           This parameter can be a value of @ref MSP_Port_selection */
//
//
//  uint32_t PREN;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
//                           This parameter can be a value of @ref GPIO_pull_define */
//
//  uint16_t PSEL0;  /*!< Peripheral to be connected to the selected pins.*/
//
//  uint16_t PSEL1;
//
//  uint32_t RESERVED0;
//
//  uint32_t RESERVED1;
//
//  uint16_t PSELC;
//
//  uint16_t PIV;
//
//  uint16_t PIES;
//
//  uint16_t PIE;
//
//  uint16_t PIFG;
//
//
//}PORT_RegDef_t;

typedef struct
{
  uint8_t PIN;      /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode_define */
  uint8_t RESERVED0;

  uint8_t POUT;       /*!< Specifies the PORT pins to be configured.
                           This parameter can be any value of @ref port_pins_define */
  uint8_t RESERVED1;

  uint8_t PDIR;  /*!< Peripheral to be connected to the selected Port.
                           This parameter can be a value of @ref MSP_Port_selection */
  uint8_t RESERVED2;

  uint8_t PREN;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull_define */
  uint8_t RESERVED3;

  uint16_t RESERVED4;

  uint8_t PSEL0;  /*!< Peripheral to be connected to the selected pins.*/

  uint8_t RESERVED5;

  uint8_t PSEL1; //0C

  uint8_t RESERVED6; //0D

//  uint8_t PIV_L; // 0e 1e
//
//  uint8_t PIV_H; // 0e 1e

  uint32_t RESERVED7; // 0E 0F 10 11

  uint32_t RESERVED8; // 12 13 14 15

  uint8_t PSELC; // 16

  uint8_t RESERVED9;

  uint8_t PIES; // 18

  uint8_t RESERVED10;

  uint8_t PIE; // 1A

  uint8_t RESERVED11;

  uint8_t PIFG; // 1C

}PORT_RegDef_t;



#endif /* MSP430_DRIVER_H_ */
