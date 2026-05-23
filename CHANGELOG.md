# Changelog

## [0.1.0] – 2026-05-23

### Added
- State machine with 5 states and callback
- LED indicator (RGB)
- Non‑blocking PWM tone player
- Display manager based on LVGL for SSD1306 OLED
- Bluetooth A2DP sink (discoverable, events)
- NFC manager PN532 (tag emulation)
- Unit tests for state machine
- Documentation: README, ARCHITECTURE, ADR, CHANGELOG
- CI/CD GitHub Actions (build and test) – placeholder

### Fixed
- Build system: used 4 MB flash, custom partition table
- Fixed CMake dependencies (ESP-IDF v6 drivers)
