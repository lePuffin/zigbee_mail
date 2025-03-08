set(SRCS_FILES
    "main.cpp"
    "board/gpio/gpio.cpp"
)

set(DIRS 
    "."
    "board/gpio"
)

if(NOT DEFINED __ESP_PLATFORM__)
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

