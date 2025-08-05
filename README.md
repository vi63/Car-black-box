# Car Black Box System

This project is a **Car Black Box** system implemented in embedded C. It functions similarly to an aircraft black box and is designed to record and monitor critical parameters of a vehicle during its operation. 
In the event of an accident, this system helps investigators determine the cause.

## Project Objective

To develop an embedded system that continuously logs vehicle data like speed, engine status, and time, and stores them securely for post-accident analysis.

##  Features

- **Real-time Clock (RTC)** integration using ds1307.c to timestamp data
- **LCD Display (CLCD)** for dashboard outputs
- **Analog-to-Digital Converter (ADC)** for speed and sensor readings
- **User authentication** and password protection
- **Data logging and retrieval** via serial communication
- **Change password and clear log** functionalities

##  Project Structure
BLACK_BOX/
├── adc.c / adc.h # ADC module for reading analog inputs
├── clcd.c / clcd.h # Character LCD interface
├── ds1307.c # RTC interface
├── dashboard.c # Dashboard functionality
├── change_pwd.c # Change password feature
├── clear_log.c # Clear stored log data
├── download.c # Data download over UART
├── main.c # Main program flow


## ⚙️ Hardware Components

- 8051 Microcontroller/ATMEGA 328p
- RTC Module (DS1307)
- 16x2 Character LCD
- Speed Sensor
- UART/USB Interface
- Push Buttons (for user input)
- EEPROM (for data storage)

## 🚀 How It Works

1. The system starts and authenticates the user via password.
2. Speed and timestamp are recorded continuously.
3. Data is displayed on the CLCD in real time.
4. Data can be downloaded using serial communication.
5. Optional: Logs can be cleared or password can be changed via menu options.

## 🔐 Security

- Password-based access for data retrieval and system configuration.
- Password stored in EEPROM.

## Compilation & Deployment

You can compile the project using any embedded C compiler (e.g., Keil µVision) and flash the binary to a suitable microcontroller.


// Example: Compile with Keil for 8051 or MPLABXIDE





