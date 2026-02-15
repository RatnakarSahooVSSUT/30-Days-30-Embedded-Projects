# Day 24: Touch-Based Smart Access Control System with IoT 🔐📲  
**ESP32 | Capacitive Touch Authentication | Servo Lock | Blynk Cloud**

This project is part of my **30 Days – 30 Embedded Projects Challenge**, a hands-on journey focused on building **real-world embedded systems** from scratch.

**Day 24** introduces a **touch-based authentication mechanism** for access control, replacing traditional keypads with a **time-based PIN system**.  
The project combines **embedded security logic**, **physical actuation**, and **IoT cloud monitoring** into a single, practical system.

---

## 🔍 Project Overview

This project implements a **Touch-Based Smart Access Control System** using an **ESP32**, a **capacitive touch sensor**, and an **SG90 servo motor** to simulate a smart door lock.

Users authenticate by **holding a touch sensor for specific durations**, forming a secure **4-step time-based PIN**.  
The system features **local-first security**, **clear user feedback**, and **remote monitoring & control** via **Blynk IoT**.

---

## ✨ Features

- ⏱️ **Touch-duration-based PIN authentication** (4-step PIN)
- 📟 **Live touch counter** displayed on OLED
- 🔒 **Servo-controlled lock/unlock mechanism**
- 🖥️ **OLED user interface** for system prompts & status
- 🟥🟢 **Red & Green LED indicators** for access status
- 🔊 **Active-LOW buzzer** for feedback and alerts
- 🚫 **3-attempt security lockout** to prevent brute force
- 🔁 **Secure PIN change mode** using a predefined touch pattern
- ☁️ **IoT-based remote unlock & monitoring** via Blynk
- 🕒 **NTP-based timestamp logging** for access events
- 🧠 **Priority-based control logic** (Physical access > IoT)

---

## 🧠 System Logic

### 🔐 Normal Operation
- User touches and holds the sensor to generate a PIN digit
- Touch duration (0–9 seconds) represents one digit
- Four sequential touch inputs form the complete PIN
- Correct PIN → Access granted

### 🚫 Security Logic
- Each wrong PIN increments an internal counter
- After **3 wrong attempts**:
  - System enters **lockout state**
  - Touch input is temporarily disabled
  - Red LED remains ON
  - Audible alert is triggered

### 🔁 PIN Reset Logic
- PIN reset is initiated using a **secure touch pattern**
- New PIN is entered using the same touch-duration method
- PIN reset is allowed **only when the system is not locked**

---

## ☁️ IoT Integration (Blynk Cloud)

The system integrates with **Blynk IoT** for remote visibility and control:

- 📲 Remote unlock capability
- 📊 Live monitoring of:
  - Lock status
  - Wrong attempt count
  - Lockout state
  - Last access result with timestamp
- 🔁 Admin-controlled lockout reset

> **Security Priority:** Physical touch input always has higher priority than IoT commands to prevent remote misuse.

---

## 🔌 Hardware Components Used

- ESP32 Development Board
- Capacitive Touch Sensor (TTP223 or equivalent)
- SG90 Mini Servo Motor
- SSD1306 OLED Display (I2C)
- Active-LOW Buzzer Module
- Red LED & Green LED
- 330 Ω resistors
- Breadboard and jumper wires

---

## 📍 Pin Configuration

### Touch Sensor

| Function | ESP32 GPIO |
|--------|------------|
| Touch Output | GPIO 4 |

### Other Connections

| Component | ESP32 GPIO |
|---------|------------|
| Servo Signal | GPIO 26 |
| Buzzer (Active-LOW) | GPIO 18 |
| Green LED | GPIO 23 |
| Red LED | GPIO 19 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

---

## ☁️ Blynk Virtual Pin Mapping

| Parameter | Virtual Pin |
|---------|-------------|
| Lock Status | V0 |
| Remote Unlock | V1 |
| Wrong Attempts | V2 |
| Lockout Status | V3 |
| Last Access Result (Timestamped) | V4 |
| Reset Lockout | V5 |

---

## 📊 Blynk Dashboard Overview

The Blynk Web Dashboard enables:

- Remote unlock control
- Admin lockout reset
- Real-time lock status indication
- Wrong attempt counter
- Lockout active indication
- Timestamped access event display

---

## 🎓 Learning Outcomes

- Capacitive touch interfacing with ESP32
- Time-based authentication and UX design
- Embedded finite-state-machine implementation
- Secure access control and lockout mechanisms
- Servo motor control for physical systems
- OLED-based embedded UI design
- IoT integration using Blynk Cloud
- NTP-based time synchronization
- Priority-based access control architecture

---

## 🔮 Future Improvements

- EEPROM-based PIN storage (persistent across power cycles)
- Multiple user profiles with role-based access
- Mobile notifications on access events
- Access history analytics and export
- RFID / biometric authentication integration
- Battery backup and power-failure handling

---

## 🚀 Challenge Status

**Day 24 / 30 - Completed**  
Touch-Based Smart Access Control with IoT Integration 🔐📲🚀

---

## 👤 Author

**Ratnakar Sahoo**  
B.Tech Undergraduate  
**30 Days - 30 Embedded Projects Challenge**

