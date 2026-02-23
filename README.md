# 🎵 TapTune – The Ultimate DIY Smart Speaker

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://github.com/davideFerigato/TapTune/actions/workflows/build.yml/badge.svg)](https://github.com/davideFerigato/TapTune/actions)

**Tap. Connect. Immerse.**  
TapTune is a Bluetooth speaker with NFC activation, hypnotic OLED animations, RGB status, and rich 3W stereo sound. Built with ESP32 and PAM8403.

![TapTune](docs/images/photo_front.jpg)

## ✨ Features
- ⚡ **NFC Tap-to-Play** – Effortless pairing with a simple touch.
- 🌈 **Intelligent RGB Status** – Red (ready), blue (connected), green (streaming).
- 🎛️ **Premium Audio** – 3W stereo via PAM8403 amplifier, physical volume knob.
- 🖥️ **Living OLED Display** – HomePod‑inspired animations: pulsing circles, expanding rings.
- 🔊 **Sonic Feedback** – Custom startup chime and connection sounds.
- 🧠 **Always‑On Intelligence** – LED stays active even when display sleeps.
- 🔌 **Modular Firmware** – Clean, documented, ready for hacking.

## 🛠️ Hardware
- ESP32 Dev Board
- PAM8403 amplifier (with integrated potentiometer)
- 2× 3W speakers (4–8Ω)
- 0.96" OLED I²C
- RGB LED (common cathode)
- Passive buzzer
- PN532 NFC module (optional)
- Photoresistor, PIR motion sensor (optional)

See [assembly guide](docs/assembly_guide.md) for wiring details.

## Firmware Structure

```
firmware/src/
├── TapTune.ino          # Orchestration
├── pins.h               # Pin mapping
├── config.h             # Constants
├── audio/               # PWM audio output
├── bluetooth/           # A2DP sink
├── display/             # OLED animations
├── led/                 # RGB status
└── buzzer/              # Sound effects
```

## 🚀 Getting Started
1. Install [Arduino IDE](https://www.arduino.cc/en/software) and ESP32 board support.
2. Install required libraries (see [firmware/lib/README.md](firmware/lib/README.md)).
3. Open `firmware/src/TapTune.ino`, select **ESP32 Dev Module**, and upload.
4. Assemble hardware following [assembly guide](docs/assembly_guide.md).
5. Power on, tap your phone, and enjoy!

## 📚 Documentation
- [User Manual](docs/user_manual.md)
- [Assembly Guide](docs/assembly_guide.md)
- [Design Decisions](docs/design_decisions.md)

## 🤝 Contributing
Pull requests and ideas are welcome! Please use the issue templates.

## 📄 License
MIT © 2026 davideFerigato
