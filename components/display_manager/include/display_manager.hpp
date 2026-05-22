#pragma once

#include "state_machine.hpp"
#include <lvgl.h>
#include <cstdint>

namespace taptune {

class DisplayManager {
public:
    DisplayManager();
    ~DisplayManager();

    void applyState(AppState state);
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
