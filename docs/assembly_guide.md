# Assembly Guide

## Components needed
- ESP32 development board
- PAM8403 amplifier module (with volume knob)
- 2x 3W speakers (4–8 Ω)
- PN532 NFC module (optional)
- 0.96" OLED display (I²C)
- RGB LED (common cathode)
- Passive buzzer
- Push button (for NFC simulation)
- Photoresistor (LDR) + 10k resistor
- PIR motion sensor
- Resistors: 3x 220Ω (for LED)
- Breadboard and jumper wires

## Wiring diagram
See `docs/images/wiring_diagram.png` for detailed connections.

## Step-by-step
1. Connect the ESP32 to the breadboard.
2. Connect the PAM8403:
   - 5V → VIN (ESP32)
   - GND → GND
   - L (input) → GPIO5 via 10µF capacitor (+ to ESP32)
   - R (input) → GPIO5 via 10µF capacitor (mono) or GPIO26 for stereo
   - Speaker outputs → left and right speakers
3. Connect the OLED:
   - VCC → 3.3V
   - GND → GND
   - SDA → GPIO21
   - SCL → GPIO22
4. Connect the RGB LED:
   - Common (longest) → GND
   - Red → GPIO32 via 220Ω
   - Green → GPIO33 via 220Ω
   - Blue → GPIO27 via 220Ω
5. Connect the buzzer:
   - Positive → GPIO14
   - Negative → GND
6. (Optional) Connect button between GPIO15 and GND.
7. (Optional) Connect photoresistor divider to GPIO34.
8. (Optional) Connect PIR output to GPIO4.

## Upload the firmware
- Install required libraries (see firmware/lib/README.md).
- Open `firmware/src/TapTune.ino` in Arduino IDE.
- Select board "ESP32 Dev Module".
- Upload.