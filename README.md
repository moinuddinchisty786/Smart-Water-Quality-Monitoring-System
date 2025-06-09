# 💧 Smart Water Quality Monitoring System

> Developed as part of my internship at *Samsung Innovation Campus (SIC)*, this project focuses on monitoring the quality of water in real time using IoT sensors and visualizing the data through a live interface built in Python.

---

## 📌 Project Overview

Water quality is critical for health, agriculture, and environmental sustainability. This project is designed to monitor key parameters of water such as *pH, **turbidity, and **temperature* using sensor modules connected to a microcontroller. The data is then sent to a Python-based GUI which displays the live readings for real-time monitoring and alerts.

---

## 💻 Technologies Used

- *Python*
- *PyCharm* – for building and running the live interface
- *Tkinter* – for GUI display
- *Serial Communication (pyserial)* – to receive data from hardware
- *Arduino/ESP32/NodeMCU* – as microcontroller interface
- *IoT Sensors*:
  - pH sensor
  - Turbidity sensor
  - Temperature sensor (DS18B20 / DHT11)

---

## ⚙ Features and Components

### ✅ Features
- Real-time display of water quality parameters (pH, turbidity, temperature)
- Graphical interface built using Tkinter
- Alerts on unsafe water quality levels
- Serial data reading from microcontroller
- Live plotting or dashboard (optional with Matplotlib)

### 🧩 Components
- *Sensors*:
  - pH sensor for acidity/alkalinity
  - Turbidity sensor for water clarity
  - Temperature sensor for thermal monitoring
- *Microcontroller*:
  - Arduino or ESP32 reads sensor data and transmits via USB
- *Python Interface*:
  - Tkinter-based GUI to visualize data live
  - Pyserial for reading real-time data from COM port
- *Alert System*:
  - Predefined threshold triggers warnings in GUI for poor-quality readings

---
#### Architecture
![WhatsApp Image 2025-06-09 at 19 37 23_bf7cbd64](https://github.com/user-attachments/assets/5b3d1282-2b37-4ea5-bbd2-64500598088a)


## ▶ How to Run

1. *Set up Hardware:*
   - Connect sensors to the microcontroller.
   - Flash microcontroller with appropriate Arduino code to send serial data.

2. *Clone the Repository:*
   bash
   git clone https://github.com/your-username/Smart-Water-Quality-Monitoring-System
   cd Smart-Water-Quality-Monitoring-System
   

3. *Install Python Requirements:*
   bash
   pip install pyserial
   

4. *Open the Project in PyCharm:*
   - Launch *PyCharm* and open the project folder.
   - Ensure the correct Python interpreter is selected.
   - Open main.py or interface.py (whichever is used in your project).

5. *Run the Live Interface:*
   - Click the *Run* button or right-click the Python file and select *Run*.
   - The GUI will open showing real-time data readings from the sensors via serial port.

6. *Start Monitoring:*
   - Make sure your microcontroller is connected to the right COM port.
   - Sensor data will automatically start appearing in the live dashboard.
   - Alerts (if configured) will pop up if any parameter crosses the safe threshold.
  
#### Results

![image](https://github.com/user-attachments/assets/d5060dcb-fc0d-47f9-80fe-e83667fddc6f)
