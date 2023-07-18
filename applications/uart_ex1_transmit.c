/*
 * uart_ex1_transmit.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Casper
 */

#include "main.h"

/*
 * UART_A0
 * P1.4 -> TX
 * P1.5 -> RX
 */

void UART_Transmit_Func(UART_Handle_t *UART_Handle);

void UART_EX1(){

    MSP_UART_PinSelect();

    UART_Handle_t UART_Handle;

    UART_Handle.pUARTx = UART_A0;

    UART_Handle.UART_Config.UART_Mode = UART_ASYNCH_MODE;
    UART_Handle.UART_Config.UART_AsynchronousMode = UART_ASYNCH_MODE_UART;
    UART_Handle.UART_Config.UART_LsbMsbSelect = UART_LSB_FIRST;
    UART_Handle.UART_Config.UART_CharLength = UART_LENGTH_8;
    UART_Handle.UART_Config.UART_ClockPrescalar = 8;
    UART_Handle.UART_Config.UART_NoOfStopBits = UART_STOP_BIT_1;
    UART_Handle.UART_Config.UART_ClockSource = UART_CLOCK_UCLK;
    UART_Handle.UART_Config.UART_ParityControl = UART_NON_PARITY;

    MSP_UART_Init(&UART_Handle);

    MSP_UART_Enable(&UART_Handle);

    MSP_UART_TransmitData(&UART_Handle, 0x55);
    delay_ms(100);
    UART_Transmit_Func(&UART_Handle);
}

void UART_Transmit_Func(UART_Handle_t *UART_Handle){
    while(1){
        MSP_UART_TransmitData(UART_Handle, 0x55);
        delay_ms(100);
    }
}
