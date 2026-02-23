#include "display.h"
#include "config.h"
#include "pins.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Animation state
enum DisplayState {
    DISP_BOOT,
    DISP_IDLE,
    DISP_CONNECTED,
    DISP_STREAMING,
    DISP_DISCONNECTING
} state = DISP_BOOT;

static unsigned long bootStartTime = 0;
static float animPhase = 0.0;
static float shrinkRadius = 20.0;
static float rotAngle = 0.0;
static bool displayPower = true;
static unsigned long lastActivityTime = 0;

// Forward declarations of drawing functions
static void drawBoot() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 24);
    display.println(F("TapTune"));
    display.display();
}

static void drawIdle() {
    display.clearDisplay();
    int cx = SCREEN_WIDTH / 2;
    int cy = SCREEN_HEIGHT / 2;
    float radius = 15 + 5 * sin(animPhase);
    display.drawCircle(cx, cy, (int)radius, SSD1306_WHITE);
    display.display();
    animPhase += 0.1;
}

static void drawConnected() {
    display.clearDisplay();
    int cx = SCREEN_WIDTH / 2;
    int cy = SCREEN_HEIGHT / 2;
    int r = 18;
    display.drawCircle(cx, cy, r, SSD1306_WHITE);
    display.drawCircle(cx, cy, r-2, SSD1306_WHITE);  // thick border
    int x = cx + (r-1) * cos(rotAngle);
    int y = cy + (r-1) * sin(rotAngle);
    display.drawPixel(x, y, SSD1306_WHITE);
    display.display();
    rotAngle += 0.05;
}

static void drawStreaming() {
    display.clearDisplay();
    int cx = SCREEN_WIDTH / 2;
    int cy = SCREEN_HEIGHT / 2;
    float radius = 35 + 15 * sin(animPhase);  // expands beyond screen
    display.drawCircle(cx, cy, (int)radius, SSD1306_WHITE);
    display.display();
    animPhase += 0.1;
}

static void drawDisconnecting() {
    display.clearDisplay();
    int cx = SCREEN_WIDTH / 2;
    int cy = SCREEN_HEIGHT / 2;
    display.drawCircle(cx, cy, (int)shrinkRadius, SSD1306_WHITE);
    display.display();
    shrinkRadius -= 0.5;
}

// Public functions
void display_init() {
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println(F("OLED not found"));
        return;
    }
    display.clearDisplay();
    display.display();
    bootStartTime = millis();
    state = DISP_BOOT;
    displayPower = true;
    lastActivityTime = millis();
}

void display_update() {
    if (!displayPower) return;

    switch (state) {
        case DISP_BOOT:
            drawBoot();
            if (millis() - bootStartTime > 3000) {
                state = DISP_IDLE;
                animPhase = 0;
                lastActivityTime = millis();
            }
            break;
        case DISP_IDLE:
            drawIdle();
            break;
        case DISP_CONNECTED:
            drawConnected();
            break;
        case DISP_STREAMING:
            drawStreaming();
            break;
        case DISP_DISCONNECTING:
            drawDisconnecting();
            if (shrinkRadius <= 0) {
                shrinkRadius = 20;
                state = DISP_IDLE;
                animPhase = 0;
                lastActivityTime = millis();
            }
            break;
    }

    // Auto power-off after timeout when disconnected
    if (state == DISP_IDLE && (millis() - lastActivityTime > DISPLAY_TIMEOUT)) {
        display_set_power(false);
    }
}

void display_set_power(bool on) {
    if (on) {
        displayPower = true;
        display.ssd1306_command(SSD1306_DISPLAYON);
        lastActivityTime = millis();
    } else {
        displayPower = false;
        display.ssd1306_command(SSD1306_DISPLAYOFF);
    }
}

void display_adjust_brightness(uint8_t level) {
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(level);
}

void display_on_connected() {
    state = DISP_CONNECTED;
    rotAngle = 0;
    display_set_power(true);
}

void display_on_disconnected() {
    state = DISP_DISCONNECTING;
    shrinkRadius = 20;
    // display remains on until timeout
}

void display_on_audio_started() {
    if (state == DISP_CONNECTED) {
        state = DISP_STREAMING;
        animPhase = 0;
    }
}

void display_on_audio_stopped() {
    if (state == DISP_STREAMING) {
        state = DISP_CONNECTED;
        rotAngle = 0;
    }
}