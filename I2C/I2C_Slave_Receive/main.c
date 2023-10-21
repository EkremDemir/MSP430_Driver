/**
 * File Name: I2C slave receive.c
 * Author: Ekrem Demir
 * Date: 22.10.2023
 * Description: MSP430G2553 I2C slave code for receiving data.
 */

#include <msp430.h>
#include <stdint.h>

// Constants
#define SLAVE_ADDRESS          0x56
#define RECEIVE_BUFFER_SIZE    32
#define LED_PIN                BIT0

// Global Variables
uint8_t receiveBuffer[RECEIVE_BUFFER_SIZE] = {0};
uint8_t receiveIndex = 0;

// Function Prototypes
void initialize_I2C_Slave(void);

int main(void)
{
    // Stop Watchdog Timer
    WDTCTL = WDTPW + WDTHOLD;

    // Initialize LED
    P1DIR |= LED_PIN;
    P1OUT |= LED_PIN;

    // Initialize I2C
    initialize_I2C_Slave();

    // Enable global interrupts
    __bis_SR_register(GIE);

    while (1)
    {
        // Main loop can be used for other tasks
    }
}

void initialize_I2C_Slave(void)
{
    // Assign I2C pins to USCI_B0
    P1SEL |= BIT6 + BIT7;
    P1SEL2|= BIT6 + BIT7;

    // Configure I2C Slave mode
    UCB0CTL1 |= UCSWRST;                      // Enable software reset
    UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
    UCB0I2COA = SLAVE_ADDRESS;                // Set slave address
    UCB0CTL1 &= ~UCSWRST;                     // Release software reset
    UCB0I2CIE |= UCSTPIE + UCSTTIE;           // Enable start and stop interrupts
    IE2 |= UCB0RXIE;                          // Enable receive interrupt

    // Clear interrupt flags
    IFG2 &= ~(UCB0TXIFG + UCB0RXIFG);
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void I2C_TX_ISR(void)
{
    if (IFG2 & UCB0RXIFG)
    {
        // Move received data to buffer
        receiveBuffer[receiveIndex++] = UCB0RXBUF;

        // Handle buffer overflow
        if (receiveIndex >= RECEIVE_BUFFER_SIZE)
            receiveIndex = 0;

        // Clear receive interrupt flag
        IFG2 &= ~UCB0RXIFG;
    }
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void I2C_RX_ISR(void)
{
    // Clear interrupt flags
    UCB0STAT &= ~(UCSTPIFG + UCSTTIFG + UCNACKIFG);
}

