#pragma once

#include "state_machine.hpp"
#include <lvgl.h>
#include <cstdint>

namespace taptune {

/**
 * @brief Manages the OLED display.
 * 
 * Initializes the I2C bus for the SSD1306 display and the LVGL library.
 * Updates the screen in real-time to reflect the current application state
 * (e.g., "Idle", "Streaming").
 */
class DisplayManager {
public:
    /**
     * @brief Initializes I2C and LVGL, sets up the default screen.
     */
    DisplayManager();

    /**
     * @brief Deinitializes LVGL.
     */
    ~DisplayManager();

    /**
     * @brief Updates the label on the display to reflect the new state.
     * @param state The current application state.
     */
    void applyState(AppState state);

    /**
     * @brief Calls the LVGL timer handler. Must be called every 20ms.
     */
    void tick();

private:
    void i2cInit();
    void lvglInit();
    void updateLabel(AppState state);

    static void flushCb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
    static void i2cWrite(uint8_t addr, const uint8_t *data, size_t len);

    lv_obj_t *label_ = nullptr;
    bool lvgl_initialized_ = false;
};

} // namespace taptune
