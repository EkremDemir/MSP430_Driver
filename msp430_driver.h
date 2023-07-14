/*
 * msp430_driver.h
 *
 *  Created on: Jul 13, 2023
 *      Author: Casper
 */

#ifndef MSP430_DRIVER_H_
#define MSP430_DRIVER_H_

#include "main.h"

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


typedef struct
{
  uint16_t PIN;      /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode_define */
  uint16_t POUT;       /*!< Specifies the PORT pins to be configured.
                           This parameter can be any value of @ref port_pins_define */
  uint16_t PDIR;  /*!< Peripheral to be connected to the selected Port.
                           This parameter can be a value of @ref MSP_Port_selection */


  uint16_t PREN;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull_define */

  uint16_t PSEL0;  /*!< Peripheral to be connected to the selected pins.*/

  uint16_t PSEL1;

  uint16_t PIV;

  uint16_t PSELC;

  uint16_t PIES;

  uint16_t PIE;

  uint16_t PIFG;

}PORT_RegDef_t;








#endif /* MSP430_DRIVER_H_ */
