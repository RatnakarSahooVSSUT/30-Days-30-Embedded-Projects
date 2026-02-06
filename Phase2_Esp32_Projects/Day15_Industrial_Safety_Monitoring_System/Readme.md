# Day 15: Industrial Indoor Environment & Safety Monitoring System

This project is an **industrial-grade indoor monitoring and automation system** built using **ESP32**.  
It continuously monitors **environmental and safety parameters** and automatically controls **ventilation, alarms, and safety indicators** to prevent hazardous indoor conditions.

This system simulates how **factories, laboratories, server rooms, and industrial indoor spaces** use embedded systems for **environment monitoring and safety automation**.

---

## What This System Does

- Detects **harmful gas concentration** using a gas sensor
- Monitors **indoor temperature** using a DHT22 sensor
- Measures **ambient light levels** for indoor condition awareness
- Automatically turns **ON ventilation** when unsafe conditions are detected
- Activates an **alarm** during dangerous situations
- Controls a **ventilation vent/window** using a servo motor
- Displays **live indoor safety data** on an OLED screen
- Indicates system state using **RGB status LED**
- Supports **manual override mode** for operator control
- Prints real-time readings to the **Serial Monitor**

This represents a **real-world industrial indoor safety and automation system**.

---

## How It Works

### Gas Monitoring
The gas sensor continuously measures indoor air quality.

| Gas Level | System Reaction |
|---------|----------------|
| Safe | Normal operation |
| Rising | Ventilation ON |
| Dangerous | Ventilation + Alarm |

---

### Temperature Monitoring
Temperature data is correlated with gas levels to assess risk severity.

| Condition | System Reaction |
|---------|----------------|
| Normal temperature | No change |
| High temperature + High gas | Emergency mode |

---

### Light Monitoring
Light level is used as an additional **indoor condition parameter** to trigger warning states.

---

## Safety & Control Logic

| Condition | Fan | Vent | Alarm | Status |
|--------|----|------|------|------|
| Normal indoor air | OFF | Closed | OFF | SAFE |
| Gas rising / Temp high | ON | Partial open | OFF | WARNING |
| Gas dangerous | ON | Fully open | ON | DANGER |
| Gas dangerous + Temp high | ON | Fully open | ON | EMERGENCY |
| Manual override | User controlled | User controlled | OFF | MANUAL |

---

## Components Used

| Component | Purpose |
|--------|--------|
| ESP32 | Main controller |
| MQ-2 Gas Sensor | Detects harmful gases |
| DHT22 | Temperature monitoring |
| LDR | Indoor light monitoring |
| Relay Module | Controls ventilation fan |
| Servo Motor | Controls vent/window position |
| Buzzer | Audible danger alarm |
| RGB LED | System status indicator |
| OLED SSD1306 | Displays live system data |
| Push Button | Manual override control |

---

## OLED Display Shows

- Temperature (°C)
- Gas level
- Light level
- Fan status
- Current system mode (SAFE / WARNING / DANGER / EMERGENCY / MANUAL)

---

## Software & Tools

- **Controller:** ESP32  
- **Programming Language:** Arduino (C/C++)
- **Libraries Used:**
  - DHT Sensor Library
  - ESP32Servo
  - Adafruit GFX
  - Adafruit SSD1306
- **Simulation Platform:** Wokwi ESP32 Simulator

---

## Learning Outcomes

- Industrial indoor safety monitoring logic
- Multi-sensor data correlation
- Actuator-based automation (fan, vent, alarm)
- State-based embedded system design
- ESP32 PWM and GPIO control
- OLED interfacing and real-time display
- Manual override implementation
- Simulation-driven embedded development

---

## Simulation

This project has been **fully tested using the Wokwi ESP32 Simulator**.



📌 **Author:** Ratnakar Sahoo  
📌 **Project:** Day 15 - Industrial Indoor Environment & Safety Monitoring System  
📌 **Challenge:** 30 Days - 30 Embedded Systems Projects  

