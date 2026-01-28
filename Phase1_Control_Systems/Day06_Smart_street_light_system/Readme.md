# Day 06: Smart Street Light Control System

In this project, I built a smart street lighting system using Arduino. The system automatically adjusts street light brightness based on surrounding conditions like day/night, vehicle movement, and safety situations such as fog or emergencies.

This simulates how modern highways and smart cities manage lighting efficiently instead of keeping lights fully bright all night.

---

## What This Project Can Do

- Automatically turns lights OFF during daytime  
- Keeps lights DIM at night to save energy  
- Turns lights FULL BRIGHT when a vehicle enters  
- Turns lights OFF after the vehicle leaves  
- Allows manual override for fog conditions  
- Allows emergency override to turn lights ON immediately  
- Controls multiple street lights together  

---

## Components Used

- Arduino UNO  
- LDR (Photoresistor) for day/night detection  
- 10kΩ resistor (with LDR)  
- PIR Sensor for vehicle entry detection  
- PIR Sensor for vehicle exit detection  
- Push Button for fog override  
- Push Button for emergency override  
- 4 LEDs to represent street lights  
- 220Ω resistors for LEDs  
- Jumper wires and breadboard  

---

## How It Works

During daytime, detected by the LDR sensor, the street lights remain OFF.

At night, the lights stay DIM to conserve energy.

When a vehicle is detected by the entry PIR sensor, the lights turn FULL BRIGHT to improve visibility and safety.

When the vehicle leaves (detected by the exit PIR sensor), the lights return to their DIM state.

If fog conditions occur, pressing the fog button forces the lights ON for better visibility.

If there is an emergency situation, pressing the emergency button immediately turns the lights ON.

---

## What I Learned

- Using LDR sensors for environmental detection  
- Working with multiple PIR sensors for motion detection  
- Implementing automatic and manual control logic together  
- Using PWM to control LED brightness  
- Understanding how smart infrastructure systems save energy and improve safety  

---

## Platform Used

This project was designed and tested using **Tinkercad Circuits**.

