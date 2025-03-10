set(SRCS_FILES
    "main.cpp"
    "board/gpio/gpio.cpp"
    "board/zigbee/zigbee_driver.cpp"
    "board/zigbee/zigbee_action_handler.cpp"
    "board/zigbee/zcl_utility.c"
    "app/zigbee_app.cpp"
)

set(DIRS 
    "."
    "board/gpio"
    "board/zigbee"
    "app"
)

if(DEFINED __ESP_LINUX__)
    list(APPEND SRCS_FILES 
        "../host/mocks/driver/mock_gpio.c"
    )

    list(APPEND DIRS 
        "../host/mocks/driver/"
    )
endif()


idf_component_register(
    SRCS 
        ${SRCS_FILES}
    INCLUDE_DIRS 
        ${DIRS}
    REQUIRES
)

