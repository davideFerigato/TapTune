#include "display.h"
#include "config.h"
#include "pins.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
static unsigned long bootStartTime = 0;
static float animPhase = 0.0, shrinkRadius = 20.0, rotAngle = 0.0;
static enum { BOOT, IDLE, CONNECTED, STREAMING, DISCONNECTING } state = BOOT;
static bool displayPower = true;

// forward declarations delle funzioni di disegno (le stesse che avevi)
static void drawBoot() { ... }
static void drawIdle() { ... }
static void drawConnected() { ... }
static void drawStreaming() { ... }
static void drawDisconnecting() { ... }

void display_init() {
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println("OLED not found");
        return;
    }
    display.clearDisplay();
    display.display();
    bootStartTime = millis();
    state = BOOT;
    displayPower = true;
}

void display_update() {
    if (!displayPower) return;
    switch (state) {
        case BOOT:
            drawBoot();
            if (millis() - bootStartTime > 3000) {
                state = IDLE;
                animPhase = 0;
            }
            break;
        case IDLE:
            drawIdle();
            break;
        case CONNECTED:
            drawConnected();
            break;
        case STREAMING:
            drawStreaming();
            break;
        case DISCONNECTING:
            drawDisconnecting();
            if (shrinkRadius <= 0) {
                shrinkRadius = 20;
                state = IDLE;
                animPhase = 0;
            }
            break;
    }
    delay(30); // frame rate
}

void display_set_power(bool on) {
    if (on) {
        displayPower = true;
        display.ssd1306_command(SSD1306_DISPLAYON);
    } else {
        displayPower = false;
        display.ssd1306_command(SSD1306_DISPLAYOFF);
    }
}

void display_adjust_brightness(uint8_t level) {
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(level);
}

// eventi
void display_on_connected() {
    state = CONNECTED;
    rotAngle = 0;
}

void display_on_disconnected() {
    state = DISCONNECTING;
    shrinkRadius = 20;
}

void display_on_audio_started() {
    if (state == CONNECTED) {
        state = STREAMING;
        animPhase = 0;
    }
}

void display_on_audio_stopped() {
    if (state == STREAMING) {
        state = CONNECTED;
        rotAngle = 0;
    }
}

void display_on_boot_complete() {
    // non serve, gestito internamente
}