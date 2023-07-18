/*
 * msp430_uart_driver.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Casper
 */

#include <stdint.h>
#include "main.h"


void MSP_UART_Init(UART_Handle_t *pUARTHandle){

    /* First Reset, Disables UART Communication
     * To avoid unpredictable behavior, configure or reconfigure
     * the eUSCI_A module when UCSWRST is set
     */
    pUARTHandle->pUARTx->UCCTLW0 |= UCSWRST;

    /* Synchronous/Asynchronous mode select */
    switch (pUARTHandle->UART_Config.UART_Mode) {
        case UART_ASYNCH_MODE:
            pUARTHandle->pUARTx->UCCTLW0 &= ~UCSYNC; // asynch mode
            break;
        case UART_SYNCH_MODE:
            pUARTHandle->pUARTx->UCCTLW0 |= UCSYNC; // synch mode
            break;
        default:
            break;
    }

    /* Asynchronous Mode Select */
    switch (pUARTHandle->UART_Config.UART_AsynchronousMode) {
        case UART_ASYNCH_MODE_UART:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0600; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCMODE_0; // uart mode
            break;
        case UART_ASYNCH_MODE_ILMM:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0600; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCMODE_1; // ilmm mode
            break;
        case UART_ASYNCH_MODE_AMM:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0600; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCMODE_2; // amm mode
            break;
        case UART_ASYNCH_MODE_AUTO_BR:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0600; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCMODE_3; // auto br mode
            break;
        default:
            break;
    }

    /* Specify Baud Rate */
    pUARTHandle->pUARTx->UCBR |= pUARTHandle->UART_Config.UART_ClockPrescalar;

    /* LSB/MSB First */
    switch (pUARTHandle->UART_Config.UART_LsbMsbSelect) {
        case UART_LSB_FIRST:
            pUARTHandle->pUARTx->UCCTLW0 &= ~UCMSB; // lsb first
            break;
        case UART_MSB_FIRST:
            pUARTHandle->pUARTx->UCCTLW0 |= UCMSB; // msb first
            break;
        default:
            break;
    }

    /* Character Length */
    switch (pUARTHandle->UART_Config.UART_CharLength) {
        case UART_LENGTH_8:
            pUARTHandle->pUARTx->UCCTLW0 &= ~UC7BIT; // 8 bit data
            break;
        case UART_LENGTH_7:
            pUARTHandle->pUARTx->UCCTLW0 |= UC7BIT; // 7 bit data
            break;
        default:
            break;
    }


    /* Stop Bit Select */
    switch (pUARTHandle->UART_Config.UART_NoOfStopBits) {
        case UART_STOP_BIT_1:
            pUARTHandle->pUARTx->UCCTLW0 &= ~UCSPB; // 1 stop bit
            break;
        case UART_STOP_BIT_2:
            pUARTHandle->pUARTx->UCCTLW0 |= UCSPB; // 2 stop bit
            break;
        default:
            break;
    }

    /* Clock Source Select */
    switch (pUARTHandle->UART_Config.UART_ClockSource) {
        case UART_CLOCK_UCLK:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0C00; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCSSEL_0; // UCLK
            break;
        case UART_CLOCK_DEV_SPESIFIC:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0C00; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCSSEL_1; // device specific
            break;
        case UART_CLOCK_SMCLK1:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0C00; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCSSEL_2; // smclk
            break;
        case UART_CLOCK_SMCLK2:
            pUARTHandle->pUARTx->UCCTLW0 &= ~0x0C00; // clear bits
            pUARTHandle->pUARTx->UCCTLW0 |= UCSSEL_3; // smclk
            break;
        default:
            break;
    }


    /* Parity Settings */
    switch (pUARTHandle->UART_Config.UART_ParityControl) {
        case UART_NON_PARITY:
            pUARTHandle->pUARTx->UCCTLW0 &= ~UCPEN; // parity disable
            break;
        case UART_ODD_PARITY:
            pUARTHandle->pUARTx->UCCTLW0 |= UCPEN; // parity enable
            pUARTHandle->pUARTx->UCCTLW0 &= ~UCPAR; // odd parity
            break;
        case UART_EVEN_PARITY:
            pUARTHandle->pUARTx->UCCTLW0 |= UCPEN; // parity enable
            pUARTHandle->pUARTx->UCCTLW0 |= UCPAR; // even parity
            break;
        default:
            break;
    }

}

void MSP_UART_Enable(UART_Handle_t *pUARTHandle)
{
    pUARTHandle->pUARTx->UCCTLW0 &= ~UCSWRST;
}

