# Day 13: Digital Spirit Level using ESP32 & MPU6050

This project is part of my **30 Days – 30 Embedded Systems Projects Challenge**.

A **Digital Spirit Level** (also called a digital inclinometer) is an electronic tool used to measure how level or tilted a surface is. In this project, an **ESP32** reads tilt data from an **MPU6050 accelerometer** and displays the angle on an **I2C 16x2 LCD**. LED indicators provide quick visual feedback for tilt direction.

This simulates the functionality of professional leveling tools used in construction, robotics, and alignment systems.

---

## Features

- Real-time tilt sensing using MPU6050 accelerometer  
- Tilt angle calculation in degrees  
- Live angle display on 16x2 LCD  
- LED indicators for tilt direction  
- Green LED lights when surface is level  
- Uses gravity vector math with `atan2()` for angle calculation  

---

## Hardware Components

| Component | Quantity |
|-----------|----------|
| ESP32 Development Board | 1 |
| MPU6050 Accelerometer + Gyroscope Module | 1 |
| 16x2 LCD with I2C Backpack | 1 |
| LEDs (Level + Direction Indicators) | 5 |
| 220Ω Resistors | 5 |

---

## Circuit Connections

### MPU6050 (I2C Communication)

| MPU6050 Pin | ESP32 Pin |
|-------------|-----------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

### LCD Display (Shared I2C Bus)

| LCD Pin | ESP32 Pin |
|---------|-----------|
| VCC | 5V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

### LED Tilt Indicators

| Function | ESP32 GPIO |
|----------|------------|
| 🟢 Level Indicator | 14 |
| ⬅ Left Tilt | 27 |
| ➡ Right Tilt | 26 |
| ⬆ Forward Tilt | 25 |
| ⬇ Back Tilt | 33 |

---

## Working Principle

The **MPU6050 accelerometer** measures how gravity acts on the sensor along X, Y, and Z axes.

When the board is flat:
Gravity mostly affects the Z-axis

When tilted:
Gravity spreads into X and/or Y axes

The ESP32 calculates tilt angles using:
angleX = atan2(ay, az)
angleY = atan2(ax, az)

Where:
- `ax, ay, az` are acceleration values
- `atan2()` converts the gravity direction into tilt angle in degrees

---

## LED Logic

| Condition | LED Behavior |
|-----------|--------------|
| Surface is level (±3°) | Green LED ON |
| Tilt left | Left LED ON |
| Tilt right | Right LED ON |
| Tilt forward | Forward LED ON |
| Tilt backward | Back LED ON |

Multiple LEDs may light if the surface is tilted diagonally.

---

## Learning Outcomes

This project helped me understand:

- Accelerometer-based tilt sensing  
- Gravity vector interpretation  
- Angle calculation using trigonometry  
- I2C communication with multiple devices  
- Real-time sensor data visualization  
- Embedded system integration of sensors + display + indicators  

---

## Simulation Platform

The project was built and tested using the **Wokwi ESP32 Simulator** before hardware implementation.

---

Built as part of a hands-on learning journey in embedded systems and sensor-based applications.







