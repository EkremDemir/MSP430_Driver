/*
 * main.h
 *
 *  Created on: Jul 13, 2023
 *      Author: Casper
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <stdint.h>
#include "msp430fr2433.h"
#include "msp430_driver.h"
#include "msp430_gpio_driver.h"
#include "msp430_uart_driver.h"

MSP_Status_t retVal;
uint8_t returnValue;

void delay_ms(uint16_t time);
int GPIO_EX1(void);
int GPIO_EX2(void);
int GPIO_EX3(void);

void UART_EX1(void);

#endif /* MAIN_H_ */
