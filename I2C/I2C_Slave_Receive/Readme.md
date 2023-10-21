# I2C Slave Receive for MSP430G2553

## Overview
This code configures the MSP430G2553 microcontroller to operate as an I2C slave device. It provides functionality to receive data from an I2C master, such as an STM32F4 board. The received data is stored in a buffer for further processing or analysis.

## Author
**Ekrem Demir**

## Date
**22.10.2023**

## Features
- Configures the MSP430G2553 as an I2C slave with address `0x48`.
- Uses interrupt-driven data reception.
- Stores received data in a buffer to prevent data loss during continuous transmission.
- Handles buffer overflow by resetting the buffer index.
- Initializes an LED on pin P1.0 for potential status indication or debugging.

## File Structure
- **I2C slave receive.c**: Contains the main program logic, including initialization and interrupt service routines.

## Usage
1. Ensure that the MSP430G2553 is correctly connected to the I2C bus, with proper pull-up resistors on SDA and SCL lines.
2. Connect the I2C master (e.g., STM32F4 board) to the same I2C bus.
3. Load the code onto the MSP430G2553 using an appropriate programmer and development environment.
4. Start the I2C master to send data to the MSP430G2553.

## Notes
- The default I2C slave address is set to `0x48`. Ensure the I2C master uses the same address when transmitting data.
- Received data is stored in the `receiveBuffer` array. Ensure that the buffer size (`RECEIVE_BUFFER_SIZE`) is sufficient for your application.
- If the buffer overflows, the buffer index is reset, and data starts overwriting from the beginning.

## Contributions
Feel free to contribute to this code by submitting pull requests or opening issues for enhancements, bug fixes, or any other feedback.
