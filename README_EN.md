
# ESP32-Based Two-Wheel Self-Balancing Car Pitch Control System

## Table of Contents
- [中文 README](ESP32_Balancing_Car_README_CN.md)

## English README

### Project Name: ESP32-Based Two-Wheel Self-Balancing Car Pitch Control System
### Project Description:
This project involves the design of a two-wheel self-balancing robot car using the ESP32 microcontroller. The car uses the MPU6050 gyroscope sensor to measure tilt angles and employs PID control for stability. The system features Bluetooth communication, allowing for real-time adjustment of PID parameters via a mobile app, and provides movement control for forward, backward, and stop operations.

### Hardware Used
- **ESP32 Microcontroller**
- **MPU6050 Gyroscope and Accelerometer**
- **DRV8833 Motor Driver Module**
- **JGA25-310-CE DC Motors**
- **LM2596S DC-DC Buck Converter**
- **18650 Lithium-ion Battery**

### Project Structure
```
ESP32_ROBOT_CAR_CODE/
├── Angular_Speed_Test/
│   ├── Angular_Speed_Test.ino
│   ├── debug_custom.json
│   ├── debug.cfg
│   └── esp32.svd
├── Bluetooth_Connection_Test/
│   ├── .skip.esp32c3
│   ├── .skip.esp32s2
│   ├── .skip.esp32s3
│   ├── Bluetooth_Connection_Test.ino
│   ├── debug_custom.json
│   ├── debug.cfg
│   └── esp32.svd
├── Machine_Frame_Balance/
│   ├── debug_custom.json
│   ├── debug.cfg
│   ├── esp32.svd
│   └── Machine_Frame_Balance.ino
├── Motor_Drive_Direction_and_Dead_Zone_Test/
│   ├── DRV8833_MOTOR_TEST/
│   │   ├── debug_custom.json
│   │   ├── debug.cfg
│   │   ├── DRV8833_MOTOR_TEST.ino
│   │   ├── esp32.svd
│   │   └── readme.txt
│   ├── DRV8833_MOTOR_TEST_ledc/
│   │   └── DRV8833_MOTOR_TEST_ledc.ino
├── My_PIDCar_APP.v2.0/
│   ├── img.cpp
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── mainwindow.ui
│   ├── qtCarBluetooth.pro
│   └── qtCarBluetooth.pro.user
├── My_PIDCar_Main/
│   ├── debug_custom.json
│   ├── debug.cfg
│   ├── esp32.svd
│   └── My_PIDCar.ino
```

### Key Features
1. **PID Control:** Utilizes PID control to stabilize the robot based on real-time tilt angle and angular velocity measurements.
2. **Bluetooth Communication:** The car is controlled via Bluetooth using a mobile app to adjust PID parameters and control movement (forward, backward, stop).
3. **Modular Design:** The car supports the addition of modules such as sensors or cameras for further functionality.

### Software Requirements
- **Arduino IDE** for programming ESP32
- **QT Framework** for mobile app development

### Installation and Usage
1. **Hardware Setup:**
   - Connect all hardware components (MPU6050, ESP32, DRV8833, motors, and battery) according to the wiring diagram.
   - Ensure stable connections to avoid short circuits.

2. **Software Setup:**
   - Install necessary libraries for MPU6050 and Bluetooth communication in Arduino IDE.
   - Upload the firmware (My_PIDCar.ino) to the ESP32.
   - Compile and run the mobile app using **qtCarBluetooth.pro**.
   - Pair the mobile device with the ESP32 via Bluetooth to control the car.
