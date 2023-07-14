/*
 * msp430_gpio_driver.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Casper
 */

#ifndef MSP430_GPIO_DRIVER_H_
#define MSP430_GPIO_DRIVER_H_


#include "main.h"

/*
 * PORT mode select(input or output)
 * @ref #define PORT_MODE_INPUT 0
 */
#define PORT_MODE_INPUT 0
#define PORT_MODE_OUTPUT 1
#define PORT_MODE_ALT_FUNC 2

#define PORT_ALT_FUNC_PRIMARY      (0x01) //CAHNGE IT LATER
#define PORT_ALT_FUNC_SECONDARY    (0x02)
#define PORT_ALT_FUNC_TERTIARY     (0x03)
#define PORT_MODE_IT_FALLING_E     (0x04)
#define PORT_MODE_IT_RISING_E      (0x05)

  /*
   * MSP_Port_selection
   */
//#define P1  1
//#define P2  2
//#define P3  3





/*
 * Possibles pins and their masking values
 * @GPIO_PIN_NUMBERS
 */

#define PORT_PIN_0                   (0x0001)
#define PORT_PIN_1                   (0x0002)
#define PORT_PIN_2                   (0x0004)
#define PORT_PIN_3                   (0x0008)
#define PORT_PIN_4                   (0x0010)
#define PORT_PIN_5                   (0x0020)
#define PORT_PIN_6                   (0x0040)
#define PORT_PIN_7                   (0x0080)
#define PORT_PIN_8                   (0x0100)
#define PORT_PIN_9                   (0x0200)
#define PORT_PIN_A                   (0x0400)
#define PORT_PIN_B                   (0x0800)
#define PORT_PIN_C                   (0x1000)
#define PORT_PIN_D                   (0x2000)
#define PORT_PIN_E                   (0x4000)
#define PORT_PIN_F                   (0x8000)


/*
 * Possibles pin modes
 * @GPIO_PIN_MODES
 */
#define  PORT_NOPULL        (0x00)   /*!< No Pull-up or Pull-down activation  */
#define  PORT_PULLUP        (0x01)   /*!< Pull-up activation                  */
#define  PORT_PULLDOWN      (0x02)   /*!< Pull-down activation*/





#define PORT_SET   1
#define PORT_RESET 0

#define ENABLE 1
#define DISABLE 0

#define GPIO_PIN_SET 0x01
#define GPIO_PIN_RESET 0x00




typedef struct
{
    uint8_t PORT_PinNumber;         /*!<possible pins from  @GPIO_PIN_NUMBERS>*/
    uint8_t PORT_PinMode;           /*!< possible values from @GPIO_PIN_MODES >*/
    uint8_t PORT_PinPuPdControl;
    uint8_t PORT_PinAltFunMode;
}PORT_PinConfig_t;


typedef struct
{
    PORT_RegDef_t *pPORTx;              /*!< This holds the base address of the GPIO port to which the pin belongs >*/
    PORT_PinConfig_t PORT_PinConfig;   /*!< This holds GPIO pin configuration settings >*/

}PORT_Handle_t;




void MSP_Port_Init(PORT_Handle_t *pPORTHandle);
MSP_Status_t MSP_Port_WritePin(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number, uint8_t state);
uint8_t MSP_Port_ReadPin(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number);
uint8_t MSP_Port_ReadPort(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number);
MSP_Status_t MSP_Port_TogglePin(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number);

void MSP_PORT_ClearInterrupt(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number);
uint16_t MSP_PORT_GetInterruptStatus(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number);
void MSP_PORT_DisableInterrupt(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number);
void MSP_PORT_EnableInterrupt(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number);
void MSP_PORT_SelectInterruptEdge(PORT_RegDef_t *pPORTx, uint8_t Port_Pin_Number,uint8_t Transition);

#endif /* MSP430_GPIO_DRIVER_H_ */
