idf_component_register(
    SRCS "src/display_manager.cpp"
    INCLUDE_DIRS "include"
    REQUIRES
        driver
        esp_driver_i2c
        state_machine
        taptune_config
        lvgl
)
