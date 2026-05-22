#include "config.hpp"
#include "pins.hpp"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static constexpr const char* TAG = "main";

extern "C" void app_main() {
    ESP_LOGI(TAG, "TapTune avviato - Fase 2");
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
