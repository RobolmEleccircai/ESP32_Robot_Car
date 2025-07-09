
# 基于 ESP32 的两轮自平衡小车俯仰控制系统

## 目录
- [English README](README.md)

## 中文 README

### 项目名称：基于 ESP32 的两轮自平衡小车俯仰控制系统
### 项目描述：
本项目设计了一款基于 ESP32 主控芯片的两轮自平衡小车。小车使用 MPU6050 陀螺仪传感器来测量倾斜角度，并通过 PID 控制算法保持平衡。该系统支持蓝牙通信，允许用户通过手机应用调节 PID 参数，并提供前进、后退和停止等运动控制。

### 硬件平台
- **ESP32 微控制器**
- **MPU6050 陀螺仪与加速度计**
- **DRV8833 电机驱动模块**
- **JGA25-310-CE 直流电机**
- **LM2596S DC-DC 降压模块**
- **18650 锂电池**

### 项目结构
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

### 关键功能
1. **PID 控制：** 利用 PID 控制算法，根据实时测量的小车倾斜角度和角速度来保持平衡。
2. **蓝牙通信：** 通过蓝牙连接，用户可以调节 PID 参数并控制小车的运动（前进、后退、停止）。
3. **模块化设计：** 小车设计支持扩展，可以根据需求添加传感器或其他功能模块。

### 软件要求
- **Arduino IDE** 用于编程 ESP32
- **QT 框架** 用于移动应用开发

### 安装与使用
1. **硬件设置：**
   - 按照接线图连接所有硬件组件（MPU6050、ESP32、DRV8833、电机和电池）。
   - 确保所有模块稳定连接，避免短路。

2. **软件设置：**
   - 在 Arduino IDE 中安装必要的库文件，用于 MPU6050 和蓝牙通信。
   - 上传固件（My_PIDCar.ino）到 ESP32。
   - 使用 **qtCarBluetooth.pro** 编译并运行手机应用。
   - 通过蓝牙将手机与 ESP32 配对，控制小车。
