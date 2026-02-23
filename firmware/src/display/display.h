#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

/**
 * @brief Initialise the OLED display.
 */
void display_init();

/**
 * @brief Update the display animation (call in loop).
 */
void display_update();

/**
 * @brief Turn display on/off.
 * @param on true = on, false = off
 */
void display_set_power(bool on);

/**
 * @brief Adjust display brightness.
 * @param level 0 (dark) ... 255 (brightest)
 */
void display_adjust_brightness(uint8_t level);

// Event handlers (called from bluetooth module)
void display_on_connected();
void display_on_disconnected();
void display_on_audio_started();
void display_on_audio_stopped();

#endif