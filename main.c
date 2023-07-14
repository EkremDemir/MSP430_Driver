#include <msp430.h> 


/**
 * main.c
 */

#include "main.h"



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
	
//	GPIO_EX1();
//	GPIO_EX2();
	GPIO_EX3();
}



