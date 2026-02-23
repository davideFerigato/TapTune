#ifndef LED_H
#define LED_H

#include <stdbool.h>

/**
 * @brief Initialise RGB LED pins.
 */
void led_init();

/**
 * @brief Set LED colour.
 * @param r red on/off
 * @param g green on/off
 * @param b blue on/off
 */
void led_set(bool r, bool g, bool b);

/**
 * @brief Update LED based on Bluetooth state.
 * @param connected true if connected
 * @param streaming true if audio streaming
 */
void led_update_state(bool connected, bool streaming);

#endif