# Day 20: Smart Street Light Control System using ESP32 💡

This project is part of my **30 Days - 30 Embedded Projects Challenge**.

Day 20 focuses on **automation logic, priority-based control, and IoT monitoring**, simulating a **smart street lighting system** used in modern smart city infrastructure.

---

## 🔍 Project Overview

This project implements a **Smart Street Light Control System** using an **ESP32** and **IR sensors**.  
Street lights turn ON automatically when a vehicle enters the road segment and turn OFF after the vehicle exits, with a **delay-based OFF logic** to ensure smooth illumination and avoid flickering.

The system also supports **manual override through an IoT dashboard** and provides **basic usage analytics**.

---

## ✨ Features

- Automatic street light control using IR sensors  
- Dual IR sensor logic (entry & exit detection)  
- **Delay-based OFF logic after vehicle exit**  
- Auto / Manual mode with priority override  
- Manual ON/OFF control via IoT dashboard  
- LED-based street light simulation (5 poles)  
- Usage analytics:
  - Last ON duration
  - Total ON time (session-based)  
- Cloud monitoring using Blynk IoT  

---

## 🧠 System Logic

### 🔹 AUTO Mode
- Entry IR sensor detects vehicle → Street lights turn ON immediately  
- Exit IR sensor detects vehicle → OFF timer starts  
- Lights turn OFF **after a predefined delay**, only if no new vehicle is detected  

This delay-based logic prevents flickering and ensures continuous illumination for slow-moving or closely spaced vehicles.

---

### 🔹 MANUAL Mode (Priority Override)
- Street lights are controlled only via the IoT dashboard  
- IR sensors are ignored  

Manual mode has higher priority to support maintenance and emergency scenarios.

---

## 🔌 Hardware Components Used

- ESP32 Development Board  
- 2 × IR Obstacle Sensors  
- 5 × LEDs (Street lights)  
- 5 × 330Ω resistors  
- Breadboard and jumper wires  

---

## 📍 Pin Configuration

### IR Sensors
| Sensor | ESP32 GPIO |
|------|-----------|
| Entry IR | GPIO 34 |
| Exit IR | GPIO 35 |

### Street Light LEDs
| LED | ESP32 GPIO |
|---|-----------|
| Light 1 | GPIO 13 |
| Light 2 | GPIO 12 |
| Light 3 | GPIO 14 |
| Light 4 | GPIO 27 |
| Light 5 | GPIO 26 |

---

## ☁️ Blynk Virtual Pin Mapping

| Feature | Virtual Pin |
|------|------------|
| Auto / Manual Mode | V0 |
| Manual Light Control | V1 |
| Street Light Status | V2 |
| Last ON Duration | V3 |
| Total ON Time | V4 |
| Trigger Source | V5 |

---

## 📊 Dashboard Overview

The Blynk dashboard enables:
- Switching between Auto and Manual modes  
- Manual control of street lights  
- Monitoring real-time street light status  
- Viewing usage analytics and trigger source  

---

## 🎓 Learning Outcomes

- IR sensor interfacing with ESP32  
- Event-driven automation logic  
- Delay-based OFF control for real-world reliability  
- Priority override implementation  
- IoT-based monitoring and control  
- Understanding smart street lighting systems  

---

## 🔮 Future Improvements

- Energy consumption and energy-saving analytics  
- LDR-based day/night operation  
- PWM-based brightness control  
- Relay-based control for real AC street lights  
- Multi-node smart street lighting network  

---

## 🚀 Challenge Status

**Day 20 / 30 - Completed**  
Smart Automation + IoT Control with Enhanced Logic

---

## 👤 Author

**Ratnakar Sahoo**  
B.Tech Undergraduate - Embedded Systems & IoT  
30 Days - 30 Embedded Projects Challenge
