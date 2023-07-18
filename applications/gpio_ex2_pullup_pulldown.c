/*
 * gpio_ex2.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Casper
 */

#include "main.h"
int GPIO_EX2(){

    PORT_Handle_t PORT_Handle;

    MSP_PORT_Init(&PORT_Handle);

    PORT_Handle.pPORTx = PORT1;
    PORT_Handle.PORT_PinConfig.PORT_PinMode = PORT_MODE_OUTPUT;
    PORT_Handle.PORT_PinConfig.PORT_PinNumber = PORT_PIN_0;
    PORT_Handle.PORT_PinConfig.PORT_PinPuPdControl = PORT_NOPULL;


    MSP_PORT_Init(&PORT_Handle);

    retVal = MSP_PORT_WritePin(PORT1, PORT_PIN_0, GPIO_PIN_RESET);

    PORT_Handle.PORT_PinConfig.PORT_PinPuPdControl = PORT_PULLUP;

    MSP_PORT_Init(&PORT_Handle);

    retVal = MSP_PORT_WritePin(PORT1, PORT_PIN_0, GPIO_PIN_SET);
    PORT_Handle.PORT_PinConfig.PORT_PinPuPdControl = PORT_PULLDOWN;

    MSP_PORT_Init(&PORT_Handle);

    if(retVal == STATE_ERROR){
        return 0;
    }

    while(1){}
}

