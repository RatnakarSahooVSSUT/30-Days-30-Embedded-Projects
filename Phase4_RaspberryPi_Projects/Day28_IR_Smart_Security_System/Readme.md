# 🚨 Day 28 - IR Based Smart Security Monitoring System 📸📧

**Raspberry Pi 4 | Pi Camera Module v2 | IR Sensor | Flask | OpenCV | Gmail SMTP**

Day 28 of my **30 Days - 30 Embedded Projects Challenge** focuses on building a real-time IR-triggered smart security system with automated snapshot capture and instant email alert notification.

---

## 🔍 Project Overview

When an object is detected continuously for 2 seconds:

- 📸 A snapshot is captured automatically  
- 📧 An email alert is sent with the image attached  
- 🎥 Live stream displays detection status  
- 🕒 Timestamp overlay is added to the video feed  
- 🔄 System resets automatically after object removal  

The system runs entirely on Raspberry Pi using Flask-based live streaming and Embedded Linux GPIO control.

---

## ⚙️ System Workflow

1. IR sensor detects obstacle (Active LOW logic)  
2. 2-second stability check prevents false triggers  
3. Snapshot saved in `/snapshots` folder  
4. Email alert sent via Gmail SMTP  
5. Live video stream shows detection status  
6. System resets for next detection cycle  

---

## 🔧 Hardware Used

- Raspberry Pi 4  
- Raspberry Pi Camera Module v2  
- IR Obstacle Sensor (Active LOW)  
- Jumper wires  
- 5V 3A Power Supply  

---

## 📍 GPIO Configuration (BCM Mode)

- IR Sensor → GPIO 17  

---

## 💻 Technologies Used

- Python  
- Flask  
- OpenCV  
- Picamera2  
- SMTP (Gmail App Password Authentication)  
- Embedded Linux GPIO  

---

## 📂 Project Structure

Day-28-IR-Smart-Security-System/  
│  
├── app.py  
├── requirements.txt  
├── README.md  
├── snapshots/  
└── images/  

---

## 🚀 How to Run

1️⃣ Install Dependencies  
pip install -r requirements.txt  

2️⃣ Enable Camera Interface  
sudo raspi-config  
→ Interface Options → Camera → Enable  

3️⃣ Run Application  
python app.py  

Open in browser:  
http://<raspberry_pi_ip>:5000  

---

## 📧 Email Setup

1. Enable 2-Step Verification in Gmail  
2. Generate a Gmail App Password  
3. Use the App Password inside `app.py` (not your real Gmail password)  

Email alert includes:  
- Detection timestamp  
- Snapshot image attachment  

---

## 🎯 Key Learning Outcomes

- IR-based intrusion detection  
- Stability filtering using time validation  
- Real-time MJPEG streaming with Flask  
- Snapshot capture using OpenCV  
- Email automation with SMTP  
- Multithreading in Embedded Linux  

---

## 🚀 Challenge Progress

**Day 28 / 30 - Completed 🔥**  
Phase 4 - Embedded Linux & Edge Systems  

---

👨‍💻 Ratnakar Sahoo  
B.Tech Undergraduate  
30 Days - 30 Embedded Projects Challenge  
