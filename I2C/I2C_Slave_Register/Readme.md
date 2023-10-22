
# I2C Slave Register Interaction for MSP430G2553

## Overview
This code configures the MSP430G2553 microcontroller to operate as an I2C slave device, capable of interacting with specific memory registers. An I2C master can write to and read from these memory registers using the provided addresses.

## Authors
**Ekrem Demir**  
**Ahmet Hakan Yıldız**

## Date
**22.10.2023**

## Features
- Configures the MSP430G2553 as an I2C slave with address `0x48`.
- Interrupt-driven I2C operations for both receiving (write) and transmitting (read) data.
- Supports interaction with specific memory register addresses.
- Uses inline functions `WritePin` and `ReadPin` to handle writing and reading of specific register addresses.

## Usage
1. Ensure the MSP430G2553 is correctly connected to the I2C bus, with proper pull-up resistors on the SDA and SCL lines.
2. Connect your I2C master device (e.g., STM32F4 board) to the same I2C bus.
3. Load the code onto the MSP430G2553 using an appropriate programmer and development environment.
4. Initiate communication from the I2C master to interact with the specific memory registers on the MSP430G2553.

**Note:** If using the MSP430G2553 Development Kit, remember that P1.6 might be multiplexed with other onboard peripherals. For pure I2C communication on P1.6 and P1.7, ensure no other conflicting peripherals are active.

Connection Table:

MSP430G2553         |       Other Device (e.g., STM32F4 board)
--------------------|------------------------
P1.7 (SDA)          |       SDA
P1.6 (SCL)          |       SCL

**Note:**  In master side I used stm32f407 discovery board. My infinite loop is;
	  do
	  {
		  status =  HAL_I2C_Mem_Write(&hi2c3, 0x48 << 1, 0x10, 1, &transmitData, 1, HAL_MAX_DELAY);
		  HAL_Delay(500);
		  status =  HAL_I2C_Mem_Read(&hi2c3, 0x48 << 1, 0x11, 1, &ReceivedData, 1, HAL_MAX_DELAY);
		  HAL_Delay(500);
	  }while(status != HAL_OK);
      HAL_Delay(1000);  // Delay for a second and repeat

## Contributions
Feel free to contribute to this code by submitting pull requests or opening issues for enhancements, bug fixes, or any other feedback.
