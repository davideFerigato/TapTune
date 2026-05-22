idf_component_register(
    SRCS "src/tone_player.cpp"
    INCLUDE_DIRS "include"
    REQUIRES
        esp_driver_ledc
        state_machine
        taptune_config
)
