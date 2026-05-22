#include "led_indicator.hpp"
#include "pins.hpp"
#include <driver/gpio.h>
#include <esp_log.h>

static constexpr const char* TAG = "led";

namespace taptune {

LedIndicator::LedIndicator() {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << pins::kLedRed) | (1ULL << pins::kLedGreen) | (1ULL << pins::kLedBlue);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    // Inizializza spento
    setRgb(false, false, false);
    ESP_LOGI(TAG, "Initialized on pins R:%d G:%d B:%d", pins::kLedRed, pins::kLedGreen, pins::kLedBlue);
}

void LedIndicator::applyState(AppState state) {
    switch (state) {
        case AppState::Boot:
            setRgb(false, false, false); // off
            break;
        case AppState::Idle:
            setRgb(true, false, false); // rosso
            break;
        case AppState::Connecting:
            setRgb(true, false, true); // rosso+blu (magenta)
            break;
        case AppState::Connected:
            setRgb(false, false, true); // blu
            break;
        case AppState::Streaming:
            setRgb(false, true, false); // verde
            break;
    }
}

void LedIndicator::setRgb(bool r, bool g, bool b) {
    gpio_set_level(static_cast<gpio_num_t>(pins::kLedRed), r ? 1 : 0);
    gpio_set_level(static_cast<gpio_num_t>(pins::kLedGreen), g ? 1 : 0);
    gpio_set_level(static_cast<gpio_num_t>(pins::kLedBlue), b ? 1 : 0);
}

} // namespace taptune
