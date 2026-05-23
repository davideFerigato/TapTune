<p align="center">
  <img src="https://raw.githubusercontent.com/davideFerigato/TapTune/main/docs/demo/tap_tune_logo.png" width="200" alt="TapTune Logo"/>
</p>

<h1 align="center">TapTune</h1>

<div align="center">

![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![Framework](https://img.shields.io/badge/framework-ESP--IDF%206.0-red)
![C++17](https://img.shields.io/badge/C++-17-brightgreen)
![License](https://img.shields.io/badge/license-MIT-yellow)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/davideFerigato/TapTune/ci.yml?label=CI)
![GitHub last commit](https://img.shields.io/github/last-commit/davideFerigato/TapTune)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/davideFerigato/TapTune?label=release)

</div>

**TapTune** turns your ESP32 into a high-quality Bluetooth A2DP speaker with a touch of NFC magic: simply tap your phone and the music starts playing.

---

## ✨ Features

- 🎵 **Bluetooth A2DP Speaker** – Stereo playback via internal DAC and PAM8403 amplifier.
- 📱 **One‑tap NFC** – Tap your phone to automatically open Bluetooth settings and connect.
- 🖥️ **OLED Display 128x64** – Shows current state (Idle, Connecting, Streaming) with smooth animations.
- 🌈 **RGB LED** – Immediate visual feedback: red when idle, magenta while pairing, blue when connected, green during playback.
- 🔊 **PWM Buzzer** – Non‑blocking tones for pairing and streaming events.
- 🧠 **Robust State Machine** – State and transition management through callbacks.
- 🧪 **Unit Tests** – Full coverage of all transitions with Unity (and native C++ tests).
- 📚 **Complete Documentation** – README, Architecture, ADR, Doxygen.

---

## 📂 Repository Structure

```
TapTune/
├── .github/            # CI/CD workflows
├── docs/               # Technical documentation, ADR, schematics
├── firmware/           # Source code (ESP‑IDF + C++17)
│   ├── components/     # Modular components
│   ├── src/            # main.cpp, pins, config
│   ├── test/           # Unit tests
│   └── CMakeLists.txt
├── platformio.ini      # PlatformIO configuration
├── partitions.csv      # Partition table
├── README.md
├── ARCHITECTURE.md
├── CHANGELOG.md
└── LICENSE
```

---

## 🚀 Getting Started

### Prerequisites

- [PlatformIO IDE](https://platformio.org/) (VS Code) or PlatformIO CLI
- USB‑UART drivers for ESP32
- Python 3.9+

### Build and Upload

1. Clone the repository:
   ```bash
   git clone https://github.com/davideFerigato/TapTune.git
   cd TapTune
   ```
2. Build:
   ```bash
   pio run
   ```
3. Flash to ESP32:
   ```bash
   pio run -t upload
   ```
4. Serial monitor:
   ```bash
   pio device monitor
   ```

### Running Tests

Native (local) tests:
```bash
./run_tests.sh
```

On‑target tests (requires ESP32 connected):
```bash
pio test -e esp32dev_test
```

---

## 🧩 Hardware

| Component            | Pin                  | Notes                                  |
|----------------------|----------------------|----------------------------------------|
| ESP32 DevKit V1      | –                    | Dual core 240 MHz, 4 MB Flash          |
| OLED SSD1306 128x64  | SDA:21, SCL:22       | Shared I²C bus                         |
| PN532 NFC            | SDA:21, SCL:22       | I²C, DIP SW1=ON SW2=OFF                |
| RGB LED (common cathode) | R:32, G:33, B:27 | 220Ω resistors on each channel         |
| Passive buzzer       | 14                   | PWM driven (LEDC)                      |
| PAM8403 amplifier    | Input: GPIO25/26     | 10µF capacitors in series              |

Detailed schematic in [`docs/hardware/taptune-schematic.pdf`](docs/hardware/taptune-schematic.pdf).

---

## 🧠 Firmware Architecture

See [`ARCHITECTURE.md`](ARCHITECTURE.md) for the state diagram and component interaction.

---

## 📈 Roadmap

- [ ] Phase 0‑7: Setup, core components, integration
- [ ] Phase 8: End‑to‑end integration, system tests
- [ ] Phase 9: Technical documentation and Doxygen
- [ ] Phase 10: CI/CD GitHub Actions
- [ ] Phase 11: Release v1.0.0
- [ ] Phase 12: Video demo

---

## 📄 License

Distributed under the MIT License. See [`LICENSE`](LICENSE) for details.

---

<p align="center">
  Made with ❤️ by Davide Ferigato
</p>
