#include "display_manager.hpp"
#include "pins.hpp"
#include "config.hpp"
#include <driver/i2c.h>
#include <esp_log.h>
#include <lvgl.h>

static constexpr const char* TAG = "display";

namespace taptune {

// ------------------- I2C porting per LVGL -------------------
static constexpr uint8_t SSD1306_I2C_ADDR = 0x3C;

void DisplayManager::i2cWrite(uint8_t addr, const uint8_t *data, size_t len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, const_cast<uint8_t*>(data), len, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
}

void DisplayManager::flushCb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint8_t x1 = static_cast<uint8_t>(area->x1);
    uint8_t x2 = static_cast<uint8_t>(area->x2);
    uint8_t y1 = static_cast<uint8_t>(area->y1);
    uint8_t y2 = static_cast<uint8_t>(area->y2);
    uint8_t width = x2 - x1 + 1;
    uint8_t height = y2 - y1 + 1;

    // Imposta la finestra di scrittura (per SSD1306)
    uint8_t cmdBuf[] = {
        0x00, // comando
        0x21, x1, x2, // column address
        0x22, y1, y2  // page address
    };
    i2cWrite(SSD1306_I2C_ADDR, cmdBuf, sizeof(cmdBuf));

    // Scrittura dei pixel
    // Converti i colori LVGL (RGB565) in monocromatico per SSD1306 (1 bit per pixel)
    size_t byteLen = (static_cast<size_t>(width) * height + 7) / 8;
    uint8_t *mono = new uint8_t[byteLen + 1];
    mono[0] = 0x40; // segnale di dati
    int idx = 1;
    uint8_t byte = 0;
    int bit = 7;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            lv_color_t c = color_p[y * width + x];
            // Soglia: se non nero, accendi
            if (c.full > 0x8080) {
                byte |= (1 << bit);
            }
            bit--;
            if (bit < 0) {
                mono[idx++] = byte;
                byte = 0;
                bit = 7;
            }
        }
    }
    if (bit != 7) {
        mono[idx++] = byte;
    }

    i2cWrite(SSD1306_I2C_ADDR, mono, idx);
    delete[] mono;

    lv_disp_flush_ready(disp);
}

// ------------------- Metodi pubblici -------------------
DisplayManager::DisplayManager() {
    i2cInit();
    lvglInit();
}

DisplayManager::~DisplayManager() {
    if (lvgl_initialized_) {
        lv_deinit();
    }
}

void DisplayManager::applyState(AppState state) {
    if (!lvgl_initialized_) return;
    updateLabel(state);
}

void DisplayManager::tick() {
    if (lvgl_initialized_) {
        lv_timer_handler();
    }
}

// ------------------- Inizializzazioni -------------------
void DisplayManager::i2cInit() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = static_cast<gpio_num_t>(pins::kI2cSda),
        .scl_io_num = static_cast<gpio_num_t>(pins::kI2cScl),
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master = {
            .clk_speed = static_cast<uint32_t>(config::kI2cClockHz)
        },
        .clk_flags = 0
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0));
    ESP_LOGI(TAG, "I2C initialized at %d Hz on SDA:%d SCL:%d", config::kI2cClockHz, pins::kI2cSda, pins::kI2cScl);
}

void DisplayManager::lvglInit() {
    lv_init();

    // Buffer di disegno (dimensioni ridotte per risparmiare RAM)
    static lv_color_t buf1[128 * 8]; // 1/8 di schermo? 128x64 => 1024 byte per 8 righe.
    static lv_color_t buf2[128 * 8];

    lv_disp_draw_buf_t drawBuf;
    lv_disp_draw_buf_init(&drawBuf, buf1, buf2, 128 * 8);

    // Driver del display
    static lv_disp_drv_t dispDrv;
    lv_disp_drv_init(&dispDrv);
    dispDrv.hor_res = 128;
    dispDrv.ver_res = 64;
    dispDrv.flush_cb = flushCb;
    dispDrv.draw_buf = &drawBuf;
    lv_disp_drv_register(&dispDrv);

    // Creazione schermata di default
    lv_obj_t *scr = lv_scr_act();
    label_ = lv_label_create(scr);
    lv_obj_center(label_);
    lv_label_set_text(label_, "TapTune");

    lvgl_initialized_ = true;
    ESP_LOGI(TAG, "LVGL initialized with SSD1306 128x64");
}

void DisplayManager::updateLabel(AppState state) {
    const char *text;
    switch (state) {
        case AppState::Boot: text = "Boot..."; break;
        case AppState::Idle: text = "Idle"; break;
        case AppState::Connecting: text = "Connecting..."; break;
        case AppState::Connected: text = "Connected"; break;
        case AppState::Streaming: text = "Streaming"; break;
        default: text = "?"; break;
    }
    lv_label_set_text(label_, text);
    lv_obj_center(label_);
}

} // namespace taptune
