# Day 01 : Intelligent Traffic Light with Pedestrian Request

In this project, I built an intelligent traffic light system using Arduino.
The system allows pedestrians to request a safe crossing by pressing a
push button, similar to real traffic signals used at road crossings.

Normally, vehicles are allowed to move while pedestrians must wait.
When the pedestrian button is pressed, the system safely stops vehicles
by switching the signal to RED and allows pedestrians to cross.

## What This Project Can Do
- Stops vehicles immediately when a pedestrian requests to cross
- Uses separate RED and GREEN lights for pedestrians
- Ensures safe traffic control logic
- Reads button input reliably using Arduino’s internal pull-up resistor
- Uses time-based logic to control signal changes

## Components Used
- Arduino UNO
- Breadboard
- LEDs for vehicle signals (Red, Yellow, Green)
- LEDs for pedestrian signals (Red, Green)
- Push Button
- 220Ω resistors
- Jumper wires

## How It Works
- Vehicles normally see a GREEN signal and can move
- Pedestrians see a RED signal and must wait
- When the button is pressed:
  - Vehicle signal turns RED
  - Pedestrian signal turns GREEN
- After a short crossing time, the system returns to normal operation

## Platform Used
This project was designed and tested using **Tinkercad Circuits**.
