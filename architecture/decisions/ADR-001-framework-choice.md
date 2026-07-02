# ADR-001: Framework choice – ESP‑IDF vs Arduino

**Status:** Accepted

**Date:** 2022-10-15

**Context:**  
We need to develop firmware for ESP32 featuring Bluetooth A2DP, NFC, LVGL display, and real‑time I/O. The base framework must be chosen.

**Options considered:**

1. **Arduino framework** on PlatformIO  
   - Simple, many libraries, but limited abstraction and suboptimal for real multitasking.

2. **Native ESP‑IDF** on PlatformIO  
   - Full control, official Espressif APIs, complete FreeRTOS support, modern drivers.

**Decision:**  
We choose **ESP‑IDF** for the following reasons:
- Official and up‑to‑date support for Bluetooth A2DP and NFC features.
- Higher production reliability.
- Allows C++17 usage, task priority management, and optimized memory.
- Better technical documentation and advanced debugging capabilities.

**Consequences:**
- Slightly steeper learning curve.
- Need to write custom components (e.g., I2C driver) but with full control.
- Easier integration with tests (Unity) and native CI/CD.
