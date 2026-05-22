idf_component_register(
    SRCS "src/bt_manager.cpp"
    INCLUDE_DIRS "include"
    REQUIRES
        bt
        state_machine
        taptune_config
)
