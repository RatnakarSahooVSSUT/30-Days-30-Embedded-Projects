# Day 17: IoT-Based Smart Traffic Light System (ESP32 + Blynk)

This project is part of my **30 Days – 30 Embedded Projects Challenge**.  
From **Day 16 onward**, I transitioned from **simulation-based projects to real hardware-based implementations with IoT integration**.

Day 17 focuses on designing a **smart traffic light control system** using **ESP32**, incorporating **pedestrian safety**, **emergency vehicle priority**, **OLED display**, and **cloud control using the Blynk platform**.

---

## Project Overview

The system simulates a real-world traffic intersection with:
- Normal traffic light sequencing
- Pedestrian crossing request handling
- Emergency vehicle override (highest priority)
- Local hardware control + remote IoT control
- Live system status visualization

Both **physical buttons** and **Blynk app controls** can operate the system.

---

## Key Features

-  **Traffic Light Control**
  - Green → Yellow → Red sequencing
  - OLED displays traffic status (`GO`, `SLOW`, `STOP`)

-  **Pedestrian Crossing System**
  - Dedicated pedestrian RED/GREEN LEDs
  - Pedestrian request button (hardware + Blynk)
  - Pedestrian access blocked during emergency

-  **Emergency Override (Top Priority)**
  - Immediate traffic GREEN for emergency vehicles
  - Pedestrian signals disabled during emergency
  - Emergency state latched until turned OFF

-  **IoT Integration using Blynk**
  - Remote pedestrian request button
  - Remote emergency ON/OFF control
  - Live traffic status text
  - Pedestrian & emergency status LEDs on dashboard

-  **OLED Display**
  - Real-time system state visualization
  - Traffic, pedestrian, and emergency status

---

##  System Logic

The system is designed using **priority-based control logic**:

1. **Emergency Mode** (Highest Priority)
2. **Pedestrian Request**
3. **Normal Traffic Operation**

Emergency mode overrides all other states.  
Pedestrian requests are only served when emergency mode is inactive.

---

## Hardware Components Used

- ESP32 Development Board
- Red, Yellow, Green LEDs (Traffic lights)
- Red & Green LEDs (Pedestrian signal)
- 2 Push Buttons (Pedestrian & Emergency)
- 330Ω resistors (for LEDs)
- SSD1306 OLED Display (I2C)
- Breadboard & Jumper Wires

---

## Blynk Dashboard Configuration

| Function | Widget | Virtual Pin |
|-------|--------|-------------|
| Pedestrian Request | Button | V0 |
| Emergency Override | Button (Switch) | V1 |
| Traffic Status | Labeled Value | V2 |
| Pedestrian Status | LED Widget | V3 |
| Emergency Status | LED Widget | V4 |

---

## Pin Configuration

### LEDs
- Traffic Red → GPIO 14  
- Traffic Yellow → GPIO 27  
- Traffic Green → GPIO 26  
- Pedestrian Red → GPIO 25  
- Pedestrian Green → GPIO 33  

### Buttons
- Pedestrian Button → GPIO 32  
- Emergency Button → GPIO 13  

### OLED (I2C)
- SDA → GPIO 21  
- SCL → GPIO 22  

---

## How to Run

1. Connect hardware as per pin configuration
2. Update Wi-Fi credentials and Blynk credentials in the code
3. Upload `traffic_light_blynk_esp32.ino` to ESP32
4. Open Blynk app and connect the device
5. Test using both hardware buttons and mobile dashboard

---

## Learning Outcomes

- Priority-based embedded system design
- Hardware + IoT hybrid control
- Blynk platform integration
- OLED interfacing with ESP32
- Real-world traffic control logic
- Safety-oriented system behavior

---

## Future Improvements

- Countdown timers on OLED and Blynk
- Event logging for emergency triggers
- Full finite state machine (FSM) refactor
- Multi-intersection traffic expansion

---

## Challenge Progress

**Day 17 / 30 Completed**  
Hardware-based + IoT-integrated embedded system 🚀

---

## Author

**Ratnakar Sahoo**  
B.Tech Undergraduate | Embedded Systems & IoT  
30 Days – 30 Embedded Projects Challenge

