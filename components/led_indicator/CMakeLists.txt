idf_component_register(
    SRCS "src/led_indicator.cpp"
    INCLUDE_DIRS "include"
    REQUIRES
        esp_driver_gpio
        state_machine
        taptune_config
)
