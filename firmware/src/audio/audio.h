#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Initialise the audio subsystem (PWM and timer).
 */
void audio_init();

/**
 * @brief Feed a chunk of audio samples to the internal buffer.
 * 
 * @param data  Pointer to 16-bit PCM samples (little-endian).
 * @param length Number of bytes.
 */
void audio_play_sample(const uint8_t *data, uint32_t length);

#endif