void MSP_UART_Disable(UART_Handle_t *pUARTHandle)
{
    pUARTHandle->pUARTx->UCCTLW0 |= UCSWRST;
}

void MSP_UART_TransmitData(UART_Handle_t *pUARTHandle, uint8_t transmitData)
{
    /* If interrupts are not enabled, wait for flags to set */
    if(!(pUARTHandle->pUARTx->UCIE & UCTXIE)){
        /* If TXIFG is set, it means tx buffer is empty */
        while(!(pUARTHandle->pUARTx->UCIFG & UCTXIFG));
    }

    pUARTHandle->pUARTx->UCTXBUF = transmitData;
}

uint8_t MSP_UART_ReceiveData(UART_Handle_t *pUARTHandle)
{
    uint8_t receivedData;

    /* If interrupts are not enabled, wait for flags to set */
    if(!(pUARTHandle->pUARTx->UCIE) & UCRXIE){
        /* If RXIFG is set, it means data in rx buffer */
        while(!(pUARTHandle->pUARTx->UCIFG & UCRXIFG));
    }

    receivedData = pUARTHandle->pUARTx->UCRXBUF;
    return receivedData;
}

void MSP_UART_EnableInterrupt(UART_Handle_t *pUARTHandle, uint8_t interruptMode)
{

    switch (interruptMode) {
        case UART_RECEIVE_INTERRUPT:
            pUARTHandle->pUARTx->UCIE |= UART_RECEIVE_INTERRUPT;
            break;
        case UART_TRANSMIT_INTERRUPT:
            pUARTHandle->pUARTx->UCIE |= UART_TRANSMIT_INTERRUPT;
            break;
        case UART_STARTBIT_INTERRUPT:
            pUARTHandle->pUARTx->UCIE |= UART_STARTBIT_INTERRUPT;
            break;
        case UART_TRANSMIT_COMPLETE_INTERRUPT:
            pUARTHandle->pUARTx->UCIE |= UART_RECEIVE_INTERRUPT;
            break;
        case UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT:
            pUARTHandle->pUARTx->UCCTLW0 |= UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT;
            break;
        case UART_BREAKCHAR_INTERRUPT:
            pUARTHandle->pUARTx->UCCTLW0 |= UART_BREAKCHAR_INTERRUPT;
            break;
        default:
            break;
    }
}

void MSP_UART_DisableInterrupt(UART_Handle_t *pUARTHandle, uint8_t interruptMode)
{

    switch (interruptMode) {
        case UART_RECEIVE_INTERRUPT:
            pUARTHandle->pUARTx->UCIE &= ~UART_RECEIVE_INTERRUPT;
            break;
        case UART_TRANSMIT_INTERRUPT:
            pUARTHandle->pUARTx->UCIE &= ~UART_TRANSMIT_INTERRUPT;
            break;
        case UART_STARTBIT_INTERRUPT:
            pUARTHandle->pUARTx->UCIE &= ~UART_STARTBIT_INTERRUPT;
            break;
        case UART_TRANSMIT_COMPLETE_INTERRUPT:
            pUARTHandle->pUARTx->UCIE &= ~UART_TRANSMIT_COMPLETE_INTERRUPT;
            break;
        case UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT:
            pUARTHandle->pUARTx->UCCTLW0 &= ~UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT;
            break;
        case UART_BREAKCHAR_INTERRUPT:
            pUARTHandle->pUARTx->UCCTLW0 &= ~UART_BREAKCHAR_INTERRUPT;
            break;
        default:
            break;
    }
}

uint8_t MSP_UART_GetInterruptStatus(UART_Handle_t *pUARTHandle, uint8_t interruptMode)
{
    return (pUARTHandle->pUARTx->UCIFG & interruptMode);
}

void MSP_UART_ClearInterrupt(UART_Handle_t *pUARTHandle, uint8_t interruptMode)
{
    pUARTHandle->pUARTx->UCIFG &= ~interruptMode;
}

void MSP_UART_PinSelect(){

    // pin select
    SYSCFG2 &= ~ADCPCTL4;
    P1SEL0 |=  PORT_PIN_4;
    P1SEL1 &= ~PORT_PIN_4;
    // output (tx channel, P1.4)
    PORT1->PDIR |= PORT_PIN_4;

    // pin select
    SYSCFG2 &= ~ADCPCTL5;
    P1SEL0 |=  PORT_PIN_5;
    P1SEL1 &= ~PORT_PIN_5;
    // input (rx channel, P1.5)
    PORT1->PDIR &= ~PORT_PIN_5; // input



}
