# ADR-003: Graphics library – LVGL vs Adafruit SSD1306

**Status:** Accepted

**Date:** 2026-05-22

**Context:**  
The SSD1306 128x64 display must show device status with clear text and, in the future, animations. Two main alternatives exist.

**Options:**

1. **Adafruit SSD1306** – lightweight, simple, only text and basic shapes.
2. **LVGL (v8)** – full graphics library with widgets, animations, themes.

**Decision:**  
We adopt **LVGL** because:
- It allows creating modern and attractive interfaces even on small screens.
- Official ESP‑IDF support, large community.
- Easy future extension (icons, progress bars, transition animations).
- Memory footprint is manageable (reduced buffers).

**Consequences:**
- Larger flash occupation (~150 KB) compensated by the 3 MB partition.
- Need for a periodic refresh (`lv_timer_handler()`) in the main loop.
- The driver for monochrome SSD1306 requires an adapter (our `flushCb` implementation).
