# STM32 IoT Template with OTA Update and I2C LCD Integration

This project is an STM32-based IoT template that includes OTA update functionality using an ESP8266 module and displays update status on an I2C LCD. The project includes EEPROM initialization with default data and checks if the EEPROM is empty before filling it.

## Features

- **OTA Update**: Over-the-air update functionality using ESP8266.
- **I2C LCD**: Display update status on an I2C-connected LCD.
- **EEPROM Handling**: Initialize EEPROM with default data if it is empty.
- **Memory Optimization**: Configured to optimize code size for fitting in bootloader memory.

## Hardware Requirements

- STM32F103RCT6 microcontroller
- ESP8266 WiFi module
- I2C LCD
- EEPROM (I2C-based)

## Software Requirements

- STM32CubeIDE

## Getting Started

### Prerequisites

1. **Install STM32CubeIDE**
    - Download and install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).

### Project Setup

1. **Clone the Repository**
   ```sh
   git clone https://github.com/hidirektor/STM32-Template.git
   cd STM32-Template

2. **Open the Project in STM32CubeIDE**
    - Open STM32CubeIDE.
    - Click on File > Open Projects from File System....
    - Select the cloned project directory.
3. **Configure Build Settings**
    - Open the project properties.
    - Navigate to C/C++ Build -> Settings.
    - Select the Tool Settings tab.
    - Under MCU GCC Compiler, select Optimization.
    - Set the optimization level to -Os (optimize for size).

### Project Structure

    - main.c: Main entry point and initialization of peripherals.
    - EEPROM.h / EEPROM.c: EEPROM handling functions.
    - ESP8266.h / ESP8266.c: ESP8266 initialization and command handling functions.
    - OTA.h / OTA.c: OTA update handling functions.
    - LCD.h / LCD.c: I2C LCD control functions.
    - Globals.h / globals.c: Global variables and constants.