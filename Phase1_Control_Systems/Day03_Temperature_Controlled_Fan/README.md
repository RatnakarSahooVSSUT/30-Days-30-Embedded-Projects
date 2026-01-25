
# Day 03 - Temperature Controlled Smart Fan 🌡️

For Day 03 of my *30 Days - 30 Projects* challenge, I built a smart temperature-controlled fan system using Arduino. This project helped me understand how embedded systems can monitor environmental conditions and automatically control devices in real time.

The system reads temperature using a sensor and adjusts the fan speed automatically based on how hot it gets. I also added a manual mode, where the fan speed can be controlled using a potentiometer. A push button is used to switch between AUTO and MANUAL modes.

To make the system more interactive and informative, I used an LCD display to show the current temperature, operating mode, and fan speed percentage. An RGB LED provides visual feedback about the temperature level, and a buzzer gives an alert if the temperature becomes too high.

---

## Features

- Automatic fan speed control based on temperature  
- Manual fan speed control using a potentiometer  
- Push button to switch between AUTO and MANUAL modes  
- LCD display showing temperature, mode, and fan speed  
- RGB LED temperature indicator (cool, normal, hot)  
- Buzzer alert when temperature crosses a critical limit  

---

## 🧠 How It Works

The temperature sensor continuously sends analog values to the Arduino. In AUTO mode, the program maps different temperature ranges to different PWM values to control the fan speed.

In MANUAL mode, the potentiometer reading is used to set the fan speed directly. The system uses debouncing logic to reliably detect button presses when switching modes.

The RGB LED changes color based on temperature:
- Blue → Cool  
- Green → Normal  
- Red → Hot  

If the temperature goes beyond a safe threshold, the buzzer turns on as a warning.

---

## Components Used

- Arduino UNO  
- Temperature Sensor (TMP36)  
- DC Motor (simulated using PWM output)  
- Potentiometer  
- Push Button  
- 16x2 LCD Display  
- RGB LED  
- Buzzer  
- Resistors and jumper wires  

---

## What I Learned

- Reading and converting analog sensor data  
- Using PWM to control motor speed  
- Implementing AUTO vs MANUAL system modes  
- Button debouncing for reliable input  
- Displaying real-time data on an LCD  
- Using LEDs and buzzers for system feedback  

---

## Platform

Designed and simulated using **Tinkercad Circuits**.

---

Day 03 complete - getting more comfortable with real-time sensor-based control systems 🚀
