#ifndef CONFIG_H
#define CONFIG_H

// Audio PWM
#define AUDIO_PWM_FREQ        78000
#define AUDIO_PWM_RESOLUTION  8
#define AUDIO_PWM_CHANNEL     0

// Buffer audio
#define AUDIO_BUFFER_SIZE     8192

// Timer audio (frequenza campionamento)
#define AUDIO_TIMER_FREQ_HZ   1000000  // 1 MHz
#define AUDIO_SAMPLE_PERIOD_US 23       // ~43.5 kHz

// Display
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDR 0x3C

// Timeout display (ms)
#define DISPLAY_TIMEOUT  20000   // 20 secondi

#endif