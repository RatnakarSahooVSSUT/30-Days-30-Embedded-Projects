# 🌱 Day 22: Smart Soil Health & Climate-Aware Irrigation Decision System

This project is part of my **30 Days - 30 Embedded Projects Challenge**.

Day 22 focuses on **smart agriculture, environmental sensing, and IoT-based data analytics**, moving beyond simple sensor monitoring into **decision-oriented embedded system design**.

---

## 🔍 Project Overview

This system monitors **soil moisture, temperature, and humidity** using an **ESP32** and provides **real-time insights and irrigation recommendations** without directly controlling a pump.

The project integrates:
- Edge-level decision logic
- Visual feedback using LEDs and OLED
- Cloud-based monitoring with **Blynk IoT**
- Historical trend visualization for data-driven analysis

The goal is to demonstrate **intelligent sensing and sustainable water usage**, not just automation.

---

## ✨ Key Features

- Soil moisture measurement with **percentage conversion**
- 3-level soil condition indication using LEDs:
  - 🔴 Dry
  - 🟡 Optimal
  - 🟢 Wet
- Temperature & humidity monitoring (DHT sensor)
- OLED display for live system status
- Climate-aware irrigation recommendation logic
- IoT dashboard using **Blynk Cloud**
- **3-plot historical trend graph**:
  - Soil Moisture (%)
  - Temperature (oC)
  - Humidity (%)
- Scalable design (ready for relay/pump integration later)

---

## 🧠 System Logic

### 🌱 Soil Classification
- `< 30%` → Dry  
- `30–70%` → Optimal  
- `> 70%` → Wet  

### 💡 Decision Logic
- Dry + High temperature + Low humidity → **WATER NOW**
- Dry only → **WAIT**
- Wet → **BLOCK**
- Optimal → **SOIL OK**

---

## 🔌 Hardware Components Used

- ESP32 (30-pin Dev Module)
- Capacitive Soil Moisture Sensor (Analog)
- DHT11 / DHT22 Temperature & Humidity Sensor
- SSD1306 OLED Display (I2C)
- 3 LEDs (Red, Yellow, Green)
- 330Ω resistors
- Breadboard & jumper wires

---

## 📍 Pin Configuration

### Soil Moisture Sensor
| Signal | ESP32 GPIO |
|------|-----------|
| AO | GPIO 34 |

### DHT Sensor
| Signal | ESP32 GPIO |
|------|-----------|
| DATA | GPIO 27 |

### LEDs
| LED | Purpose | GPIO |
|---|---|---|
| Red | Dry | GPIO 13 |
| Yellow | Optimal | GPIO 12 |
| Green | Wet | GPIO 14 |

### OLED (I2C)
| Signal | ESP32 GPIO |
|------|-----------|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## ☁️ Blynk Virtual Pin Mapping

| Parameter | Virtual Pin |
|---------|-------------|
| Soil Moisture (%) | V0 |
| Temperature | V1 |
| Humidity | V2 |
| Soil Status | V3 |
| Recommendation | V4 |

---

## 📊 Dashboard Features

- Live gauges for soil moisture, temperature, and humidity
- Text indicators for soil status and irrigation recommendation
- **SuperChart with 3 plots** for historical trend analysis
- Time range selection (live, 1h, 1d, etc.)

---

## 🎓 Learning Outcomes

- Analog sensor calibration & percentage mapping
- Multi-sensor data fusion
- Decision-based embedded system design
- OLED UI development
- Cloud-based IoT integration using Blynk
- Time-series data visualization
- Sustainable and scalable system architecture

---

## 🔮 Future Enhancements

- Pump/relay integration
- Drying-rate and evaporation index calculation
- Soil health score (0-100)
- Blynk event alerts
- Multi-node heatmap visualization
- EEPROM-based calibration storage

---

## 🚀 Challenge Status

**Day 22 / 30 - Completed**  
Smart Agriculture & IoT Analytics 🌱📈

---

## 👤 Author

**Ratnakar Sahoo**  
B.Tech Undergraduate
30 Days - 30 Embedded Projects Challenge

