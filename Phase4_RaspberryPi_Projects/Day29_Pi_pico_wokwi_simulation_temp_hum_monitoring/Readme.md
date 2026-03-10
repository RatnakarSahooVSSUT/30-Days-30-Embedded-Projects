🌡️ Day 29 - Smart Environment Monitoring System 📊🔔
Raspberry Pi Pico | DHT22 | SSD1306 OLED | Buzzer | MicroPython | Wokwi

Day 29 of my 30 Days - 30 Embedded Projects Challenge focuses on building a real-time environment monitoring system with live temperature and humidity display along with automatic alert generation when environmental conditions exceed safe limits.

🔍 Project Overview
The system continuously monitors environmental conditions using a DHT22 sensor connected to a Raspberry Pi Pico.

When temperature exceeds 35°C:

📊 Real-time temperature and humidity are displayed on an OLED dashboard  
🔴 LED indicator turns ON  
🔔 Buzzer alert is triggered  
⚠️ OLED display shows HOT ALERT status  
🔄 System continuously updates sensor readings every few seconds  

The entire system is implemented using MicroPython and simulated using the Wokwi embedded hardware simulator.

⚙️ System Workflow
DHT22 sensor reads temperature and humidity values  
Raspberry Pi Pico processes the sensor data  
Sensor values are displayed on an SSD1306 OLED display  
Temperature thresholds determine system status  
LED and buzzer activate when temperature exceeds safe limits  
System continuously updates readings every 2 seconds  

🔧 Hardware Used
Raspberry Pi Pico (RP2040)  
DHT22 Temperature & Humidity Sensor  
SSD1306 OLED Display (I2C)  
Buzzer (PWM controlled)  
LED Indicator  
220Ω Resistor  
Jumper wires  

📍 GPIO Configuration (RP2040)
DHT22 DATA → GPIO 15  
OLED SDA → GPIO 4  
OLED SCL → GPIO 5  
LED → GPIO 16  
Buzzer → GPIO 17  

💻 Technologies Used
MicroPython  
Embedded GPIO Control  
I2C Communication  
PWM Signal Generation  
Sensor Data Processing  
Wokwi IoT Simulator  

🚀 How to Run
1️⃣ Open the project in Wokwi simulator

2️⃣ Run the simulation

3️⃣ Adjust the DHT22 temperature slider to observe system behavior

🎯 Key Learning Outcomes
Environmental sensor interfacing with RP2040  
I2C communication with OLED displays  
PWM-based buzzer alert generation  
Real-time embedded monitoring systems  
Simulation-based hardware prototyping  

🚀 Challenge Progress
Day 29 / 30 - Completed 🔥
Phase 4 - Embedded Systems & Microcontroller Applications

👨‍💻 Ratnakar Sahoo
B.Tech Undergraduate
30 Days - 30 Embedded Projects Challenge
