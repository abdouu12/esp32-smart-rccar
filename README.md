# esp32-smart-rccar
A Wi-Fi-controlled RC car powered by an ESP32, with live video streaming via an ESP32-CAM. The car is controlled through a web-based interface hosted on the ESP32, using HTTP requests to drive motors via PWM. This repo includes firmware, hardware setup, and code for web-based navigation and video streaming.


# How to use it:

make sure have the following:
## hardware:
### Microcontrollers & Electronics:
ESP MCU  (I used the ESP32-WROOM32)
ESP-CAM
### Motors & Drivers:
4x DC Motors (6V) - TT gear motors for movement
1x Stepper Motor OR Servo Motor - For additional movement (e.g., camera pan/tilt)
Stepper Motor Driver (if using stepper motor) - Required for stepper motor control
DC Motor Driver - To control the DC motors (e.g., L298N, L293D, or similar)
### Power:
2 to 4 18650 Batteries - Power source for ESP32 and motors
Battery Holder - To securely hold the batteries
voltage regulator
## software:
Make sure you have the following software installed:
Arduino IDE (with ESP32 board support) OR
Espressif IDE (ESP-IDF) for a more advanced development setup

## Setting Up the Car
Follow the schematic provided in the repository for detailed wiring connections.
Flash the ESP32 firmware for motor control and web-based navigation.
Flash the ESP32-CAM firmware for video streaming.

## Learn More
For a detailed explanation of the components and mechanics of the car, check out my blog post! 








