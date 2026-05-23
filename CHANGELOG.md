# Changelog

## [1.0.0] – 2022-12-22

### Added
- First stable release
- Full state machine with 5 states
- RGB LED indicator
- Non‑blocking PWM tone player
- LVGL-based display manager for SSD1306 OLED
- Bluetooth A2DP sink (discoverable, event-driven)
- NFC manager using PN532 in tag emulation mode
- Unit tests for state machine (Unity + native C++)
- Complete documentation: README, architecture, ADR, Doxygen
- CI/CD pipeline with build, test, clang-tidy, and documentation deployment
- GitHub Actions workflows for CI and Docs

### Fixed
- Build system configured for 4 MB flash
- CMake dependencies aligned with ESP‑IDF v6 drivers
