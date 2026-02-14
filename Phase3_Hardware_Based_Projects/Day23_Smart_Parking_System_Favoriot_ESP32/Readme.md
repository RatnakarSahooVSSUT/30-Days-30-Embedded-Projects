# Day 23: Smart Parking Management System with IoT 🚗🅿️  
**ESP32 | IR Sensors | Servo Motor | OLED | Favoriot IoT**

This project is part of my **30 Days - 30 Embedded Projects Challenge**.

**Day 23** focuses on **smart infrastructure, safety-critical automation, and cloud-based monitoring**, implemented through an IoT-enabled smart parking system with email alerts.

---

## 🔍 Project Overview

This project implements a **Smart Parking Management System** using an **ESP32** that automatically monitors parking slot availability, controls an entry gate, ensures safety through obstruction detection, displays system status locally, and sends real-time data to the **Favoriot IoT platform**.

Critical events such as **parking full** and **gate obstruction** trigger **email notifications** via cloud rules.

---

## ✨ Features

- Automatic parking slot occupancy detection  
- Servo-controlled entry gate  
- Gate obstruction detection with safety override  
- OLED display for live system status  
- LED indicators for slot availability and parking full  
- Parking duration tracking per slot  
- Virtual vehicle count calculation  
- Favoriot IoT cloud integration  
- Email alerts for parking full and gate obstruction  

---

## 🔌 Circuit Connections

### IR Sensors
| Sensor Function | ESP32 GPIO |
|----------------|-----------|
| Slot 1 IR | GPIO 34 |
| Slot 2 IR | GPIO 35 |
| Entry IR | GPIO 32 |
| Gate Safety IR | GPIO 33 |

### Output Devices
| Component | ESP32 GPIO |
|----------|-----------|
| Servo Signal | GPIO 25 |
| Slot 1 Red LED | GPIO 12 |
| Slot 1 Green LED | GPIO 13 |
| Slot 2 Red LED | GPIO 14 |
| Slot 2 Green LED | GPIO 27 |
| Parking Full LED | GPIO 26 |

### OLED (I2C)
| Signal | ESP32 GPIO |
|-------|-----------|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## 🧠 System Logic

### 🚗 Parking Operation
- IR sensors detect vehicle presence in slots  
- Available parking spaces are calculated in real time  
- Entry gate opens automatically when space is available  

### 🚨 Safety Logic
- A dedicated IR sensor monitors obstruction under the gate  
- Gate opens immediately if obstruction is detected  
- Safety alert is latched and sent to the cloud  

### ☁️ IoT Integration
- ESP32 uploads structured data to Favoriot  
- Cloud rules evaluate conditions  
- Email notifications are triggered entirely from the cloud  

---

## 📧 Email Alert Logic (Favoriot Rules)

- **Parking Full Alert**  
  - Condition: `available == 0`  
  - Action: Send Email Notification  

- **Gate Obstruction Alert**  
  - Condition: `gate_obstruction == 1`  
  - Action: Send Email Notification  

Email notifications are handled entirely on the cloud, following proper IoT system architecture.

---

## 📊 OLED Display Information

The OLED displays:
- Slot 1 and Slot 2 occupancy  
- Available parking spaces  
- Gate status (**OPEN / CLOSED**)  
- Real-time system updates  

---

## 🎓 Learning Outcomes

- IR-based occupancy detection techniques  
- Servo motor control with safety interlocks  
- State-based embedded system design  
- Cloud data modeling for IoT platforms  
- Handling transient events using latching logic  
- Reliable alert generation using rule engines  
- Integration of local UI with cloud monitoring  

---

## 🔮 Future Improvements

- Support for multiple parking slots  
- Vehicle identification using RFID or camera  
- Mobile application dashboard  
- Usage analytics and reporting  
- Automated billing and payment integration  

---

## 🚀 Challenge Status

**Day 23 / 30 - Completed**  
Smart Parking Management System with IoT & Safety Alerts 🚗🅿️📡

---

## 👤 Author

**Ratnakar Sahoo**  
B.Tech Undergraduate  
**30 Days - 30 Embedded Projects Challenge**

