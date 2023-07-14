/*
 * msp430_gpio_driver.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Casper
 */

#ifndef MSP430_GPIO_DRIVER_H_
#define MSP430_GPIO_DRIVER_H_


#include "main.h"

typedef struct
{
    uint8_t PORT_PinNumber;
    uint8_t PORT_PinMode;           /*!< possible values from @GPIO_PIN_MODES >*/
    uint8_t PORT_PinSpeed;          /*!< possible values from @GPIO_PIN_SPEED >*/
    uint8_t PORT_PinPuPdControl;
    uint8_t PORT_PinOPType;
    uint8_t PORT_PinAltFunMode;

}PORT_PinConfig_t;

typedef struct
{
    PORT_RegDef_t *pPORTx;              /*!< This holds the base address of the GPIO port to which the pin belongs >*/
    PORT_PinConfig_t PORT_PinConfig;   /*!< This holds GPIO pin configuration settings >*/

}PORT_Handle_t;


#endif /* MSP430_GPIO_DRIVER_H_ */
