# Day 21 - Smart Keypad-Based Access Control System 🔐

This project is part of my **30 Days - 30 Embedded Projects Challenge**.

Day 21 focuses on **security systems, human–machine interaction, and IoT integration**, moving beyond sensor-only automation into **access control and authentication-based embedded design**.

---

## 🔍 Project Overview

This project implements a **Smart Access Control System** using an **ESP32**, a **4×4 keypad**, and a **servo motor** to simulate a door lock mechanism.

Users can unlock the system using a secure PIN entered via the keypad.  
The system provides **visual feedback (OLED + LEDs)**, **audio feedback (buzzer)**, enforces **limited attempts with lockout**, and allows **remote monitoring and control using the Blynk IoT platform**.

---

## ✨ Features

- PIN-based access control using 4×4 keypad  
- Servo-controlled locking and unlocking mechanism  
- OLED display for system status and user prompts  
- Red & Green LED status indicators  
- Active-LOW buzzer for feedback and alerts  
- Maximum 3 wrong attempts with automatic lockout  
- Secure PIN reset using keypad sequence  
- IoT-based remote unlock and monitoring via Blynk  
- Priority-based logic (Keypad > IoT)  

---

## 🧠 System Logic

### 🔐 Normal Operation
- User enters PIN via keypad  
- Correct PIN → Access granted  
- Wrong PIN → Attempt count increments  

### 🚫 Security Logic
- After **3 wrong attempts**:
  - System enters lockout state  
  - Red LED remains ON  
  - Keypad input disabled temporarily  

### 🔁 PIN Reset Logic
- PIN reset is triggered using a secure keypad sequence  
- New PIN is entered and confirmed via keypad  
- Reset is allowed only when system is not locked  

### ☁️ IoT Integration
- Remote unlock command via Blynk dashboard  
- Live monitoring of:
  - Lock status
  - Wrong attempts count
  - Lockout status
  - Last access result  

Keypad input always has **higher priority** than IoT commands to ensure physical security.

---

## 🔌 Hardware Components Used

- ESP32 Development Board  
- 4×4 Matrix Keypad (HX-543)  
- SG90 Mini Servo Motor  
- SSD1306 OLED Display (I2C)  
- Active-LOW Buzzer Module  
- 2 LEDs (Access Granted / Access Denied)  
- 330Ω resistors  
- Breadboard and jumper wires  

---

## 📍 Pin Configuration

### Keypad (HX-543)
| Function | ESP32 GPIO |
|-------|-----------|
| C1 | GPIO 13 |
| C2 | GPIO 12 |
| C3 | GPIO 14 |
| C4 | GPIO 27 |
| R1 | GPIO 26 |
| R2 | GPIO 25 |
| R3 | GPIO 33 |
| R4 | GPIO 32 |

### Other Connections
| Component | ESP32 GPIO |
|--------|-----------|
| Servo Signal | GPIO 18 |
| Buzzer OUT | GPIO 19 |
| Green LED | GPIO 4 |
| Red LED | GPIO 5 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

---

## ☁️ Blynk Virtual Pin Mapping

| Parameter | Virtual Pin |
|--------|------------|
| Lock Status | V0 |
| Remote Unlock | V1 |
| Wrong Attempts | V2 |
| Lockout Status | V3 |
| Last Access Result | V4 |
| Reset Lockout | V5 |

---

## 📊 Blynk Dashboard Overview

The Blynk Web Dashboard provides:
- Remote unlock control  
- Lockout reset for admin  
- Real-time lock status indication  
- Wrong attempt counter  
- Lockout active indication  
- Last access result display  

---

## 🎓 Learning Outcomes

- Matrix keypad interfacing with ESP32  
- Secure PIN-based authentication logic  
- State-machine design for embedded systems  
- Handling lockout and retry mechanisms  
- Servo motor control for locking systems  
- OLED-based user interface design  
- IoT integration using Blynk Cloud  
- Priority-based access control logic  

---

## 🔮 Future Improvements

- EEPROM-based PIN storage (persistent across power cycles)  
- Timestamped access logs  
- Multiple user PINs with roles  
- Mobile app notifications  
- RFID or biometric authentication integration  

---

## 🚀 Challenge Status

**Day 21 / 30 – Completed**  
Secure Embedded System with IoT Integration 🔐🚀

---

## 👤 Author

**Ratnakar Sahoo**  
B.Tech Undergraduate 
30 Days - 30 Embedded Projects Challenge
