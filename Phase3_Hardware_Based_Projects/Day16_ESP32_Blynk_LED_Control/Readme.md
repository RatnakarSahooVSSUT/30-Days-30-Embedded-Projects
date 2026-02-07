# Day 16: ESP32 Hardware LED Control using Blynk IoT

## Project Overview
This project demonstrates a real hardware-based IoT system where an external LED connected to an ESP32 is controlled using the Blynk mobile application over Wi-Fi.

## Hardware Used
- ESP32 Dev Module
- LED
- 220Ω resistor
- Breadboard
- Jumper wires

## Circuit Connection
- GPIO 23 → 220Ω resistor → LED → GND

## Software & Platform
- Arduino IDE
- Blynk IoT platform
- Wi-Fi

## Working
- ESP32 connects to Wi-Fi and Blynk Cloud
- Mobile switch sends data via Virtual Pin V0
- ESP32 receives command and controls LED

## Learning Outcome
- Hands-on ESP32 GPIO control
- Hardware-based IoT implementation
- Blynk template and Virtual Pin usage
- Real-time mobile to hardware control

