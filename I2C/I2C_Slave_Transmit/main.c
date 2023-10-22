/**
 * @file main.c
 * @author Ekrem Demir
 * @date 22.10.2023
 * @brief MSP430G2553 I2C slave code for transmiting data.
 */

#include <msp430.h>
#include <stdint.h>

// Constants
#define SLAVE_ADDRESS          0x48
#define TRANSMIT_BUFFER_SIZE   32
#define LED_PIN                BIT0

// Global Variables
static uint8_t transmitBuffer[TRANSMIT_BUFFER_SIZE] = "Practice Makes Perfect Practice ";
static uint8_t transmitIndex = 0;

// Function Prototypes
static void InitializeI2CSlave(void);

/**
 * @brief Main function.
 * 
 * Initializes system peripherals and enters infinite loop.
 */
int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Initialize LED
    P1DIR |= LED_PIN;
    P1OUT |= LED_PIN;

    // Initialize I2C
    InitializeI2CSlave();

    // Enable global interrupts
    __bis_SR_register(GIE);

    // Main loop
    while (1)
    {
        // Idle state, can be used for power-saving modes or other tasks
    }
}

/**
 * @brief Initializes I2C in slave mode.
 */
static void InitializeI2CSlave(void)
{
    // Assign I2C pins to USCI_B0
    P1SEL |= BIT6 + BIT7;
    P1SEL2|= BIT6 + BIT7;

    // Enable software reset and set I2C Slave, synchronous mode
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = UCMODE_3 | UCSYNC;  

    // Set own address
    UCB0I2COA = SLAVE_ADDRESS;

    // Release from software reset and configure interrupts
    UCB0CTL1 &= ~UCSWRST;
    UCB0I2CIE |= UCSTPIE | UCSTTIE; 
    IE2 |= UCB0TXIE | UCB0RXIE;

    // Clear interrupt flags
    IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);
}

/**
 * @brief I2C Transmit Interrupt Service Routine.
 * 
 * Handles transmission of data when a transmit interrupt occurs.
 */
#pragma vector = USCIAB0TX_VECTOR
__interrupt void I2C_TX_ISR(void)
{
    if (IFG2 & UCB0TXIFG)
    {
        // Transmit data
        UCB0TXBUF = transmitBuffer[transmitIndex++];

        // Reset transmitIndex if it exceeds buffer size
        if (transmitIndex >= TRANSMIT_BUFFER_SIZE)
        {
            transmitIndex = 0;
        }

        // Clear transmit and receive interrupt flags
        IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);
    }
}

/**
 * @brief I2C Receive Interrupt Service Routine.
 * 
 * Clears interrupt flags when a receive interrupt occurs.
 */
#pragma vector = USCIAB0RX_VECTOR
__interrupt void I2C_RX_ISR(void)
{
    // Clear specific interrupt flags
    UCB0STAT &= ~(UCSTPIFG | UCSTTIFG | UCNACKIFG);
}
