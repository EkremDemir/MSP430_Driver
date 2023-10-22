# I2C Slave Transmit for MSP430G2553

## Overview
This code configures the MSP430G2553 microcontroller to operate as an I2C slave device. It provides functionality to transmit data to an I2C master, such as an STM32F4 board.

## Author
**Ekrem Demir**
**Ahmet Hakan Yıldız**

## Date
**23.10.2023**

## Features
- Configures the MSP430G2553 as an I2C slave with address `0x56`.
- Uses interrupt-driven data reception.
- Handles buffer overflow by resetting the buffer index.
- Transmit predefined data.

## Usage
1. Ensure that the MSP430G2553 is correctly connected to the I2C bus, with proper pull-up resistors on SDA and SCL lines.
2. Connect the I2C master (e.g., STM32F4 board) to the same I2C bus.
3. Load the code onto the MSP430G2553 using an appropriate programmer and development environment.
4. Start the I2C master to receive data to the MSP430G2553.
   
**Note:**  If you're using the MSP430G2553 Development Kit, keep in mind that P1.6 is multiplexed with LED2. To utilize P1.6 for I2C communication, ensure that you disconnect or remove the header connected to LED2 on the development kit. This will prevent any interference or unexpected behavior during I2C communication.

MSP430G2553         |       Other Device (e.g., STM32F4 board)
--------------------|------------------------
P1.7 (SDA)          |       SDA
P1.6 (SCL)          |       SCL

## Contributions
Feel free to contribute to this code by submitting pull requests or opening issues for enhancements, bug fixes, or any other feedback.
