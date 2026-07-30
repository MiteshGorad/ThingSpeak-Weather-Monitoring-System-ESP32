# 🌦️ ThingSpeak-Based Weather Monitoring System (ESP32)

An IoT-based weather monitoring system built using two ESP32 development boards. The transmitter node collects environmental data from sensors and uploads it to ThingSpeak. The receiver node retrieves the latest data from ThingSpeak and displays it on a 16×2 I2C LCD.

---

## Features

- 🌡️ Temperature Monitoring
- 💧 Humidity Monitoring
- 🌫️ Air Quality / Gas Level Monitoring (MQ-9)
- ☁️ Cloud Data Logging using ThingSpeak
- 📡 Wi-Fi Communication
- 🖥️ Real-Time LCD Display
- 🔄 Automatic Data Refresh

---

## Hardware

- ESP32 DevKit ×2
- DHT11 Temperature & Humidity Sensor
- MQ-9 Gas Sensor
- 16×2 I2C LCD
- Breadboard
- Jumper Wires
- USB Cable

---

## Software

- Arduino IDE
- ThingSpeak
- ArduinoJson
- DHT Sensor Library
- LiquidCrystal_I2C
- HTTPClient

---

## Project Architecture

```
DHT11 + MQ-9
        │
        ▼
   ESP32 Transmitter
        │
   Wi-Fi Upload
        │
        ▼
   ThingSpeak Cloud
        │
   Wi-Fi Download
        │
        ▼
   ESP32 Receiver
        │
        ▼
    16×2 I2C LCD
```

---

## ThingSpeak Fields

| Field | Description |
|--------|-------------|
| Field 1 | Temperature (°C) |
| Field 2 | Humidity (%) |
| Field 3 | MQ-9 Sensor Value |

---

## Repository Structure

```
transmitter/
    ESP32 code for reading sensors and uploading data.

receiver/
    ESP32 code for reading data from ThingSpeak and displaying it.

circuit/
    Wiring diagram and schematic.

images/
    Project photos and screenshots.

docs/
    Documentation and project report.
```

---

## Future Improvements

- Rain Sensor
- BMP280 (Pressure Sensor)
- OLED Display
- Buzzer Alert
- Mobile Dashboard
- MQTT Support
- ESP-NOW Communication

---

## Author

**Mitesh Gorad**

M.Sc. Computer Science  
Electronics • Embedded Systems • IoT • Robotics
