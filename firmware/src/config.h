#ifndef CONFIG_H
#define CONFIG_H

// Audio PWM
#define AUDIO_PWM_FREQ       78000
#define AUDIO_PWM_RESOLUTION 8
#define AUDIO_PWM_CHANNEL    0

// Audio buffer size (samples)
#define AUDIO_BUFFER_SIZE     8192

// Timer frequency for audio playback (1 MHz)
#define AUDIO_TIMER_FREQ_HZ   1000000
// Sample period in microseconds (~43.5 kHz)
#define AUDIO_SAMPLE_PERIOD_US 23

// OLED display dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDR 0x3C

// Display timeout (ms) – display turns off after this time when disconnected
#define DISPLAY_TIMEOUT  20000   // 20 seconds

// Debounce delay for button (ms)
#define BUTTON_DEBOUNCE  50

#endif