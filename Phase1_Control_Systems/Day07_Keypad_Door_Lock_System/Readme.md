# Day 07: Smart Keypad Door Lock System

This project demonstrates a password-based electronic door locking system using Arduino.  
It simulates how secure access systems are implemented in ATMs, offices, homes, and smart buildings using keypads, visual indicators, and safety logic.

The system allows authorized access through a keypad, provides real-time feedback via an LCD, and enhances security using alarm and lockout mechanisms.

Designed and tested using **Tinkercad Circuits**.

---

## Key Features

### Keypad-Based Password Entry
- Uses a **4×4 matrix keypad** for entering a numeric password.
- Password input is hidden on the LCD using `*` symbols for security.

### Servo Motor Door Lock
- A **servo motor** acts as the door locking mechanism.
- Unlocks when the correct password is entered.
- Automatically locks again after a short delay.

### LCD Display Interface
- A **16×2 LCD** displays system status such as:
  - Enter Password
  - Access Granted
  - Wrong Password
  - System Locked
- Provides clear feedback to the user.

### Locked State Indicator
- **Red LED** remains ON when the system is locked or waiting for a password.
- Turns OFF only when the correct password is entered.
- Blinks during alarm and lockout conditions.

### Access Granted Indicator
- **Green LED** turns ON when the correct password is entered.
- Indicates successful authentication.

### Alarm & Lockout Protection
- After **3 consecutive wrong password attempts**:
  - Red LED blinks
  - Buzzer sounds
  - System enters temporary lockout mode
- Prevents unauthorized brute-force attempts.

### Change Password Feature
- Authorized users can change the password using the keypad.
- Old password verification is required before setting a new password.
- No need to reprogram the Arduino to update the password.

### Buzzer Alerts
- Provides audio feedback for:
  - Successful access
  - Wrong password attempts
  - Alarm and lockout mode

---

## Components Used

| Component | Purpose |
|---------|---------|
| Arduino UNO | Main controller |
| 4×4 Keypad | Password input |
| Servo Motor | Door lock mechanism |
| 16×2 LCD | User interface |
| Red LED | Locked / alarm indication |
| Green LED | Access granted indication |
| Buzzer | Audio alerts |
| 220Ω Resistors | LED current limiting |
| Breadboard & Jumper Wires | Circuit connections |

---

## System Working Logic

1. **System Start**
   - Red LED turns ON indicating locked state.
   - LCD displays “Enter Password”.

2. **Password Entry**
   - User enters password using keypad.
   - Input is masked on LCD.

3. **Correct Password**
   - Green LED turns ON.
   - Red LED turns OFF.
   - Servo unlocks the door.
   - Door automatically locks again after a delay.

4. **Wrong Password**
   - Buzzer sounds briefly.
   - Red LED remains ON.
   - Wrong attempt counter increases.

5. **Three Wrong Attempts**
   - Red LED blinks.
   - Buzzer sounds alarm.
   - System enters lockout mode for a short duration.

6. **Password Change Mode**
   - User presses a specific key to enter change-password mode.
   - Old password must be verified.
   - New password is saved successfully.

---

## Learning Outcomes

- Interfacing **matrix keypads** with Arduino
- Controlling **servo motors** for mechanical locking
- Using **LCD displays** for user interaction
- Implementing **security logic and lockout mechanisms**
- Managing **state-based system behavior**
- Combining hardware and software for real-world security systems

---

## Simulation Platform

This project was designed and tested using:

**Tinkercad Circuits**

---

## Author

**Ratnakar Sahoo**  
B.Tech Electronics & Telecommunication Engineering  
VSSUT Burla  

---

*Part of my “30 Days – 30 Arduino Projects” challenge focusing on practical, real-world embedded systems.*

