# Proyecto IDC

# 🔐 RFID-Based Access Control System with MQTT and Telegram Integration

This project implements a secure and modular **RFID-based access control system** using an **ESP32 microcontroller**, a **local UID database**, and **real-time notifications** via **Telegram** through the **MQTT protocol**.

It is designed to be portable, scalable, and understandable, separating embedded logic from external services like messaging bots. The system is ideal for prototyping smart locks, restricted-access zones, or IoT-connected doors.

## 📁 Project Structure

```plaintext
📦 Project Root
├── README.md
├── Arduino/
│ ├── src/ # Main firmware code for ESP32 (main.cpp)
│ │ └── main.cpp
│ ├── include/ # Header files and abstract interfaces (ports)
│ │ ├── adapters/ # Notifier / Output interface definitions 
│ │ ├── core/ # AccessController definition
│ │ └── ports/ # Interfaces definitions
│ ├── lib/ # Implementations (LEDs, Serial, MQTT...)
│ │ ├── adapters/
│ │ └── core/
│ ├── data/
│ │ └── cards.txt # Authorized RFID UIDs (one per line)
│ ├── test/ # There are not any test working at the moment
│ └── platformio.ini # PlatformIO configuration
└── Telegram_Bot/
  ├── bot.py # Telegram bot logic (command handling)
  └── MQTT_client.py # MQTT subscriber logic (hidden complexity)
```

## 🚀 Project Features

- ✅ **RFID Reader** (MFRC522) to detect user identity
- ✅ **Local whitelist-based access validation** using LittleFS
- ✅ **Output actions** (LEDs, buzzers, actuators)
- ✅ **Pluggable notifier system** (Serial, MQTT, etc.)
- ✅ **MQTT integration** for pushing messages to external services
- ✅ **Telegram bot** for human-readable access alerts

## 🧰 Technologies Used

| Component         | Technology      |
|------------------|------------------|
| Microcontroller  | ESP32            |
| Development Env. | PlatformIO       |
| RFID Reader      | MFRC522          |
| Filesystem       | LittleFS         |
| Networking       | Wi-Fi + MQTT     |
| Messaging Bot    | Telegram + Python |
| Communication    | PubSubClient, paho-mqtt |
| Notification     | JSON via MQTT    |

## 🧑‍💻 Developer Guide

### 🔧 ESP32 Firmware

1. **Setup PlatformIO** and clone the repo.
2. Add authorized RFID UIDs to `Arduino/data/cards.txt`:
```bash
04A1B2C3D4
123456789A
```
3. Flash the code:
```bash
pio run --target upload
```
4. Upload the file system:
```bash
pio run --target uploadfs
```

### 🧩 Add a Notifier

Add a new class inheriting from the Notifier interface inside include/ports/Notifier.h. Then implement your class in lib/adapters/ and register it using AccessController::addNotifier().

### 🛠️ Example Notifiers
- SerialNotifier: Outputs access results over serial.
- MQTTNotifier: Publishes JSON messages to a topic.

## 🧑‍🏫 User Guide

### Step-by-Step Usage
1. Power on the ESP32.
2. Open a serial monitor to see logs.
3. Place a card on the RFID reader.
4. The system:
    - Validates if the UID is authorized.
    - Activates an output device (e.g. green LED for access).
    - Sends a message to Telegram via MQTT.

## 🛰️ Telegram Bot Setup

The bot is designed to run independently from the embedded code.

### Prerequisites
- Python 3.10+
- `pip install python-telegram-bot paho-mqtt`

### Configure Telegram_Bot/bot.py
Update these placeholders with your credentials:
```Py
TELEGRAM_TOKEN = "YOUR_BOT_TOKEN"
MQTT_CONFIG = {
    "host": "YOUR_BROKER_IP",
    "port": 1883,
    "username": "your_user",
    "password": "your_pass"
}
```

### Run the Bot
```bash
python3 Telegram_Bot/bot.py
```

Then on Telegram, send /start to the bot. You’ll begin receiving real-time alerts like:
```bash
🔔 UID: 04A1B2C3D4
Estado: ✅ ACCESO PERMITIDO
```

## 🐛 Known Issues and Limitations

| Issue                        | Description / Workaround                                              |
|------------------------------|---------------------------------------------------------------------|
| PlatformIO + Testing          | Mocking Arduino.h is difficult. Consider integration tests on-device. |
| Dependency issues (PubSubClient) | Ensure it is added via `lib_deps` in `platformio.ini`.                |
| Native tests fail with STL/Arduino | Some libraries expect a hardware context; avoid using `std::string` in cross-boundary code if testing. |
| Telegram bot persistence      | Current version does not store `chat_id` persistently. Restarting the bot requires re-sending `/start`. |

## 🧠 Lessons Learned

- PlatformIO is powerful but can complicate testing.
- ESP32 offers better compatibility over Pico W in this context.
- Designing with a clean architecture allowed us to swap components (e.g. `SerialNotifier` → `MQTTNotifier`) without changing core logic.
- Splitting the bot and firmware helped isolate responsibilities and avoid resource constraints on the microcontroller.

## 📌 Future Improvements

- Secure MQTT with TLS/SSL
- Admin Telegram commands to add/remove UIDs remotely
- Persistent Telegram chat ID
- Real-time web dashboard
- Mobile app integration (Flutter or React Native)

## 👤 Author

**Elena Cofent Muñoz, Julian Melmer Stiefkens**

Project developed as part of a practical IoT system at university.  
Feel free to contribute or suggest improvements!