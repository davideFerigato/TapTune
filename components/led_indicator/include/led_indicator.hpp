#pragma once

#include "state_machine.hpp"

namespace taptune {

class LedIndicator {
public:
    LedIndicator();
    void applyState(AppState state);

private:
    void setRgb(bool r, bool g, bool b);
};

} // namespace taptune
