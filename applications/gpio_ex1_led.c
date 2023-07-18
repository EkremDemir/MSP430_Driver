/*
 * gpio_ex1.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Casper
 */

#include "main.h"

int GPIO_EX1(){

    PORT_Handle_t PORT_Handle;

    MSP_PORT_Init(&PORT_Handle);

    PORT_Handle.pPORTx = PORT1;
    PORT_Handle.PORT_PinConfig.PORT_PinMode = PORT_MODE_OUTPUT;
    PORT_Handle.PORT_PinConfig.PORT_PinNumber = PORT_PIN_0;

    MSP_PORT_Init(&PORT_Handle);
    retVal = MSP_PORT_WritePin(PORT1, PORT_PIN_0, GPIO_PIN_SET);

    if(retVal == STATE_ERROR){
        return 0;
    }

    while(1){


        MSP_PORT_TogglePin(PORT1, PORT_PIN_0);
        delay_ms(100);
        returnValue = MSP_PORT_ReadPin(PORT1, PORT_PIN_0);
        if(returnValue == STATE_ERROR){
            return 0;
        }
    }
}
