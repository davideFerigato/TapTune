#pragma once

#include "state_machine.hpp"

namespace taptune {

/**
 * @brief Controls the passive buzzer using PWM.
 * 
 * Plays non-blocking audio patterns for application events:
 * - Connecting: Short beep at 1200Hz.
 * - Streaming: Alternating beep at 1800Hz.
 */
class TonePlayer {
public:
    TonePlayer();
    void onStateChanged(AppState state);
    void tick();

private:
    void startTone(unsigned int freq, unsigned int onMs, unsigned int offMs);
    void stop();
    void updatePwm();

    AppState currentState_ = AppState::Boot;
    bool playing_ = false;
    unsigned int freq_ = 0;
    unsigned int onMs_ = 0;
    unsigned int offMs_ = 0;
    unsigned int tickCounter_ = 0;
    bool isOnPhase_ = true;
};

} // namespace taptune
