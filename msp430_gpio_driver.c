/*
 * msp430_gpio_driver.c
 *
 *  Created on: Jul 13, 2023
 *      Author: Casper
 */

#ifndef MSP430_GPIO_DRIVER_C_
#define MSP430_GPIO_DRIVER_C_

#include <stdint.h>

/*
 * msp_gpio.c
 *
 *  Created on: 12 Tem 2023
 *      Author: night
 */

#include "main.h"



MSP_Status_t MSP_Port_WritePin(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number, uint8_t state)
{

    MSP_Status_t retVal= STATE_ERROR;

    if(pPORTx->PDIR & Port_Pin_Number)   //make sure port is output
    {

        switch (state) {
            case GPIO_PIN_SET:
                pPORTx->POUT |= Port_Pin_Number;   // Set pin as high
                retVal = STATE_OK;
                break;

            case GPIO_PIN_RESET:
                pPORTx->POUT &= ~(Port_Pin_Number); // set pin as low
                retVal = STATE_OK;
                break;

            default:
                break;
        }
    }

    return retVal;
}

MSP_Status_t MSP_Port_TogglePin(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number)
{
    MSP_Status_t retVal= STATE_ERROR;

    if(pPORTx->PDIR & Port_Pin_Number)   //make sure port is output
    {
        retVal = STATE_OK;
        pPORTx->POUT ^= Port_Pin_Number;   // Toggle the pin
    }

    return retVal;
}

void MSP_Port_Init(PORT_Handle_t *pPORTHandle)
{


    EnorDiGPIO(ENABLE);

    //Configure the mode selection
    switch(pPORTHandle->PORT_PinConfig.PORT_PinMode)
    {
        case PORT_MODE_OUTPUT:
        {
            pPORTHandle->pPORTx->POUT &= ~(pPORTHandle->PORT_PinConfig.PORT_PinNumber); //Clear output pin state
            pPORTHandle->pPORTx->PDIR |= pPORTHandle->PORT_PinConfig.PORT_PinNumber;    // Set Pin state as output
            break;
        }
        case PORT_MODE_INPUT:
        {
            pPORTHandle->pPORTx->PDIR &= ~(pPORTHandle->PORT_PinConfig.PORT_PinNumber); // Set Pin state as input

            // Configuration for pull up/down resistors
            if(pPORTHandle->PORT_PinConfig.PORT_PinPuPdControl == PORT_NOPULL)
            {
                //pass
            }
            else if(pPORTHandle->PORT_PinConfig.PORT_PinPuPdControl == PORT_PULLUP)  // Select Pull up
            {
                pPORTHandle->pPORTx->PREN |= pPORTHandle->PORT_PinConfig.PORT_PinNumber;
                pPORTHandle->pPORTx->POUT |= pPORTHandle->PORT_PinConfig.PORT_PinNumber;
            }
            else if(pPORTHandle->PORT_PinConfig.PORT_PinPuPdControl == PORT_PULLDOWN)  // Select Pull down
            {
                pPORTHandle->pPORTx->PREN |= pPORTHandle->PORT_PinConfig.PORT_PinNumber;
                pPORTHandle->pPORTx->POUT &= ~(pPORTHandle->PORT_PinConfig.PORT_PinNumber);
            }
            else
            {
                //pass
            }
            break;
        }
        case PORT_MODE_ALT_FUNC:   //  configuration for the alternate function should be done in the peripheral's driver!!DDDD
        {
            // Set pin to alternate function mode
            switch(pPORTHandle->PORT_PinConfig.PORT_PinAltFunMode)
            {
                case PORT_ALT_FUNC_PRIMARY:
                {
                    pPORTHandle->pPORTx->PSEL0 |= pPORTHandle->PORT_PinConfig.PORT_PinNumber;
                    pPORTHandle->pPORTx->PSEL1 &= ~(pPORTHandle->PORT_PinConfig.PORT_PinNumber);
                    break;
                }
                case PORT_ALT_FUNC_SECONDARY:
                {
                    pPORTHandle->pPORTx->PSEL0 &= ~(pPORTHandle->PORT_PinConfig.PORT_PinNumber);
                    pPORTHandle->pPORTx->PSEL1 |= pPORTHandle->PORT_PinConfig.PORT_PinNumber;
                    break;
                }
                case PORT_ALT_FUNC_TERTIARY:
                {
                    pPORTHandle->pPORTx->PSELC |= pPORTHandle->PORT_PinConfig.PORT_PinNumber; // Use the PxSELC register to set both PxSEL1 and PxSEL0 simultaneously
                    break;
                }
                default:
                {
                    //pass
                    break;
                }
            }

            break;
        }
        default:
        {
            //pass
            break;
        }
    }
}


uint8_t MSP_Port_ReadPin(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number)
{
    uint8_t read = (uint8_t)(pPORTx->PIN & Port_Pin_Number);
    return read;
}

uint8_t MSP_Port_ReadPort(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number)
{
    uint8_t read = (uint8_t)(pPORTx->PIN);
    return read;
}


#endif /* MSP430_GPIO_DRIVER_C_ */
