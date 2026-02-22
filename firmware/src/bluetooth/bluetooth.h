#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <functional>

// Callbacks esterne (da collegare ai moduli LED/display/buzzer)
extern void bluetooth_on_connected();
extern void bluetooth_on_disconnected();
extern void bluetooth_on_audio_started();
extern void bluetooth_on_audio_stopped();

void bluetooth_init(const char* deviceName);
void bluetooth_poll();  // se necessario

#endif