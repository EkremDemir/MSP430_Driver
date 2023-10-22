/**
 * @file i2c_slave_receive.c
 * @author Ekrem Demir
 * @date 22.10.2023
 * @brief MSP430G2553 I2C slave code to interact with specific registers.
 */

#include <msp430.h>
#include <stdint.h>

// Constants
#define SLAVE_ADDRESS          0x48
#define TRANSMIT_BUFFER_SIZE   32
#define RECEIVE_BUFFER_SIZE    32

#define REGISTER_ADRESS_1      0x10
#define REGISTER_ADRESS_2      0x11

// Global Variables
uint8_t receiveData = 0;
uint8_t transmitData = 0x50;
uint8_t memAddressReceivedFlag = 1;
uint8_t RegisterAdress = 0;

// Function Prototypes
static void InitializeI2CSlave(void);
static inline void WritePin(uint8_t RegisterAddress, uint8_t data);
static inline uint8_t ReadPin(uint8_t RegisterAddress);

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

    // Enable software reset, set I2C Slave mode, and synchronous mode
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = UCMODE_3 | UCSYNC;

    // Set the I2C slave's own address
    UCB0I2COA = SLAVE_ADDRESS;

    // Release from software reset and enable relevant I2C interrupts
    UCB0CTL1 &= ~UCSWRST;
    UCB0I2CIE |= UCSTPIE | UCSTTIE;
    IE2 |= UCB0TXIE | UCB0RXIE;

    // Clear interrupt flags
    IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);
}

/**
 * @brief I2C Transmit Interrupt Service Routine.
 *
 * Responds to both read and write requests from the I2C master.
 */
#pragma vector = USCIAB0TX_VECTOR
__interrupt void I2C_TX_ISR(void)
{
    // If UCTR = 0, it's a Receive operation (Master is writing to Slave)
    if(!(UCB0CTL1 & UCTR))
    {
        if(IFG2 & UCB0RXIFG) // Check if a byte has been received
        {
            if(memAddressReceivedFlag) // If true, the master sends a memory address
            {
                RegisterAdress = UCB0RXBUF;
                memAddressReceivedFlag = 0; // Indicate that next byte is data
            }
            else
            {
                receiveData = UCB0RXBUF; // Store the data received from master
                WritePin(RegisterAdress, receiveData); // Write data based on the given register address
            }
        }
    }
    // If UCTR = 1, it's a Transmit operation (Master is reading from Slave)
    else if(IFG2 & UCB0TXIFG)
    {
        UCB0TXBUF = ReadPin(RegisterAdress); // Load the transmit buffer with data from the given register address
    }

    // Clear transmit and receive interrupt flags
    IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void I2C_RX_ISR(void)
{
    if(UCB0STAT & UCSTTIFG) // Check for start condition
    {
        memAddressReceivedFlag = 1; // Indicate that the next byte received will be a memory address
    }

    // Clear start and stop condition interrupt flags
    UCB0STAT &= ~(UCSTPIFG | UCSTTIFG | UCNACKIFG);
}

/**
 * @brief Writes a value to a specific register.
 *
 * @param RegisterAddress The register address.
 * @param data The data to write.
 */
static inline void WritePin(uint8_t RegisterAddress, uint8_t data)
{
    switch (RegisterAddress) {
        case REGISTER_ADRESS_1:
            P1OUT |= data;
            break;
        // Additional cases for other registers can be added here
        default:
            break;
    }
}

/**
 * @brief Reads a value from a specific register.
 *
 * @param RegisterAddress The register address.
 * @return The data read from the register.
 */
static inline uint8_t ReadPin(uint8_t RegisterAddress)
{
    uint8_t data = 0;

    switch (RegisterAddress) {
        case REGISTER_ADRESS_2:
            data = P1OUT;
            break;
        // Additional cases for other registers can be added here
        default:
            break;
    }

    return data;
}
