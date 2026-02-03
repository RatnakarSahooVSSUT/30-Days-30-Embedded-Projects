# Day 12: Simon Says Memory Game (ESP32)

This project is part of my **30 Days Embedded Systems Challenge**.

Day 12 features a **Simon Says Memory Game** built using an **ESP32**, LEDs, push buttons, buzzer, and a 16x2 I2C LCD display.  
The system generates a random LED pattern that the player must repeat correctly. The sequence grows each round, testing memory and reaction skills.

---

## Features

- Random LED pattern generation  
- Memory-based gameplay  
- Push-button user input  
- Buzzer sound feedback  
- 16x2 LCD displays:
  - Current Score
  - Highest Score  
- High score updates automatically when beaten  

---

## Components Used

| Component | Quantity |
|-----------|----------|
| ESP32 Dev Board | 1 |
| LEDs (Red, Green, Blue, Yellow) | 4 |
| Push Buttons | 4 |
| 220Ω Resistors | 4 |
| Buzzer | 1 |
| 16x2 LCD with I2C Module | 1 |

---

## Pin Connections

### LEDs

| LED | ESP32 Pin |
|-----|-----------|
| Red | GPIO 23 |
| Green | GPIO 22 |
| Blue | GPIO 21 |
| Yellow | GPIO 19 |

### Push Buttons

| Button | ESP32 Pin |
|--------|-----------|
| Red | GPIO 32 |
| Green | GPIO 33 |
| Blue | GPIO 25 |
| Yellow | GPIO 26 |

### Buzzer

| Buzzer | ESP32 Pin |
|--------|-----------|
| + | GPIO 18 |
| – | GND |

### LCD (I2C)

| LCD Pin | ESP32 Pin |
|---------|-----------|
| SDA | GPIO 4 |
| SCL | GPIO 5 |
| VCC | 5V |
| GND | GND |

---

## How It Works

1. The system generates a random LED sequence.
2. LEDs blink in order to display the pattern.
3. The player must repeat the same sequence using buttons.
4. If correct:
   - Score increases
   - A new LED is added to the pattern
5. If wrong:
   - Buzzer sounds
   - "Game Over" is displayed
   - Score resets

---

## Learning Outcomes

This project demonstrates:

- Array handling in embedded systems  
- Random sequence generation  
- State-based game logic  
- Human-machine interaction  
- I2C LCD interfacing  
- Real-time score tracking  

---

## Simulation

This project was built and tested using the **Wokwi ESP32 Simulator**.

---

## 30 Days Embedded Challenge

This project is part of my **30-day journey** to build practical embedded systems daily and strengthen real-world hardware + firmware skills.

