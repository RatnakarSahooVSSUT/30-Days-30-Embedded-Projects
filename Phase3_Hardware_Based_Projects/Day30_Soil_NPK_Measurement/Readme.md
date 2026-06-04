# 🌱 Day 30: Smart Soil NPK Monitoring System using RS485 Modbus RTU 📡🌾

**ESP32 | RS485 NPK Sensor | MAX485 | OLED Display | Precision Agriculture**

This project is part of my **30 Days – 30 Embedded Projects Challenge**, a hands-on journey focused on building **real-world embedded systems** from scratch.

**Day 30** focuses on **industrial sensor communication, precision agriculture, environmental monitoring, and embedded data acquisition systems** using the Modbus RTU protocol.

---

![EMBEDDED](https://img.shields.io/badge/EMBEDDED-SYSTEMS-4B5563?style=for-the-badge)
![ESP32](https://img.shields.io/badge/ESP32-DEVELOPMENT-0EA5E9?style=for-the-badge)
![IOT](https://img.shields.io/badge/IOT-SMART%20AGRICULTURE-374151?style=for-the-badge)
![PROJECTS](https://img.shields.io/badge/PROJECTS-NPK%20MONITORING-65A30D?style=for-the-badge)
![30 DAYS](https://img.shields.io/badge/30%20DAYS-DAY%2030-4B5563?style=for-the-badge)
![30 PROJECTS](https://img.shields.io/badge/30%20PROJECTS-FINAL%20PROJECT-F97316?style=for-the-badge)
![HARDWARE](https://img.shields.io/badge/HARDWARE-RS485%20MODBUS-6B7280?style=for-the-badge)
![DEVELOPMENT](https://img.shields.io/badge/DEVELOPMENT-EMBEDDED%20SYSTEMS-EF4444?style=for-the-badge)

---

## 🔍 Project Overview

This project implements a **Smart Soil Nutrient Monitoring System** using an **ESP32**, an **RS485 NPK Soil Sensor**, a **MAX485 communication module**, and a **0.96" OLED Display**.

The system continuously measures and displays:

- 🌿 Nitrogen (N)
- 🌿 Phosphorus (P)
- 🌿 Potassium (K)

The sensor communicates using the **Modbus RTU protocol over RS485**, while the ESP32 processes and displays the nutrient values in real-time.

The project demonstrates practical implementation of **industrial communication protocols** in **smart agriculture applications**.

---

## ✨ Features

- 🌱 Real-time Nitrogen Monitoring
- 🌱 Real-time Phosphorus Monitoring
- 🌱 Real-time Potassium Monitoring
- 📡 RS485 Modbus RTU Communication
- 📟 OLED-Based Live Data Display
- ⚡ ESP32-Based Embedded System
- 🌾 Precision Agriculture Application
- 🔄 Continuous Soil Monitoring
- 📈 Expandable for IoT Cloud Platforms
- 🛠 Industrial Sensor Interfacing

---

## 🧠 System Logic

### 📡 Sensor Communication

- ESP32 communicates with the NPK sensor using RS485
- MAX485 converts RS485 signals into TTL UART signals
- Modbus RTU protocol is used for data exchange

### 🌱 Nutrient Acquisition

The sensor measures:

- Nitrogen Content (mg/kg)
- Phosphorus Content (mg/kg)
- Potassium Content (mg/kg)

### 📟 Data Visualization

The acquired values are displayed on:

- OLED Display
- Serial Monitor

allowing real-time soil nutrient analysis.

---

## 🔌 Hardware Components Used

- ESP32 Development Board
- RS485 NPK Soil Sensor
- MAX485 TTL-RS485 Converter Module
- SSD1306 OLED Display (0.96")
- 12V DC Power Supply
- Breadboard
- Jumper Wires

---

## 📍 Pin Configuration

### MAX485 Connections

| MAX485 Pin | ESP32 GPIO |
|------------|------------|
| RO | GPIO 16 |
| DI | GPIO 17 |
| RE | GPIO 4 |
| DE | GPIO 4 |
| VCC | 3.3V |
| GND | GND |

### OLED Connections

| OLED Pin | ESP32 GPIO |
|----------|------------|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VCC | 3.3V |
| GND | GND |

### NPK Sensor Connections

| Sensor Wire | Connection |
|------------|------------|
| Brown | +12V |
| Black | GND |
| Yellow/Grey | RS485 A |
| Blue | RS485 B |

---

## 📡 Modbus Communication Parameters

| Parameter | Value |
|------------|--------|
| Protocol | Modbus RTU |
| Baud Rate | 9600 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Device Address | 0x01 |

---

## 📊 Register Mapping

| Parameter | Register Address |
|------------|------------------|
| Nitrogen (N) | 0x001E |
| Phosphorus (P) | 0x001F |
| Potassium (K) | 0x0020 |

---

## 📺 Example Output

### OLED Display

```text
N: 3 mg/kg
P: 5 mg/kg
K: 10 mg/kg
````

### Serial Monitor

```text
N: 3 mg/kg
P: 5 mg/kg
K: 10 mg/kg
```

---

## 🛠️ Tech Stack

* ESP32
* Arduino IDE
* RS485 Communication
* Modbus RTU
* MAX485
* SSD1306 OLED
* Embedded C++
* Precision Agriculture

---

## 🎓 Learning Outcomes

* RS485 Communication Protocol
* Modbus RTU Implementation
* ESP32 UART Communication
* Industrial Sensor Interfacing
* OLED Display Programming
* Embedded Data Acquisition
* Real-Time Monitoring Systems
* Precision Agriculture Applications
* Hardware Debugging & Troubleshooting

---

## 🔮 Future Improvements

* ☁️ Blynk IoT Integration
* 📊 Cloud Data Logging
* 🚿 Smart Irrigation Automation
* 📱 Mobile Dashboard
* 🤖 AI-Based Soil Fertility Prediction
* 🌦 Weather-Aware Irrigation
* 🌍 Remote Agricultural Monitoring

---

## 🚀 Challenge Status

**Day 30 / 30 - Completed**

Smart Soil NPK Monitoring System using RS485 Modbus RTU 🌱📡🚀

---

## 👤 Author

**Ratnakar Sahoo**
B.Tech Undergraduate

**30 Days - 30 Embedded Projects Challenge** 🚀

```
