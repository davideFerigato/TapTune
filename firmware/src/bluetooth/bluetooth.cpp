#include "bluetooth.h"
#include "audio.h"
#include "BluetoothA2DPSink.h"

static BluetoothA2DPSink a2dp_sink;

void read_data_stream(const uint8_t *data, uint32_t length) {
    audio_play_sample(data, length);
}

void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
    if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
        bluetooth_on_connected();
    } else {
        bluetooth_on_disconnected();
    }
}

void audio_state_changed(esp_a2d_audio_state_t state, void *ptr) {
    if (state == ESP_A2D_AUDIO_STATE_STARTED) {
        bluetooth_on_audio_started();
    } else {
        bluetooth_on_audio_stopped();
    }
}

void bluetooth_init(const char* deviceName) {
    a2dp_sink.set_stream_reader(read_data_stream, false);
    a2dp_sink.set_on_connection_state_changed(connection_state_changed);
    a2dp_sink.set_on_audio_state_changed(audio_state_changed);
    a2dp_sink.start(deviceName);
}