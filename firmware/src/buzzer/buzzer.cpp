#include "buzzer.h"
#include "pins.h"
#include <Arduino.h>

static void playTone(int freq, int dur) {
    tone(PIN_BUZZER, freq, dur);
    delay(dur + 30);
    noTone(PIN_BUZZER);
}

void buzzer_init() {
    pinMode(PIN_BUZZER, OUTPUT);
}

void buzzer_play_startup() {
    playTone(523,150); delay(50);
    playTone(659,150); delay(50);
    playTone(784,250); delay(80);
    playTone(1047,400);
}

void buzzer_play_connect() {
    playTone(880,120); delay(60);
    playTone(1319,250);
}

void buzzer_play_disconnect() {
    playTone(988,150); delay(50);
    playTone(784,150); delay(50);
    playTone(659,200); delay(60);
    playTone(523,300);
}