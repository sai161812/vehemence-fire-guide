# 🔥 Firefighter Smart Escape Pathfinder (Prototype)

A wearable prototype designed to help firefighters **identify a safe direction toward an exit** inside smoke-filled buildings.
The system combines **temperature sensing, obstacle detection, and RF exit beacon detection** to determine whether the direction a firefighter is facing is safe.

---

# Project Status

This repository currently contains a **working prototype stage** where:

* ESP32 reads **temperature**
* ESP32 measures **distance to obstacles**
* ESP32 detects **RF exit signal**
* System evaluates safety conditions
* LED indicates whether the direction is **safe or unsafe**

The **exit beacon transmitter setup is prepared but not yet finalized in code testing**.

---

# Hardware Used

| Component                            | Purpose                  |
| ------------------------------------ | ------------------------ |
| ESP32 Dev Module                     | Main microcontroller     |
| MLX90614 Infrared Temperature Sensor | Detects dangerous heat   |
| HC-SR04 Ultrasonic Sensor            | Detects obstacles        |
| 433 MHz RF Receiver                  | Detects exit beacon      |
| 433 MHz RF Transmitter               | Exit beacon source       |
| LED                                  | Safe direction indicator |
| 220Ω Resistor                        | LED current limiting     |
| Power Bank                           | System power supply      |
| Breadboard + Jumper Wires            | Prototyping connections  |

---

# System Concept

The firefighter rotates their body while wearing the device.

The system scans the direction they are facing and checks three conditions:

1. **Temperature safety**
2. **Obstacle clearance**
3. **Exit beacon detection**

If all conditions are satisfied, the device indicates a **safe path**.

---

# Safety Logic

```
temperature < temperature_threshold
AND
distance > obstacle_threshold
AND
rf_signal_detected
```

If true:

```
LED ON
```

If false:

```
LED OFF
```

---

# Hardware Connections

## MLX90614 Temperature Sensor

```
VIN → ESP32 3.3V
GND → ESP32 GND
SDA → GPIO21
SCL → GPIO22
```

---

## HC-SR04 Ultrasonic Sensor

```
VCC  → ESP32 5V
GND  → ESP32 GND
TRIG → GPIO5
ECHO → GPIO18
```

---

## RF Receiver

```
VCC → ESP32 5V
GND → ESP32 GND
DATA → GPIO27
ANT → 17 cm wire antenna
```

---

## LED Indicator

```
GPIO2 → 220Ω resistor → LED → GND
```

---

# Exit Beacon Setup

The exit location is marked using a **433 MHz RF transmitter**.

Current prototype setup:

```
VCC → 5V power source
GND → GND
DATA → VCC
ANT → 17 cm wire antenna
```

Connecting **DATA to VCC** forces the transmitter to broadcast continuously, creating a simple RF beacon.

---

# Software Environment

Development environment:

```
Arduino IDE
```

Required library:

```
Adafruit MLX90614
```

Install using Arduino Library Manager.

---

# Current Program Behavior

Every cycle the ESP32 performs:

1. Read **object temperature** from MLX90614
2. Measure **distance** using ultrasonic sensor
3. Detect **RF signal presence**
4. Evaluate safety logic
5. Turn LED **ON or OFF**

Serial Monitor prints sensor data for debugging.

Example output:

```
Temperature: 28.3 C
Distance: 65 cm
RF Signal: 1
SAFE DIRECTION
```

---

# Power

The prototype is currently powered using:

```
USB power bank → ESP32
```

---

# Current Limitations

* RF receiver can produce **noise / false signals**
* Exit direction detection is **basic**
* No enclosure or wearable mounting yet

These will be improved in future iterations.

---

# Future Improvements

Planned enhancements include:

* Signal filtering for RF detection
* Haptic vibration feedback
* Multiple directional sensors
* Better exit direction estimation
* Wearable enclosure integration

---

# Prototype Goal

Demonstrate a **low-cost embedded system concept** that assists firefighters in identifying safer escape directions during emergency situations.

---
