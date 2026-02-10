# Day 19: IoT Temperature & Humidity Monitoring System 🌡️💧

This project is part of my **30 Days - 30 Embedded Projects Challenge**.

On Day 19, the focus is on **environmental monitoring with IoT-based data logging and trend visualization**, similar to real-world weather stations and smart building systems.

---

## Project Overview

This system measures **temperature and humidity** using a **DHT11 sensor** interfaced with an **ESP32**.  
The data is:

- Displayed locally on an **OLED display**
- Indicated using **LED-based threshold alerts**
- Sent to the **Blynk IoT Cloud**
- Logged and visualized as **historical trends on a web dashboard**

---

## Features

- 🌡️ Temperature monitoring (°C)
- 💧 Humidity monitoring (%)
- 📟 OLED display for local visualization
- 🚦 LED indicators for threshold status
- ☁️ IoT dashboard using Blynk
- 📊 Historical trend visualization using Custom Chart
- 🔄 Stable sampling using timer-based logic

---

## System Logic

1. ESP32 reads temperature and humidity from DHT11
2. Values are displayed on OLED
3. Threshold logic determines status and LED indication
4. Sensor data is pushed to Blynk Cloud
5. Blynk logs the data and visualizes trends over time

---

## Hardware Components Used

- ESP32 Development Board
- DHT11 Temperature & Humidity Sensor
- SSD1306 OLED Display (I2C)
- 3 LEDs (Green, Yellow, Red)
- 330Ω resistors
- Breadboard and jumper wires

---

## Pin Configuration

### DHT11
| Signal | ESP32 Pin |
|------|----------|
| DATA | GPIO 4 |
| VCC | 3.3V |
| GND | GND |

### OLED (I2C)
| OLED Pin | ESP32 Pin |
|--------|----------|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### LEDs
| LED | ESP32 Pin | Status |
|---|---|---|
| Green | GPIO 13 | Normal |
| Yellow | GPIO 12 | Warning |
| Red | GPIO 14 | Critical |

---

## Blynk Virtual Pin Mapping

| Parameter | Virtual Pin |
|--------|------------|
| Temperature | V0 |
| Humidity | V1 |
| Temperature Status | V2 |
| Humidity Status | V3 |
| Last Update Time | V4 |

---

## Dashboard Overview

- Live temperature and humidity values
- Combined historical trend graph using Custom Chart
- Status labels for real-time condition monitoring

> Note: Due to free-plan limitations, temperature and humidity are plotted on a shared Y-axis.

---

## Project Snapshots

| Hardware Setup | Blynk Dashboard |
|---------------|----------------|
| ![](images/hardware_setup.jpg) | ![](images/blynk_dashboard.png) |

---

## Learning Outcomes

- Interfacing DHT11 with ESP32
- OLED-based embedded visualization
- Threshold-based alert design
- Blynk IoT Cloud integration
- Time-series data logging and analysis
- Designing real-world IoT monitoring systems

---

## Future Improvements

- Upgrade to DHT22 / SHT31 for higher accuracy
- Push notifications for critical thresholds
- SD card data backup
- Multi-sensor environmental monitoring
- Integration with other smart systems

---

## Challenge Status

**Day 19 / 30 - Completed**  
Environmental Monitoring + IoT Data Analytics

---

## Author

**Ratnakar Sahoo**  
B.Tech Undergraduate - Embedded Systems & IoT  
30 Days - 30 Embedded Projects Challenge

