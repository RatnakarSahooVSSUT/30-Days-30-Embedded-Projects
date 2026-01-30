# Day 08: Smart Indoor Climate Monitor

This project is a smart indoor climate and comfort monitoring system built using an **ESP32**. The goal was to understand how embedded systems can automatically monitor room conditions and make intelligent decisions based on environmental data and occupancy.

The system tracks **temperature, humidity, light level, and human presence**, and controls ventilation in an energy-efficient way.

---

## What This System Does

- Measures **temperature and humidity** using a DHT22 sensor  
- Detects **ambient light level** using an LDR sensor  
- Detects **room occupancy** using a PIR motion sensor  
- Displays real-time environmental data on an **OLED display**  
- Turns a **fan ON only when necessary**, based on room conditions and occupancy  
- Prints all sensor readings to the **Serial Monitor** for monitoring and debugging  

This simulates how **smart buildings and energy-efficient indoor systems** manage climate automatically.

---

## How It Works (In Simple Words)

The system continuously reads all sensors and makes decisions.

### Temperature & Humidity (DHT22)
The DHT22 measures the room’s temperature and humidity.

- If temperature is high → Room becomes uncomfortable  
- If humidity is high → Air feels heavy  

###  Light Level (LDR)
The LDR measures how bright or dark the room is.  
(In this project, it is monitored and displayed for analysis.)

### Motion Detection (PIR Sensor)
The PIR sensor detects if someone is in the room.

- Motion detected → Room is occupied  
- No motion → Room is empty  

### 🌬 Fan Control Logic
The fan turns ON **only if**:
- Motion is detected (someone is present)  
**AND**
- Temperature > 30°C **OR**
- Humidity > 75%

If the room is empty, the fan stays OFF even if it is hot — saving energy.

---

## OLED Display Shows

The OLED screen provides a live monitoring dashboard:

- Temperature (°C)  
- Humidity (%)  
- Light level (analog value)  
- Motion status (YES/NO)

---

## Components Used

| Component | Purpose |
|----------|---------|
| **ESP32** | Main controller |
| **DHT22 Sensor** | Measures temperature and humidity |
| **LDR Module** | Detects ambient light level |
| **PIR Motion Sensor** | Detects human presence |
| **OLED SSD1306 Display** | Displays live sensor readings |
| **LED** | Indicates fan ON/OFF status |
| Jumper Wires | Circuit connections |

---

## Circuit Overview

### DHT22 (Temperature & Humidity)
- Connected to ESP32 GPIO4  
- Provides digital environmental readings  

### LDR (Light Sensor)
- Connected to ESP32 GPIO34  
- Provides analog light intensity value  

### PIR Sensor (Motion Detection)
- Connected to ESP32 GPIO27  
- Detects movement in the room  

### OLED Display (I2C)
- SDA → GPIO21  
- SCL → GPIO22  
- Displays real-time sensor data  

### Fan Indicator LED
- Connected to GPIO26  
- Turns ON when fan condition is active  

---

## Code Logic (Program Flow)

1. ESP32 reads:
   - Temperature & humidity from DHT22  
   - Light level from LDR  
   - Motion status from PIR  

2. The system checks:
   - Is someone in the room?
   - Is the room too hot or humid?

3. If both conditions are met → Fan LED turns ON

4. All values are:
   - Printed to the Serial Monitor  
   - Displayed on the OLED screen  

5. The system runs continuously in a loop for real-time monitoring.

---

## What I Learned from This Project

- Interfacing multiple sensors with ESP32  
- Handling both analog and digital inputs  
- Designing condition-based automation logic  
- Displaying real-time data on an OLED  
- Building an energy-efficient embedded monitoring system  
- Implementing intelligent decision-making in embedded systems  

---

## Platform Used

Designed and simulated using **Wokwi ESP32 Simulator**

---

This project demonstrates how embedded systems can be used in **smart homes, energy-efficient buildings, and automated indoor climate monitoring systems**.

