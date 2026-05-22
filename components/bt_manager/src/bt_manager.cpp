#include "bt_manager.hpp"
#include "config.hpp"
#include <esp_a2dp_api.h>
#include <esp_bt.h>
#include <esp_bt_main.h>
#include <esp_gap_bt_api.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

static constexpr const char* TAG = "bt";

namespace taptune {

BtManager* BtManager::instance_ = nullptr;

BtManager::BtManager() {
    instance_ = this;
    eventQueue_ = xQueueCreate(8, sizeof(AppEvent));
    if (!eventQueue_) {
        ESP_LOGE(TAG, "Failed to create event queue");
        return;
    }

    esp_bt_controller_config_t btCfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if (esp_bt_controller_init(&btCfg) != ESP_OK) {
        ESP_LOGE(TAG, "BT controller init failed");
        return;
    }
    if (esp_bt_controller_enable(ESP_BT_MODE_BTDM) != ESP_OK) {
        ESP_LOGE(TAG, "BT controller enable failed");
        return;
    }
    if (esp_bluedroid_init() != ESP_OK) {
        ESP_LOGE(TAG, "Bluedroid init failed");
        return;
    }
    if (esp_bluedroid_enable() != ESP_OK) {
        ESP_LOGE(TAG, "Bluedroid enable failed");
        return;
    }

    // Registra callback A2DP
    esp_a2d_register_callback(a2dCallback);
    esp_a2d_sink_register_data_callback(nullptr);
    esp_a2d_sink_init();

    ESP_LOGI(TAG, "BtManager initialized");
}

BtManager::~BtManager() {
    if (started_) stop();
    if (eventQueue_) {
        vQueueDelete(static_cast<QueueHandle_t>(eventQueue_));
    }
    esp_a2d_sink_deinit();
    esp_bluedroid_disable();
    esp_bluedroid_deinit();
    esp_bt_controller_disable();
    esp_bt_controller_deinit();
}

void BtManager::start() {
    if (started_) return;
    started_ = true;

    // Imposta il nome del dispositivo
    esp_bt_gap_set_device_name(config::kDeviceName);

    // Rendi il dispositivo discoverable e connettibile
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

    ESP_LOGI(TAG, "A2DP sink started, discoverable as '%s'", config::kDeviceName);
}

void BtManager::stop() {
    if (!started_) return;
    // Disconnetti eventuali connessioni A2DP
    esp_a2d_sink_disconnect(0);
    // Imposta non discoverable
    esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);
    started_ = false;
    ESP_LOGI(TAG, "A2DP sink stopped");
}

std::optional<AppEvent> BtManager::pollEvent() {
    AppEvent ev;
    if (eventQueue_ && xQueueReceive(static_cast<QueueHandle_t>(eventQueue_), &ev, 0)) {
        return ev;
    }
    return std::nullopt;
}

void BtManager::a2dCallback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param) {
    if (instance_) instance_->handleA2dEvent(event, param);
}

void BtManager::handleA2dEvent(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param) {
    switch (event) {
        case ESP_A2D_CONNECTION_STATE_EVT:
            if (param->conn_stat.state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
                pushEvent(AppEvent::BluetoothConnected);
                ESP_LOGI(TAG, "Connected");
            } else if (param->conn_stat.state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
                pushEvent(AppEvent::BluetoothDisconnected);
                ESP_LOGI(TAG, "Disconnected");
            }
            break;
        case ESP_A2D_AUDIO_STATE_EVT:
            if (param->audio_stat.state == ESP_A2D_AUDIO_STATE_STARTED) {
                pushEvent(AppEvent::StreamingStarted);
                ESP_LOGI(TAG, "Streaming started");
            } else if (param->audio_stat.state == ESP_A2D_AUDIO_STATE_SUSPEND) {
                pushEvent(AppEvent::StreamingStopped);
                ESP_LOGI(TAG, "Streaming stopped/suspended");
            }
            break;
        default:
            break;
    }
}

void BtManager::pushEvent(AppEvent ev) {
    if (eventQueue_) {
        xQueueSend(static_cast<QueueHandle_t>(eventQueue_), &ev, 0);
    }
}

} // namespace taptune
