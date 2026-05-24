#pragma once

#include "state_machine.hpp"
#include <optional>
#include <cstdint>

namespace taptune {

/**
 * @brief Manages the PN532 NFC module.
 * 
 * Configures the PN532 in target emulation mode. When an external reader
 * (e.g., a smartphone) reads the tag, an event is generated to trigger the
 * Bluetooth connection flow.
 */
class NfcManager {
public:
    /**
     * @brief Initializes the PN532 and configures it as an NFC target.
     */
    NfcManager();

    /**
     * @brief Deinitializes resources.
     */
    ~NfcManager();

    /**
     * @brief Retrieves the next event from the NFC event queue, if any.
     * @return std::optional<AppEvent> The event, or std::nullopt if queue is empty.
     */
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
