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
    /**
     * @brief Configures the LEDC peripheral for PWM output.
     */
    TonePlayer();

    /**
     * @brief Updates the active tone pattern based on state changes.
     * @param state The new application state.
     */
    void onStateChanged(AppState state);

    /**
     * @brief Periodically updates the PWM output. Call every 20ms.
     */
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
