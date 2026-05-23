#include "config.hpp"
#include "pins.hpp"
#include "state_machine.hpp"
#include "led_indicator.hpp"
#include "tone_player.hpp"
#include "display_manager.hpp"
#include "bt_manager.hpp"
#include "nfc_manager.hpp"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static constexpr const char* TAG = "main";

using namespace taptune;

extern "C" void app_main() {
    ESP_LOGI(TAG, "TapTune avviato");

    LedIndicator led;
    TonePlayer tone;
    DisplayManager display;
    BtManager bt;
    NfcManager nfc;

    StateMachine sm([&](AppState state) {
        led.applyState(state);
        tone.onStateChanged(state);
        display.applyState(state);
    });

    sm.dispatch(AppEvent::BootCompleted);

    // Avvia il Bluetooth (diventa discoverable)
    bt.start();

    while (true) {
        tone.tick();
        display.tick();

        while (auto ev = bt.pollEvent()) {
            sm.dispatch(*ev);
        }
        while (auto ev = nfc.pollEvent()) {
            sm.dispatch(*ev);
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
