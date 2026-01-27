# Day-05 Smart Water Tank Level Controller (Control System)

For Day 05 of my **30 Days – 30 Projects** challenge, I built a smart water tank level controller using Arduino. The goal of this project was to understand how real systems automatically maintain water levels using sensors and control logic.

This system continuously monitors the water level using an ultrasonic sensor and controls a motor (pump) to keep the tank filled within safe limits. I also added multiple water level indicators, an LCD display for live status, and both automatic and manual control modes.

This project helped me move deeper into **feedback-based control systems**.

---

## What This System Does

- Measures water level using an ultrasonic sensor  
- Automatically turns the motor ON when the tank is low  
- Turns the motor OFF when the tank reaches a safe level  
- Shows water level and motor status on an LCD  
- Provides multi-level LED indicators (Low, Medium, Full)  
- Allows switching between **AUTO mode** and **MANUAL mode**  
- In MANUAL mode, a second button directly controls the motor  

---

## How It Works (Simple Explanation)

The ultrasonic sensor measures the distance to the water surface inside the tank.

- Large distance → Water level is LOW  
- Medium distance → Water level is MEDIUM  
- Small distance → Tank is FULL  

Based on this:

### In **AUTO mode**
- Motor turns ON when water level is LOW  
- Motor turns OFF when water reaches MEDIUM or FULL  

### In **MANUAL mode**
- The system stops automatic control  
- A separate button allows the user to turn the motor ON or OFF manually  

The LCD displays:
- Current water level  
- Motor status (ON/OFF)  
- Mode (AUTO/MANUAL)

---

## Components Used

- Arduino UNO  
- Ultrasonic Sensor (HC-SR04)  
- DC Motor (simulating water pump)  
- NPN Transistor (motor driver)  
- Diode (motor protection)  
- 3 LEDs (Low, Medium, Full level indicators)  
- 16x2 LCD Display  
- 2 Push Buttons (Mode switch + Manual motor control)  
- Resistors and jumper wires  

---

## Circuit Overview

### Ultrasonic Sensor  
Measures the distance to the water surface.

### Level Indicator LEDs  
- 🔴 Red → Low level  
- 🟡 Yellow → Medium level  
- 🟢 Green → Full level  

### Motor Control  
The motor is controlled using a transistor so Arduino can safely switch it ON and OFF.

### Buttons  
- Mode Button → Switch between AUTO and MANUAL  
- Motor Button → Controls motor directly in MANUAL mode  

### LCD Display  
Shows real-time system information like water level, motor status, and operating mode.

---

## Code Logic Summary

1. Measure water level using ultrasonic sensor  
2. Determine if level is LOW, MEDIUM, or FULL  
3. In AUTO mode:  
   - Motor ON at LOW level  
   - Motor OFF at MEDIUM or FULL level  
4. In MANUAL mode:  
   - Motor controlled by user button  
5. Update LEDs and LCD display continuously  

The system keeps running in a loop, constantly checking water level and updating outputs.

---

## What I Learned

- How ultrasonic sensors can be used for level measurement 
- Using transistors to control motors safely  
- Designing systems with **AUTO and MANUAL modes**  
- Displaying real-time system data using an LCD  
- Understanding practical control systems used in homes and industries  

---

## Platform Used

Designed and simulated using **Tinkercad Circuits**

---

This project gave me hands-on experience with a real-world style control system that is commonly used in water management and automation systems.

