# Day 11: RFID Based Smart Access Control System

For Day 11 of my **30 Days – 30 Projects** challenge, I built a **Smart Access Control System** using an ESP32 and RFID technology. This project simulates how modern offices, labs, and secure facilities manage entry using RFID cards.

---

## What This System Does

- Reads RFID card/tag using RC522 module  
- Compares scanned card UID with stored authorized UID  
- Grants access by rotating a servo motor (door unlock)  
- Denies access with a different buzzer alert  
- Provides serial monitor feedback for debugging and monitoring  

---

## How It Works

When an RFID card is placed near the reader:

1. The ESP32 reads the card’s **unique UID**
2. The UID is compared with the stored authorized UID
3. If it matches:
   - A short high-tone beep plays
   - Servo rotates to simulate door unlocking
   - After a delay, the servo returns to lock position
4. If it doesn’t match:
   - A long low-tone beep plays
   - Access is denied

---

## Components Used

- ESP32 Dev Board  
- RC522 RFID Module  
- RFID Card / Tag  
- SG90 Servo Motor  
- Passive Buzzer  
- Breadboard & Jumper Wires  

---

## Pin Connections

| Component | ESP32 Pin |
|----------|-----------|
| RC522 SDA (SS) | GPIO 5 |
| RC522 SCK | GPIO 18 |
| RC522 MOSI | GPIO 23 |
| RC522 MISO | GPIO 19 |
| RC522 RST | GPIO 22 |
| Servo Signal | GPIO 13 |
| Buzzer | GPIO 12 |
| RC522 VCC | 3.3V |
| RC522 GND | GND |
| Servo VCC | 5V |
| Servo GND | GND |

---

## What I Learned

- SPI communication with RFID module  
- Working with unique device identifiers (UID)  
- Building authentication logic in embedded systems  
- Generating tones without hardware PWM conflicts  
- Integrating sensors with actuators for security applications  

---

## Real-World Applications

This type of system is used in:

- Office access control systems  
- College attendance systems  
- Industrial entry management  
- Smart home door locks  
- Laboratory security systems  

---

## Platform Used

Simulation built using **Wokwi ESP32 Simulator**

---

### Day 11 Complete  
Stepping deeper into **embedded security systems and real-world authentication design** 

