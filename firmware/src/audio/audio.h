#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stddef.h>

void audio_init();
void audio_update();  // eventuale, se serve
void audio_play_sample(const uint8_t *data, uint32_t length);  // chiamata dalla callback BT

#endif