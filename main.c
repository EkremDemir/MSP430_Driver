#include <msp430.h> 


/**
 * main.c
 */

#include "main.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	return 0;
}
