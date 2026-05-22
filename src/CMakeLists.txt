idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES
        esp_system
        nvs_flash
        bt
        state_machine
        led_indicator
        tone_player
        display_manager
        bt_manager
        taptune_config
)
