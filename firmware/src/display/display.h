#ifndef DISPLAY_H
#define DISPLAY_H

void display_init();
void display_update();  // da chiamare in loop
void display_set_power(bool on);  // per accendere/spegnere
void display_adjust_brightness(uint8_t level); // 0-255

// Eventi esterni (chiamati da bluetooth)
void display_on_connected();
void display_on_disconnected();
void display_on_audio_started();
void display_on_audio_stopped();
void display_on_boot_complete();

#endif