#include "led.h"
#include "pins.h"
#include <Arduino.h>

void led_init() {
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_LED_B, OUTPUT);
    led_set(false, false, false);
}

void led_set(bool r, bool g, bool b) {
    digitalWrite(PIN_LED_R, r ? HIGH : LOW);
    digitalWrite(PIN_LED_G, g ? HIGH : LOW);
    digitalWrite(PIN_LED_B, b ? HIGH : LOW);
}

void led_update_state(bool connected, bool streaming) {
    if (!connected) {
        led_set(true, false, false);  // red
    } else if (streaming) {
        led_set(false, true, false);  // green
    } else {
        led_set(false, false, true);  // blue
    }
}