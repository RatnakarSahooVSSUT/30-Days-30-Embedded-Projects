# Day 25: Dual Gas Safety Monitoring System with IoT 🚨🌫️  
**ESP32 | MQ-4 | MQ-7 | OLED | Blynk IoT**

This project is part of my **30 Days - 30 Embedded Projects Challenge**, where I design and build real-world embedded systems step by step.

**Day 24** focuses on **environmental safety, gas sensing, calibration, and IoT-based monitoring**, using dual MQ-series gas sensors for accurate and reliable detection.

---

## 🔍 Project Overview

This project implements a **Dual Gas Safety Monitoring System** using an **ESP32**, capable of detecting:

- **Methane (CH₄)** using the **MQ-4 sensor**
- **Carbon Monoxide (CO)** using the **MQ-7 sensor**

The system performs **proper sensor calibration**, estimates gas concentration in **ppm**, provides **local alerts** using LEDs and a buzzer, displays live data on an **OLED**, and supports **remote monitoring via Blynk IoT**.

---

## ✨ Features

- Dual gas detection: **Methane (CH₄) & Carbon Monoxide (CO)**
- Proper **Rs → R₀ → ppm** estimation (datasheet-based)
- Multi-sample ADC averaging for stable readings
- Exponential Moving Average (EMA) filtering
- OLED display with real-time gas concentration
- **Gas-specific alarm patterns**
  - CH₄: Slow warning beep
  - CO: Fast urgent beep
  - Both gases: Continuous alarm
- Red & Green LED status indicators
- **Active-LOW buzzer support**
- IoT dashboard integration using **Blynk Cloud**
- Real-time ppm visualization and alarm status

---

## 🧠 System Logic

### 🟢 Normal Operation
- MQ-4 and MQ-7 continuously monitor gas levels
- ppm values are calculated and filtered
- OLED shows live gas concentrations
- Green LED indicates safe conditions

### 🚨 Alarm Logic
- **Methane > 2000 ppm** → CH₄ alert (slow beep)
- **CO > 50 ppm** → CO alert (fast beep)
- **Both gases high** → Critical condition (continuous alarm)
- Red LED turns ON during any alarm state

### ☁️ IoT Monitoring
- Live CH₄ and CO ppm values sent to Blynk
- Separate alarm indicators for each gas
- Human-readable system status displayed on dashboard

---

## 🔌 Hardware Components Used

- ESP32 (30-pin Dev Module)
- MQ-4 Gas Sensor (Methane)
- MQ-7 Gas Sensor (Carbon Monoxide)
- SSD1306 OLED Display (I2C)
- Active-LOW Buzzer Module
- Red LED & Green LED
- 330 Ω resistors
- Breadboard & jumper wires

---

## 📍 Pin Configuration

### Gas Sensors
| Sensor | ESP32 GPIO |
|------|------------|
| MQ-4 AO | GPIO 34 |
| MQ-7 AO | GPIO 35 |
| MQ Sensors VCC | 5V |
| MQ Sensors GND | GND |

### Other Components
| Component | ESP32 GPIO |
|--------|------------|
| Green LED | GPIO 16 |
| Red LED | GPIO 17 |
| Buzzer (Active-LOW) | GPIO 18 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

---

## ☁️ Blynk Virtual Pin Mapping

| Parameter | Virtual Pin |
|---------|-------------|
| Methane (CH₄ ppm) | V0 |
| Carbon Monoxide (CO ppm) | V1 |
| Gas Status (Text) | V2 |
| Overall Alarm State | V3 |
| Methane Alarm | V4 |
| CO Alarm | V5 |

---

## 📊 Blynk Dashboard Overview

The Blynk dashboard provides:
- Live CH₄ and CO ppm gauges
- Separate alarm indicators for Methane and CO
- Overall alarm status LED
- System status text (SAFE / ALERT / CRITICAL)

---

## 🎓 Learning Outcomes

- Understanding MQ-series gas sensors
- Proper sensor warm-up and calibration techniques
- Analog signal conditioning and ADC averaging
- Logarithmic ppm estimation from datasheet curves
- Embedded filtering using EMA
- Designing gas-specific alarm logic
- OLED-based embedded UI design
- IoT integration using Blynk Cloud
- Safety-oriented embedded system design

---

## 🔮 Future Improvements

- Blynk push notifications on alarm
- Timestamped gas log history
- Automatic exhaust fan / relay control
- Temperature & humidity compensation
- Battery-backed operation
- Cloud-based analytics and alerts

---

## 🚀 Challenge Status

**Day 24 / 30 - Completed**  
Dual Gas Safety Monitoring System with IoT Integration 🚨🌫️📲

---

## 👤 Author

**Ratnakar Sahoo**  
B.Tech Undergraduate  
**30 Days - 30 Embedded Projects Challenge**
