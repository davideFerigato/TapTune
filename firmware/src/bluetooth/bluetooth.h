#ifndef BLUETOOTH_H
#define BLUETOOTH_H

/**
 * @brief Callbacks that must be implemented by the main sketch.
 */
extern void bluetooth_on_connected();
extern void bluetooth_on_disconnected();
extern void bluetooth_on_audio_started();
extern void bluetooth_on_audio_stopped();

/**
 * @brief Initialise the A2DP Bluetooth sink.
 * @param deviceName  Name to advertise.
 */
void bluetooth_init(const char* deviceName);

#endif