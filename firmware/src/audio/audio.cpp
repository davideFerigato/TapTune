#include "audio.h"
#include "config.h"
#include "pins.h"
#include "Arduino.h"

static const size_t BUFFER_SIZE = AUDIO_BUFFER_SIZE;
static uint8_t audioBuffer[BUFFER_SIZE];
static volatile size_t head = 0;
static volatile size_t tail = 0;

static hw_timer_t *audioTimer = NULL;
static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onAudioTimer() {
    if (head != tail) {
        int16_t sample = ( (int16_t)audioBuffer[tail + 1] << 8 ) | audioBuffer[tail];
        uint8_t uSample = (sample + 32768) >> 8;   // convert signed 16-bit to 8-bit unsigned
        ledcWrite(AUDIO_PWM_CHANNEL, uSample);
        tail += 2;
        if (tail >= BUFFER_SIZE) tail = 0;
    }
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