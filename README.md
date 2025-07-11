# 🌍 RATTlestone: The Rural Climate Vigilante 🚨

> A scalable, low-cost weather station prototype for detecting **illegal carbon emissions** in rural industrial zones — powered by **ESP32 NodeMCU** and **Arduino Uno Rev3**.

---

## 🧠 Key Features

- ✅ **MQ135 Air Quality Sensor** (Detects CO₂, NH₃, smoke, etc.)
- 🌡️ **DHT11 Temperature + Humidity Sensor**
- 📺 **I2C LCD Display** for local readout
- 🌐 **Wi-Fi Dashboard** using ESP32 Web Server
- 🔁 Supports both **Arduino Uno** and **ESP32**
- 🛠️ Portable & ATL Lab-friendly
- 🧾 Ideal for **Smart City** / **SDG 13** / **School Science Projects**

---

## 🛠️ Hardware Used

| Component            | Function                         |
|----------------------|----------------------------------|
| ESP32 NodeMCU        | Wi-Fi + Data Processing          |
| Arduino UNO Rev3     | Alternate Microcontroller        |
| MQ135 Sensor         | Air Quality Measurement          |
| DHT11 Sensor         | Temp & Humidity                  |
| LCD 16x2 (I2C)       | Visual Output                    |
| Jumper Wires + Breadboard | Prototyping                  |

---

## 🌐 Live Preview

If hosted via ESP32 (on same Wi-Fi), view live air quality stats via local IP (printed on Serial Monitor).

Or simulate on your personal server.

---

## 📷 Project Glimpse

![Setup Demo](Images/setup-demo.jpg)

---

## 🧪 How to Use

1. Clone this repo.
2. Choose your board (`ESP32` or `Arduino Uno`)
3. Connect:
   - MQ135 → A0 (UNO) or D35 (ESP32)
   - DHT11 → D4
   - LCD → SDA/SCL (I2C)
4. Upload code via Arduino IDE
5. Monitor values on LCD & via Serial / Web

---

## ✨ Use Case

- 🔍 Spot illegal carbon emission in unregulated zones
- 📚 ATL / School Innovation Projects
- 🏙️ Smart Village Tech
- 🌐 Weather Watchdog for the Unseen

---

## 💡 Future Upgrades

- 📸 ESP32-CAM for photo documentation
- ☁️ Firebase/Google Sheets integration
- 🚘 Rover mode to auto-detect polluters
- 🔔 Buzzer alerts on threshold

---

## 👨‍💻 Built By

**[Rahul Smritijeet](https://github.com/rahulsmritijeet)** — Student, Innovator, and proud creator of chaos.  
> This is hardware. Real. Raw. Rattlestone.”

---

## ⚖️ License

MIT — Use it. Remix it. Just don’t greenwash it.


