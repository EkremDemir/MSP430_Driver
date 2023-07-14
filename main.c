#include <msp430.h> 


/**
 * main.c
 */

#include "main.h"

MSP_Status_t retVal;
uint8_t returnValue;

void delay_ms(uint16_t time)
{
    while(time)
    {
        __delay_cycles(1000);
        //By default clock is 1 MHZ. Hence 1 tick is 1us. 1ms means 1000 ticks.

        --time;
    }
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	PORT_Handle_t PORT_Handle;

	MSP_Port_Init(&PORT_Handle);

	PORT_Handle.pPORTx = PORT1;
	PORT_Handle.PORT_PinConfig.PORT_PinMode = PORT_MODE_OUTPUT;
	PORT_Handle.PORT_PinConfig.PORT_PinNumber = PORT_PIN_0;

	MSP_Port_Init(&PORT_Handle);
	retVal = MSP_Port_WritePin(PORT1, PORT_PIN_0, GPIO_PIN_SET);

    if(retVal == STATE_ERROR){
        return 0;
    }

	while(1){


	    MSP_Port_TogglePin(PORT1, PORT_PIN_0);
	    delay_ms(100);
	    returnValue = MSP_Port_ReadPin(PORT1, PORT_PIN_0);
	    if(returnValue == STATE_ERROR){
	        return 0;
	    }
	}

}



