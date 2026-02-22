#ifndef LED_H
#define LED_H

#include <stdbool.h>

void led_init();
void led_set(bool r, bool g, bool b);
void led_update_state(bool connected, bool streaming);

#endif