# 🌡️ Smart Environment Monitoring and Control System (IoT-Based)

This project is a smart temperature and humidity monitoring and control system using the **NodeMCU ESP8266**, **DHT22 sensor**, and **ThingSpeak** cloud platform. It enables real-time environmental data collection and allows **automatic or manual control** of fans and heaters.

---

## 📌 Features

- Measures **temperature** and **humidity** using DHT22 sensor.
- Sends real-time data to **ThingSpeak** for remote monitoring.
- Automatically controls **fans** and **heaters** based on set thresholds.
- Allows **manual ON/OFF control** via serial communication (from mobile app or PC).
- Built-in logic for emergency handling when temperature or humidity exceed safe limits.

---

## 🔧 Hardware Requirements

- NodeMCU ESP8266 (ESP-12E)
- DHT22 Temperature & Humidity Sensor
- 4x Relays for fan control
- 2x Relays for heater control
- ESP8266-compatible power supply
- Jumpers, Breadboard, or PCB
- Internet access (Wi-Fi)

---

## 🧠 Microcontroller Pin Configuration

| Device     | GPIO Pin |
|------------|----------|
| DHT22      | D3 (GPIO0) |
| Fan 1      | D4 (GPIO2) |
| Fan 2      | D2 (GPIO4) |
| Fan 3      | D1 (GPIO5) |
| Fan 4      | D6 (GPIO12) |
| Heater 1   | D7 (GPIO13) |
| Heater 2   | D5 (GPIO14) |

---

## 🔌 Serial Command Interface

You can send the following characters via Serial to control devices manually:

| Command | Action               |
|---------|----------------------|
| A       | Turn ON Fan 1        |
| a       | Turn OFF Fan 1       |
| B       | Turn ON Fan 2        |
| b       | Turn OFF Fan 2       |
| C       | Turn ON Fan 3        |
| c       | Turn OFF Fan 3       |
| D       | Turn ON Fan 4        |
| d       | Turn OFF Fan 4       |
| E       | Turn ON Heater 1     |
| e       | Turn OFF Heater 1    |
| F       | Turn ON Heater 2     |
| f       | Turn OFF Heater 2    |

You can also send formatted data in this structure to update thresholds:
