/**
 * @file main.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "board/gpio.hpp"

/** @section Defines */

/** @section Functions */
// Public
static const char* TAG = "main";

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Hello, Carlos!");

    zigbee_mailbox::GPIO gpio;

    while (true) {
        ESP_LOGI(TAG, "Running...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Private

// End of file
