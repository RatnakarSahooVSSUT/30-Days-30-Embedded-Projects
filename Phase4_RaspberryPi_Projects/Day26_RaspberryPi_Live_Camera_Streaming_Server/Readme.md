# Day 26: Edge Video Streaming System with Raspberry Pi 🎥🌐

Raspberry Pi 4 | Pi Camera v2 | Flask | OpenCV | WiFi Streaming

This project marks the beginning of Phase 4 in my 30 Days - 30 Embedded Projects Challenge, transitioning from microcontroller-based systems to Embedded Linux and edge computing.

Today’s build focuses on real-time camera streaming over WiFi using a Raspberry Pi.

---

## 🔍 Project Overview

This project implements a Live Edge Video Streaming System using:

- Raspberry Pi 4
- Raspberry Pi Camera Module v2 (IMX219)
- Flask Web Server
- OpenCV frame encoding
- MJPEG browser-based streaming

Instead of using VNC (which causes lag), the system streams compressed camera frames directly to a browser over WiFi, enabling smoother and more efficient remote viewing.

---

## ✨ Features

- Real-time camera capture using Picamera2
- Optimized 320x240 streaming for low latency
- MJPEG streaming over HTTP
- Browser-based live view (no VNC required)
- WiFi-compatible streaming
- Lightweight Flask server implementation
- OpenCV frame encoding
- Black-themed responsive web interface
- Performance-optimized for network transmission

---

## 🧠 System Logic

📷 Camera Capture  
- Picamera2 captures frames at 320x240 resolution  
- Frame rate limited to 15 FPS for smooth WiFi performance  

🖥 Frame Processing  
- Frames converted from RGB → BGR  
- JPEG encoding using OpenCV  

🌐 Web Streaming  
- Flask server streams frames using multipart HTTP response  
- Browser displays MJPEG stream  
- Accessible via:  
  `http://<raspberry_pi_ip>:5000`

---

## 🔌 Hardware Components Used

- Raspberry Pi 4 (2GB)
- Raspberry Pi Camera Module v2
- CSI Ribbon Cable
- WiFi Network

---

## 📡 Network Configuration

- Flask server bound to `0.0.0.0`
- Port: 5000
- Stream accessible within same local WiFi network

---

## 🎓 Learning Outcomes

- Understanding CSI camera interfacing
- Using Picamera2 on Raspberry Pi OS
- Managing video latency over WiFi
- Replacing VNC with browser-based streaming
- Building embedded web servers
- Frame encoding and MJPEG streaming
- Performance optimization for edge devices
- Embedded Linux networking fundamentals

---

## 🔮 Future Improvements

- Add Face Detection overlay
- Add FPS counter
- Add AI-based object detection
- Add distance estimation logic
- Integrate sensor data beside video
- Convert into full Edge AI safety system

---

## 🚀 Challenge Status

Day 26 / 30 - Completed  
Edge Video Streaming System with Raspberry Pi 🌐🎥

Phase 4 officially begins.

👤 Author  
Ratnakar Sahoo  
B.Tech Undergraduate  
30 Days - 30 Embedded Projects Challenge
