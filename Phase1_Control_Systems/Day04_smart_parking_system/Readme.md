# Smart Parking System with Automatic Gate

This project is a simple smart parking system built using Arduino. The idea was to understand how parking lots can automatically detect free and occupied slots and control the entry gate without human intervention.

I used ultrasonic sensors to check if a car is present in each parking slot. Based on that, LEDs show whether a slot is free or occupied, and an LCD display shows the overall parking status. A servo motor acts as the parking gate and opens only when there is at least one free slot.

---

## What This System Does

- Detects vehicles in parking slots using ultrasonic sensors  
- Shows slot status using red (occupied) and green (free) LEDs  
- Displays parking information on an LCD screen  
- Automatically opens the gate when slots are available  
- Keeps the gate closed when all slots are full  

This simulates how modern smart parking systems help manage vehicle entry.

---

## How It Works (In Simple Words)

Each parking slot has an ultrasonic sensor. The sensor measures the distance to see if something (a car) is in front of it.

- If the distance is small → Car is present → Slot is **occupied**
- If the distance is large → No car → Slot is **free**

Based on this:
- Red LED turns ON when a slot is occupied  
- Green LED turns ON when a slot is free  

The Arduino counts how many slots are free.  
If at least one slot is free → Gate opens  
If all slots are full → Gate closes  

The LCD continuously shows slot status and gate condition.

---

## Components Used

- Arduino UNO  
- 3 Ultrasonic Sensors (HC-SR04)  
- 3 Red LEDs  
- 3 Green LEDs  
- 16x2 LCD Display  
- Servo Motor (for gate)  
- Resistors and jumper wires  

---

## Circuit Overview

### Ultrasonic Sensors (Slot Detection)

Each sensor has:
- TRIG pin to send the signal  
- ECHO pin to receive the reflected signal  

If the measured distance is less than about 15 cm, the slot is treated as occupied.

---

### LEDs

Each slot has:
- Green LED → Slot is free  
- Red LED → Slot is occupied  

This gives a quick visual idea of parking availability.

---

### Servo Motor (Gate)

The servo acts like the parking gate.

- Gate opens when at least one slot is free  
- Gate closes when all slots are full  

---

### LCD Display

The LCD shows live updates such as:
S1:FREE S2:FULL
S3:FREE GATE:OPEN
So anyone can easily see parking status.

---

## Code Logic (What’s Happening in the Program)

1. Arduino measures distance from each ultrasonic sensor.  
2. It decides whether each slot is free or occupied.  
3. LEDs are updated accordingly.  
4. The number of free slots is calculated.  
5. If free slots > 0 → Servo opens the gate.  
6. If free slots = 0 → Servo closes the gate.  
7. LCD display is updated with the latest information.

The system keeps repeating this process in a loop, so everything updates in real time.

---

## What I Learned from This Project

- How ultrasonic sensors detect objects  
- Managing multiple sensors in one program  
- Controlling LEDs based on sensor input  
- Using a servo motor for automation  
- Displaying system status using an LCD  
- Building a small real-life style automation system  

---

## Platform Used

Designed and simulated using **Tinkercad Circuits**

---

This project helped me understand how embedded systems can be used in real-life applications like smart parking and automation systems.



