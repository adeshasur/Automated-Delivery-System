# Automated Delivery System

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![Robotics](https://img.shields.io/badge/Robotics-Project-FF6F61?style=for-the-badge)](https://github.com/adeshasur/Automated-Delivery-System)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

**Robotics NIBM Project** - A sophisticated automated sorting and delivery system featuring a smart conveyor belt and a mobile delivery robot.

![3D Model](3D%20Model.png)

---

## System Overview

The Automated Delivery System is designed to streamline the process of measuring, categorizing, and delivering packages based on their physical dimensions. The project consists of two primary modules:

1.  **Conveyor Sender Module**: Detects incoming boxes, measures their width and height using ultrasonic sensors, categorizes them, and moves them forward.
2.  **Robot Receiver Module**: (Work in Progress) Receives the categorized items and delivers them to their designated destinations.

---

## Features

-   **Automatic Box Detection**: Uses IR sensors to detect when a box enters the measurement zone.
-   **Precision Measurement**: Dual HC-SR04 Ultrasonic sensors for horizontal and vertical dimension calculation.
-   **Smart Categorization**:
    -   **Small (Type A)**: `<= 3cm`
    -   **Medium (Type B)**: `<= 6cm`
    -   **Large (Type C)**: `<= 8cm`
-   **Real-time Feedback**: I2C LCD (16x2) displays current status, measurements, and box type.
-   **Industrial Control**: PWM-based motor speed control for smooth conveyor operation.

---

## Hardware Components

| Component | Purpose |
| :--- | :--- |
| **Arduino Uno / Nano** | Central Control Unit |
| **HC-SR04 (x2)** | Ultrasonic Distance Measurement |
| **IR Obstacle Sensor** | Box Detection Trigger |
| **L298N Motor Driver** | Conveyor Belt Speed & Direction Control |
| **I2C LCD (16x2)** | Status & Measurement Display |
| **DC Gear Motor** | Conveyor Belt Power |

---

## Pin Mapping (Conveyor Sender)

| Sensor/Actuator | Arduino Pin |
| :--- | :--- |
| **IR Sensor** | Pin 2 |
| **Ultrasonic 1 (Trig)** | Pin 4 |
| **Ultrasonic 1 (Echo)** | Pin 3 |
| **Ultrasonic 2 (Trig)** | Pin 6 |
| **Ultrasonic 2 (Echo)** | Pin 5 |
| **Motor Speed (ENB)** | Pin 9 |
| **Motor IN3** | Pin 10 |
| **Motor IN4** | Pin A0 |
| **LCD I2C** | SDA (A4), SCL (A5) |

---

## Getting Started

### 1. Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) installed.
- Required Libraries:
    - `Wire.h` (Built-in)
    - `LiquidCrystal_I2C.h`

### 2. Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/adeshasur/Automated-Delivery-System.git
   ```
2. Open `Conveyor_Sender/Conveyor_Sender.ino` in Arduino IDE.
3. Select your board and port, then click **Upload**.

---

## Calibration
You can adjust the measurement thresholds and empty space values in the `Conveyor_Sender.ino` file:

```cpp
int emptySpaceWidth = 9;   // Distance to the side wall (cm)
int emptySpaceHeight = 12; // Distance to the top sensor (cm)

int smallBox = 3;   
int mediumBox = 6;   
int largeBox = 8;
```

---

## Roadmap
- [x] Initial Conveyor logic implementation.
- [x] Box categorization system.
- [ ] Implement `Robot_Receiver` communication logic.
- [ ] Add line-following or obstacle avoidance for the delivery robot.
- [ ] Battery level monitoring for the receiver module.

---

## Contributing
Contributions are welcome! Feel free to open an issue or submit a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
Developed by **[Adesha Sur](https://github.com/adeshasur)**
