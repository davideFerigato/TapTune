#include "config.hpp"
#include "pins.hpp"
#include "state_machine.hpp"
#include "led_indicator.hpp"
#include "tone_player.hpp"
#include "display_manager.hpp"
#include "bt_manager.hpp"
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

    StateMachine sm([&](AppState state) {
        led.applyState(state);
        tone.onStateChanged(state);
        display.applyState(state);
    });

    sm.dispatch(AppEvent::BootCompleted);

    // Per test: avvia il Bluetooth subito
    bt.start();
    sm.dispatch(AppEvent::NfcTapped);   // simula il tap NFC per attivare la connessione

    while (true) {
        tone.tick();
        display.tick();

        // Processa eventi dal Bluetooth
        while (auto ev = bt.pollEvent()) {
            sm.dispatch(*ev);
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
