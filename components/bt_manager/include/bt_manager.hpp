#pragma once

#include "state_machine.hpp"
#include <esp_a2dp_api.h>
#include <optional>

namespace taptune {

/**
 * @brief Manages the Bluetooth A2DP sink.
 * 
 * Handles the initialization of the Bluetooth stack, makes the device
 * discoverable, accepts connections, and raises events through a queue
 * to signal connection, disconnection and streaming state changes.
 */
class BtManager {
public:
    /**
     * @brief Initializes the Bluetooth controller and A2DP sink.
     */
    BtManager();

    /**
     * @brief Cleans up Bluetooth resources.
     */
    ~BtManager();

    /**
     * @brief Makes the device discoverable and ready to accept connections.
     */
    void start();

    /**
     * @brief Disconnects and stops advertising.
     */
    void stop();

    /**
     * @brief Retrieves the next event from the Bluetooth event queue, if any.
     * @return std::optional<AppEvent> The event, or std::nullopt if queue is empty.
     */
    std::optional<AppEvent> pollEvent();

private:
    static void a2dCallback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);
    void handleA2dEvent(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);
    void pushEvent(AppEvent ev);

    void *eventQueue_;
    bool started_ = false;
    static BtManager* instance_;
};

} // namespace taptune
