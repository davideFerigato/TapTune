#include "tone_player.hpp"
#include "pins.hpp"
#include <driver/ledc.h>
#include <esp_log.h>

static constexpr const char* TAG = "tone";

namespace taptune {

TonePlayer::TonePlayer() {
    ledc_timer_config_t timerCfg = {};
    timerCfg.speed_mode = LEDC_LOW_SPEED_MODE;
    timerCfg.duty_resolution = LEDC_TIMER_10_BIT;
    timerCfg.timer_num = LEDC_TIMER_0;
    timerCfg.freq_hz = 1000; // default, verrà cambiata
    timerCfg.clk_cfg = LEDC_AUTO_CLK;
    ESP_ERROR_CHECK(ledc_timer_config(&timerCfg));

    ledc_channel_config_t chanCfg = {};
    chanCfg.gpio_num = pins::kBuzzer;
    chanCfg.speed_mode = LEDC_LOW_SPEED_MODE;
    chanCfg.channel = LEDC_CHANNEL_0;
    chanCfg.timer_sel = LEDC_TIMER_0;
    chanCfg.duty = 0;
    chanCfg.hpoint = 0;
    ESP_ERROR_CHECK(ledc_channel_config(&chanCfg));

    ESP_LOGI(TAG, "Initialized on pin %d", pins::kBuzzer);
}

void TonePlayer::onStateChanged(AppState state) {
    currentState_ = state;
    stop();
    switch (state) {
        case AppState::Connecting:
            startTone(1200, 120, 280);
            break;
        case AppState::Streaming:
            startTone(1800, 300, 120);
            break;
        default:
            // silenzio
            break;
    }
}

void TonePlayer::tick() {
    if (!playing_) return;

    tickCounter_++;
    unsigned int currentPhase = isOnPhase_ ? onMs_ : offMs_;
    if (tickCounter_ >= currentPhase / 20) {
        tickCounter_ = 0;
        isOnPhase_ = !isOnPhase_;
        updatePwm();
    }
}

void TonePlayer::startTone(unsigned int freq, unsigned int onMs, unsigned int offMs) {
    freq_ = freq;
    onMs_ = onMs;
    offMs_ = offMs;
    tickCounter_ = 0;
    isOnPhase_ = true;
    playing_ = true;

    ledc_set_freq(LEDC_LOW_SPEED_MODE, LEDC_TIMER_0, freq_);
    updatePwm();
}

void TonePlayer::stop() {
    playing_ = false;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void TonePlayer::updatePwm() {
    if (isOnPhase_ && playing_) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 512); // 50% duty a 10bit
    } else {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    }
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

} // namespace taptune
