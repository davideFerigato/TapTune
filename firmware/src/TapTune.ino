/**
 * TapTune - Main orchestration file
 * 
 * This file initializes all modules and contains the main loop.
 * It also defines the callback functions required by the bluetooth module.
 */

#include "pins.h"
#include "config.h"
#include "audio/audio.h"
#include "bluetooth/bluetooth.h"
#include "led/led.h"
#include "buzzer/buzzer.h"
#include "display/display.h"

// Global state variables (shared among modules)
bool bluetoothConnected = false;
bool audioStreaming = false;

// Callbacks for bluetooth events (declared in bluetooth.h)
void bluetooth_on_connected() {
    bluetoothConnected = true;
    buzzer_play_connect();
    display_on_connected();
    led_update_state(bluetoothConnected, audioStreaming);
}

void bluetooth_on_disconnected() {
    bluetoothConnected = false;
    audioStreaming = false;
    buzzer_play_disconnect();
    display_on_disconnected();
    led_update_state(bluetoothConnected, audioStreaming);
}

void bluetooth_on_audio_started() {
    audioStreaming = true;
    display_on_audio_started();
    led_update_state(bluetoothConnected, audioStreaming);
}

void bluetooth_on_audio_stopped() {
    audioStreaming = false;
    display_on_audio_stopped();
    led_update_state(bluetoothConnected, audioStreaming);
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println(F("TapTune starting..."));

    led_init();
    buzzer_init();
    display_init();
    audio_init();
    bluetooth_init("TapTune");

    buzzer_play_startup();
    led_update_state(false, false);
}

void loop() {
    display_update();   // handles animations and display power management
    // Future: read sensors (photoresistor, PIR), handle button, etc.
    delay(10);
}