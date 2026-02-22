#include "audio.h"
#include "config.h"
#include "pins.h"
#include "driver/ledc.h"
#include "esp_timer.h"  // o il timer HAL dell'ESP32

static const size_t BUFFER_SIZE = AUDIO_BUFFER_SIZE;
static uint8_t audioBuffer[BUFFER_SIZE];
static volatile size_t head = 0;
static volatile size_t tail = 0;
static hw_timer_t *audioTimer = NULL;
static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

static void IRAM_ATTR onAudioTimer() {
    // ... stesso codice ...
}

void audio_init() {
    ledcAttach(PIN_AUDIO_PWM, AUDIO_PWM_FREQ, AUDIO_PWM_RESOLUTION);
    ledcWrite(AUDIO_PWM_CHANNEL, 0);
    audioTimer = timerBegin(AUDIO_TIMER_FREQ_HZ);
    timerAttachInterrupt(audioTimer, &onAudioTimer);
    timerAlarm(audioTimer, AUDIO_SAMPLE_PERIOD_US, true, 0);
}

void audio_play_sample(const uint8_t *data, uint32_t length) {
    for (size_t i = 0; i < length; i++) {
        audioBuffer[head] = data[i];
        head = (head + 1) % BUFFER_SIZE;
    }
}