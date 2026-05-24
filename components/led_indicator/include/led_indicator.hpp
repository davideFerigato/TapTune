#pragma once

#include "state_machine.hpp"

namespace taptune {

/**
 * @brief Controls the RGB LED indicator.
 * 
 * Translates an AppState into a specific LED color:
 * - Boot: OFF
 * - Idle: Red
 * - Connecting: Magenta
 * - Connected: Blue
 * - Streaming: Green
 */
class LedIndicator {
public:
    LedIndicator();
    void applyState(AppState state);

private:
    void setRgb(bool r, bool g, bool b);
};

} // namespace taptune
