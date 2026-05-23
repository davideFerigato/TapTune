#pragma once

#include "state_machine.hpp"
#include <optional>
#include <cstdint>

namespace taptune {

class NfcManager {
public:
    NfcManager();
    ~NfcManager();

    std::optional<AppEvent> pollEvent();

private:
    void init();
    void handleTargetDetected();

    void writeCommand(const uint8_t *cmd, size_t len);
    void readResponse(uint8_t *buf, size_t len);

    void* eventQueue_;
    bool initialized_ = false;
    static NfcManager* instance_;
    static void s_targetTask(void* arg);
};

} // namespace taptune
