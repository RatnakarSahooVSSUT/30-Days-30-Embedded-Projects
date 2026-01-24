# Day 02 - Smart 4-Floor Elevator System 🛗🚪

For Day 02 of my *30 Days – 30 Projects* challenge, I built a smart elevator control system that simulates how a real elevator behaves inside a building.
The goal of this project was to move beyond simple LED logic and start thinking like an embedded systems engineer - handling movement, user inputs, safety conditions, and real-time responses.

## 🚀 What This Elevator Can Do

This system simulates a 4-floor elevator with realistic behavior:

- Users can select any floor using push buttons
- The elevator moves floor-by-floor instead of jumping directly
- A 7-segment display shows the current floor number
- A servo motor acts as the elevator door
- A buzzer sounds when the door opens and closes
- An emergency stop button safely stops the elevator at the nearest floor and opens the door

## 🧠 How It Works

When a floor button is pressed, the system checks if the door is closed and then begins moving toward the requested floor. As the elevator “travels,” LEDs indicate the current floor and the display updates accordingly.

When it reaches the floor:
- The door opens (servo rotates)
- A buzzer alerts that the door is open
- After a short delay, the door closes with another alert sound

If the emergency button is pressed while the elevator is moving, the system stops at the nearest floor, opens the door, and waits until the emergency condition is cleared. This simulates real-world elevator safety behavior.

## 🧩 Components Used

- Arduino UNO  
- 4 LEDs for floor position indication  
- 4 Push buttons for floor selection  
- 1 Emergency stop button  
- CD4511 BCD to 7-segment driver IC  
- 7-segment display (common cathode)  
- Servo motor (door mechanism)  
- 2 Piezo buzzers (door open & close alerts)  
- Resistors and jumper wires  

## 📚 What I Learned From This Project

- Designing embedded systems using state-based logic  
- Handling multiple inputs and outputs together  
- Using external driver ICs (CD4511) to reduce pin usage  
- Making systems responsive by avoiding long blocking delays  
- Implementing safety overrides like real industrial systems  

## 🛠 Platform Used

This project was designed and simulated using **Tinkercad Circuits** .

---

Day 02 complete - and one step deeper into embedded systems and automation 🚀

