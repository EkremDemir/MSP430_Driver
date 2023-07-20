#include "main.h"
void delay_ms(uint16_t time);


TIM_Handle_t htim0;
PORT_Handle_t p1;

void TIM_Init(void);
void Port_Init(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    TIM_Init();
    Port_Init();
    while(1)
    {
        if(MSP_READ_IFG(&htim0))
        {
            MSP_Port_TogglePin(PORT1, PORT_PIN_0);
        }
    }
}

void delay_ms(uint16_t time)
{
    while(time)
    {
        __delay_cycles(1000);  //By default clock is 1 MHZ. Hence 1 tick is 1us. 1ms means 1000 ticks.
        --time;
    }
}


void TIM_Init(void)
{
    htim0.pTIMx = TIM0A3;
    htim0.TIM_BaseConfig.Tim_Mode = TIM_MODE_UP;
    htim0.TIM_BaseConfig.Tim_ClockSource = TIM_CLK_SMCLK;
    htim0.TIM_BaseConfig.Tim_ClockDivider =TIM_CLK_DIV_8;
    htim0.TIM_BaseConfig.Tim_CCR0_Value = 32768;

    MSP_Tim_BaseInit(&htim0);
    //htim0.TIM_BaseConfig.Tim_CCR0_Value
}



void Port_Init(void)
{
    p1.pPORTx = PORT1;
    p1.PORT_PinConfig.PORT_PinMode = PORT_MODE_OUTPUT;
    p1.PORT_PinConfig.PORT_PinNumber = PORT_PIN_0;
    p1.PORT_PinConfig.PORT_PinPuPdControl = PORT_NOPULL;

    MSP_Port_Init(&p1);
}
