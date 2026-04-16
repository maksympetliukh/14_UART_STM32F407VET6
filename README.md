# USART TX/RX EXERCISE

## What this project is
This project was created to learn how USART interface works - its logic and core operating principles.
This project is developed accordingly to online course [(MCU1) Learn bare metal driver development using Embedded C: Writing drivers for STM32 GPIO,I2C,SPI,USART from scratch](https://www.udemy.com/course/mastering-microcontroller-with-peripheral-driver-development/)
by Kiran Nayak (FastBit Embedded Brain Academy).

## Goals
- learn the USART general architecture and registers
- learn how to develop USART driver and different APIs using specific MCU documentation
- learn TX and RX design and logic
- learn how to communicate two devices via USART interface
- learn blocking API for USART
- learn USART IRQ interruptions (non-blocking API)
- learn how to check this communication with different tools (minicom and Sealae Logic Analyzer)

## What actually 01_USART_STRING_BLOCKING_API does
- configure button GPIO peripherals
- configure USART GPIO peripherals (AF4)
- configure USART initiation 
- initiate all required peripherals
- enable USART interface
- handle the button
- send the data (TX)

## What actually 02_USART_TXRX_IRQ does
- configure button GPIO peripherals
- configure USART GPIO peripherals (AF4)
- configure USART initiation
- implement USART event callback logic 
- initiate all required peripherals
- enable USART interface
- configure USART IRQ
- enable USART Interruption
- handle the button
- send the data
- callback activates and handles the event interrupt
- receive the data
- callback activates and handles the event interrupt

## How to check whether signal is correct or not with logic analyzer
- connect devices (in my case it is STM32F407VET6 and STM32f401CCU6) via USART interface (TX, RX, GND, VCC)
- connect a logic analyzer (with breadboard)
- configure signal parameters (2 MHz and 10-50 MS\s)
- start transmission
- get a measure and explore whether it correct 

## How to check whether signal is correct or not with Minicom
- connect a device with USB-UART converter
- open a serial terminal with minicom:
```bash
sudo minicom -D /dev/ttyACM0 -b 11520
```
- send the data
- check the data in serial terminal

## Used devices
- MCU: **STM32F407VET6**
- MCU: **STM32F401CCU6**
- CPU: **ARM Cortex-M4**
- Logic Analyzer: **Sealae Logic Analyzer**
- Debugger: **ST-LINK V2.2**
- USB_UART converter: **WeAct v 1.0**

## Used software and documentation
- Programming language: **C**
- Implementation: **bare-metal**
- IDE: **STM32CubeIDE**
- Debug tool: **STM32CubeProgrammer**
- Analysis tool: **PulseView**
- Reference manual: **RM0090**
- Reference manual: **RM00368**
- User manual: **ARM Cortex-M4**
- Serial terminal: **Minicom**