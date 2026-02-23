#ifndef BUZZER_H
#define BUZZER_H

/**
 * @brief Initialise buzzer pin.
 */
void buzzer_init();

/**
 * @brief Play startup jingle.
 */
void buzzer_play_startup();

/**
 * @brief Play connection confirmation sound.
 */
void buzzer_play_connect();

/**
 * @brief Play disconnection sound.
 */
void buzzer_play_disconnect();

#endif