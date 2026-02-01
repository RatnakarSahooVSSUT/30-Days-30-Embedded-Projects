# Day 09: Industrial Gas Safety & Ventilation System

This project is an industrial-style safety monitoring system built using **ESP32**. It detects harmful gas levels and high temperatures, then automatically activates ventilation and alarms to prevent dangerous situations.

---

## What This System Does

- Detects toxic gas concentration using a gas sensor  
- Monitors room temperature using a DHT22 sensor  
- Turns ON ventilation when gas levels rise  
- Activates an alarm when gas becomes dangerous  
- Enters **emergency mode** when high gas and high temperature occur together  
- Displays live safety data on an OLED screen  
- Prints real-time readings to the Serial Monitor  

This simulates how **factories, labs, and industrial environments** use embedded systems for safety monitoring.

---

## How It Works

### Gas Monitoring
The gas sensor measures air quality.

| Gas Level | System Reaction |
|-----------|-----------------|
Low | Safe condition |
Medium | Ventilation ON |
High | Ventilation + Alarm |

### Temperature Monitoring
High temperature increases risk.

| Condition | System Reaction |
|----------|----------------|
Normal | No change |
High Temp + High Gas | Emergency Mode |

---

## Safety Logic

| Condition | Fan | Alarm | Status |
|-----------|-----|-------|--------|
Safe air | OFF | OFF | SAFE |
Gas rising | ON | OFF | GAS HIGH |
Gas dangerous | ON | ON | GAS DANGER |
Gas dangerous + Temp high | ON | ON | EMERGENCY |

---

## Components Used

| Component | Purpose |
|----------|---------|
| ESP32 | Main controller |
| Gas Sensor (MQ style) | Detects harmful gases |
| DHT22 | Temperature monitoring |
| OLED SSD1306 | Displays system status |
| LED | Ventilation indicator |
| Buzzer | Danger alarm |

---

## OLED Display Shows

- Gas Level  
- Temperature  
- Fan Status  
- Safety Status  

---

## Learning Outcomes

- Industrial safety monitoring logic  
- Multi-sensor data correlation  
- Alarm and ventilation control  
- Embedded system state handling  
- OLED interfacing with ESP32  

---

## Simulation

Tested using Wokwi ESP32 Simulator.

🔗 Simulation link available in `wokwi-simulation-link.txt`

---

Part of **30 Days – 30 Embedded Systems Projects Challenge**

