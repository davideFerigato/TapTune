#pragma once

#include "state_machine.hpp"
#include <esp_a2dp_api.h>
#include <optional>

namespace taptune {

class BtManager {
public:
    BtManager();
    ~BtManager();

    void start();
    void stop();

    /// Chiamata periodica (es. nel main loop) per estrarre gli eventi A2DP
    std::optional<AppEvent> pollEvent();

private:
    static void a2dCallback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);
    void handleA2dEvent(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);
    void pushEvent(AppEvent ev);

    void *eventQueue_;   // QueueHandle_t
    bool started_ = false;
    static BtManager* instance_;   // per callback C
};

} // namespace taptune
