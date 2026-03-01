# 🚪 Day 27 – Smart PIR Gate Alert System with Raspberry Pi 🔔

**Raspberry Pi 4 | PIR Sensor | SSD1306 OLED | Servo Motor | Active-Low Buzzer**

Day 27 of my **30 Days - 30 Embedded Projects Challenge** focuses on building a complete motion-based smart gate alert system using Raspberry Pi and Embedded Linux GPIO control.

This project integrates motion detection, visual alerts, audio notification, and physical actuation into a simple embedded security prototype.

---

## 🔍 Project Overview

When motion is detected:

- OLED displays **“Motion Detected!”**
- Active-Low buzzer generates doorbell sound  
- LED indicator turns ON  
- System waits for button confirmation  
- Servo rotates to open the gate  
- Gate automatically closes after delay  
- System resets to ready state  

---

## 🔧 Hardware Components

- Raspberry Pi 4  
- HC-SR501 PIR Motion Sensor  
- 0.96" SSD1306 OLED Display (I2C)  
- SG90 Servo Motor  
- Active-Low Buzzer Module (3.3V powered)  
- Push Button  
- LED + 220Ω Resistor  
- External 5V supply for servo  

---

## 📍 GPIO Configuration (BCM Mode)

| Component | GPIO Pin |
|-----------|----------|
| PIR Sensor | 17 |
| Button | 23 |
| LED | 24 |
| Buzzer | 25 |
| Servo (PWM) | 18 |
| OLED SDA | 2 |
| OLED SCL | 3 |

---

## 🧠 Key Learning Outcomes

- PIR motion sensing and calibration  
- Handling Active-Low logic correctly  
- I2C OLED interfacing on Raspberry Pi  
- PWM-based servo control  
- Managing hardware noise and signal stability  
- Embedded Linux GPIO debugging  

---

## 🚀 Challenge Status

**Day 27 / 30 - Completed**  
Phase 4 - Embedded Linux & Edge Systems 🔥  

**Author**
Ratnakar Sahoo  
B.Tech Undergraduate  
30 Days – 30 Embedded Projects Challenge
