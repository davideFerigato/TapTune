# Design Decisions

## Why ESP32?
- Built‑in Bluetooth Classic (A2DP) and dual‑core performance.
- Easy to program with Arduino framework.
- Affordable and widely available.

## Audio output: PWM vs DAC
- The internal DAC pins (GPIO25/26) require AC‑coupling capacitors, which we didn't have initially.
- We switched to PWM on GPIO5 with a timer interrupt to generate audio, avoiding external components until capacitors arrive.

## Display animations
- Inspired by Apple HomePod: minimal, smooth, and informative.
- Different states: boot, idle (pulsing circle), connected (rotating dot), streaming (expanding ring), disconnecting (shrinking circle).

## LED behaviour
- Always active, even when display sleeps, to indicate device status.
- Red = ready, blue = connected, green = streaming.

## Buzzer jingles
- Custom frequencies to give a premium feel.
- Startup: ascending scale (confidence), connect: double beep, disconnect: descending scale.

## Modular firmware
- Separated into modules (audio, bluetooth, display, led, buzzer) for maintainability and future expansion.
- Clear separation of concerns; main .ino only orchestrates.