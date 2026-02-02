
# Day 10: ESP32 Joystick Controlled Pan-Tilt Gimbal System

For Day 10 of my **30 Days – 30 Projects** challenge, I built a **2-axis pan-tilt control system** using an ESP32, joystick module, servo motors, and an OLED display.  
This project focuses on **real-time motion control**, **analog input processing**, and **human-machine interaction**.

---

## What This System Can Do

This project simulates a **camera or sensor positioning system** with live feedback:

- Joystick controls **Pan (X-axis)** and **Tilt (Y-axis)** movement  
- Two servo motors rotate based on joystick direction  
- OLED display shows real-time angle values  
- Smooth and responsive control using ESP32 analog inputs  

---

## How It Works

The ESP32 continuously reads analog values from the joystick’s X and Y axes.  
These values are mapped to servo angles between **0° and 180°**.

When the joystick moves:
- Horizontal movement controls the **Pan servo**
- Vertical movement controls the **Tilt servo**

The OLED display updates in real time to show the current angles, giving the user visual feedback.

When the joystick button is pressed:
- Both servos return to the center position  
- OLED briefly shows a **CENTER** message  
- The system waits until the button is released before resuming control  

---

## Components Used

- ESP32 Dev Board  
- 2 × SG90 Servo Motors (Pan & Tilt)  
- Analog Joystick Module  
- SSD1306 128×64 OLED Display (I2C)  
- Breadboard  
- Jumper Wires  

---

## Pin Connections

| Component | ESP32 Pin |
|----------|-----------|
| Joystick X-axis | GPIO 34 |
| Joystick Y-axis | GPIO 35 |
| Joystick Button | GPIO 25 |
| Pan Servo | GPIO 18 |
| Tilt Servo | GPIO 19 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

---

## What I Learned From This Project

- Reading **analog joystick input** using ESP32 ADC  
- Mapping sensor values to **precise servo angles**  
- Using **PWM (LEDC)** on ESP32 to control servos  
- Displaying real-time system data on an **I2C OLED**  
- Designing responsive systems using **non-blocking logic**  

---

## Real-World Applications

This type of pan-tilt control system is used in:

-  **CCTV camera positioning systems**
-  **Robotic arm joint control**
-  **Antenna alignment systems**
-  **Sensor direction control in IoT monitoring**
-  **Camera gimbals for video stabilization**

---

## Platform Used

This project was designed and simulated using the **Wokwi ESP32 Simulator**.

---

### Day 10 Complete  
Another step deeper into **motion control systems, embedded interfaces, and robotics foundations** 🚀
