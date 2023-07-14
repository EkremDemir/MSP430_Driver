/*
 * gpio_ex3_interrupt.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Casper
 */


#include "main.h"
uint16_t read;

int GPIO_EX3(){

    PORT_Handle_t PORT_Handle;


    /* INTERRUPT CONFIGURATION */

    PORT_Handle.pPORTx = PORT2;
    PORT_Handle.PORT_PinConfig.PORT_PinMode = PORT_MODE_INPUT;
    PORT_Handle.PORT_PinConfig.PORT_PinNumber = PORT_PIN_3;
    PORT_Handle.PORT_PinConfig.PORT_PinPuPdControl = PORT_PULLUP;
    MSP_Port_Init(&PORT_Handle);

    MSP_PORT_SelectInterruptEdge(PORT2, PORT_PIN_3, FALLING_EDGE);

    MSP_PORT_EnableInterrupt(PORT2, PORT_PIN_3);

    read = MSP_PORT_GetInterruptStatus(PORT2, PORT_PIN_3);

    /* OUTPUT PIN CONFIGURATION */

    PORT_Handle.pPORTx = PORT1;
    PORT_Handle.PORT_PinConfig.PORT_PinMode = PORT_MODE_OUTPUT;
    PORT_Handle.PORT_PinConfig.PORT_PinNumber = PORT_PIN_0;
    PORT_Handle.PORT_PinConfig.PORT_PinPuPdControl = PORT_PULLUP;

    MSP_Port_Init(&PORT_Handle);

    while(1){

        read = MSP_PORT_GetInterruptStatus(PORT2, PORT_PIN_3);
        if(read==8){
            MSP_Port_TogglePin(PORT1, PORT_PIN_0);
            while(1){

            }
        }

        delay_ms(10);
    }
}

