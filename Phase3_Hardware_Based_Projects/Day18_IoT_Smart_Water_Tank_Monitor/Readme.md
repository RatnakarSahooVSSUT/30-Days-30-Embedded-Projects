# Day 18: IoT Smart Water Tank Monitoring System

This project is part of my **30 Days - 30 Embedded Projects Challenge**.

From Day 18 onward, the focus shifts to **sensor-based, real hardware projects with IoT integration**.

In this project, an **ultrasonic sensor is used to measure water level in a tank**, with real-time local and cloud-based visualization.

---

## Project Overview

The system measures the water level inside a tank using an **HC-SR04 ultrasonic sensor** mounted at the top.  
The measured data is processed by an **ESP32**, displayed locally on an **OLED**, indicated visually using **LED level bars**, and monitored remotely using the **Blynk IoT platform**.

---

## Features

- Ultrasonic-based water level measurement
- Calibrated distance-to-level conversion
- OLED display showing:
  - Distance (cm)
  - Water level (%)
  - Tank status (EMPTY → FULL)
- 5-LED level indicator bar
- IoT dashboard using Blynk
- Stable readings using averaging and filtering
- Safe voltage-level handling for ESP32

---

## System Logic

- Tank height is predefined and calibrated
- Distance is measured from the top of the tank
- Water level is calculated as:
  Water Level = Tank Height - Measured Distance
- Percentage and status are derived from the calculated level
- Threshold-based logic controls LEDs and status text

---

## Hardware Components Used

- ESP32 Development Board
- HC-SR04 Ultrasonic Sensor
- SSD1306 OLED Display (I2C)
- 5 LEDs with 330Ω resistors
- Voltage divider for ultrasonic Echo pin
- Breadboard and jumper wires

---

## Pin Configuration

### Ultrasonic Sensor
- TRIG → GPIO 5  
- ECHO → GPIO 18 (via voltage divider)

### OLED Display (I2C)
- SDA → GPIO 21  
- SCL → GPIO 22  

### LEDs
- 10% → GPIO 13  
- 30% → GPIO 12  
- 50% → GPIO 14  
- 70% → GPIO 27  
- 80% (FULL) → GPIO 26  

---

## IoT Dashboard (Blynk)

The following parameters are monitored on the Blynk dashboard:

| Parameter | Virtual Pin |
|---------|------------|
| Water Level (%) | V0 |
| Distance (cm) | V1 |
| Tank Status | V2 |

This project currently focuses on **monitoring only**.  
Control and automation will be introduced in upcoming projects.

---

## Learning Outcomes

- Ultrasonic sensor interfacing
- Sensor calibration and error correction
- Noise reduction using averaging
- Embedded system visualization using OLED
- IoT data monitoring with Blynk
- Designing reliable sensor-based systems

---

## Future Improvements

- Automatic pump control using relay
- Overflow alerts and notifications
- Multiple tank monitoring
- Sensor fusion for improved accuracy

---

## Challenge Status

**Day 18 / 30 - Completed**  
IoT-enabled, sensor-based embedded system 🚀

---

## Author

**Ratnakar Sahoo**  
B.Tech Undergraduate | Embedded Systems & IoT  
30 Days – 30 Embedded Projects Challenge


