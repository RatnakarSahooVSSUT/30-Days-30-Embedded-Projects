# Day 14: Smart Pressure Trend Weather Predictor

This project is part of my **30 Days - 30 Embedded Systems Projects Challenge**.

A **barometric pressure sensor** can be used to predict short-term weather changes by observing how atmospheric pressure varies over time. In this project, an **ESP32** reads pressure and temperature data from a **BMP180 barometric sensor**, combines it with **humidity data from a DHT22**, and predicts upcoming weather conditions. A **16x2 I2C LCD** displays live pressure and forecast results, while LEDs provide quick visual weather indicators.

This simulates the working principle of **home weather stations** and traditional **barometer-based forecasting systems**.

---

## Features

- Real-time atmospheric pressure and temperature monitoring using BMP180  
- humidity measurement using DHT22  
- Pressure averaging to reduce noise and improve trend accuracy  
- Weather forecasting based on **pressure + temperature trends**  
- Live pressure and forecast display on 16x2 LCD  
- LED indicators for weather condition (Clear / Cloudy / Rain)

---

## Hardware Components

| Component | Quantity |
|----------|----------|
| ESP32 Development Board | 1 |
| BMP180 Barometric Pressure Sensor | 1 |
| DHT22 Temperature & Humidity Sensor | 1 |
| 16x2 LCD with I2C Backpack | 1 |
| LEDs (Weather Indicators) | 3 |
| 220Ω Resistors | 3 |

---

## Circuit Connections

### BMP180 (I2C Communication)

| BMP180 Pin | ESP32 Pin |
|------------|-----------|
| 3.3V | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

### DHT22 Sensor

| DHT22 Pin | ESP32 Pin |
|-----------|-----------|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 4 |

---

### LCD Display (Shared I2C Bus)

| LCD Pin | ESP32 Pin |
|---------|-----------|
| VCC | 5V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

### Weather Indicator LEDs

| Condition | ESP32 GPIO |
|-----------|------------|
| Clear Weather | 14 |
| Cloudy | 27 |
| Rain Likely | 26 |

---

## Working Principle

Atmospheric pressure changes before weather changes. Instead of using a single pressure reading, this system:

1. Stores multiple pressure readings  
2. Calculates an average pressure  
3. Compares the new average with the previous average  
4. Observes temperature trend  
5. Uses both trends to predict weather

### Forecast Logic

| Pressure Trend | Temperature Trend | Humidity | Prediction |
|----------------|-------------------|----------|------------|
| Dropping quickly | Falling | High | 🌧 Rain likely |
| Dropping slowly | Any | Moderate | ☁ Cloudy |
| Stable or Rising | Rising | Normal | ☀ Clear |

This is a simplified version of **barometric trend forecasting** used in home weather stations.

---

## LED Logic

| Forecast | LED Behavior |
|----------|--------------|
| Clear | Green LED ON |
| Cloudy | Yellow LED ON |
| Rain | Red LED ON |

---

## Real-World Applications

- Home weather monitoring stations  
- IoT environmental sensing systems  
- Smart agriculture weather awareness  
- Outdoor activity planning devices  

---

## Simulation Platform

The project was designed and tested using the **Wokwi ESP32 Simulator**.

---

## Learning Outcomes

This project helped me understand:

- Barometric pressure sensing  
- Pressure trend analysis  
- Environmental data fusion (pressure + temperature + humidity)  
- Noise reduction using averaging  
- Embedded forecasting logic  
- Multi-sensor I2C integration  

---

## Challenge Context

Day 14 of my **30 Days – 30 Embedded Systems Projects Challenge**, focusing on **atmospheric sensing and environmental trend prediction**.

