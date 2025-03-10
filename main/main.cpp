/**
 * @file main.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "app/zigbee_app.hpp"
#include "board/gpio/gpio.hpp"
#include "board/zigbee/zigbee_driver.hpp"

/** @section Defines */

/** @section Functions */
// Public
static const char* TAG = "main";

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Hello, Carlos!");

    zigbee_mailbox::GPIO         gpio;
    zigbee_mailbox::ZigbeeDriver zigbee_driver;

    ESP_ERROR_CHECK(nvs_flash_init());

    xTaskCreate(zigbee_driver.ZigbeeTask, "Zigbee_main", zigbee_mailbox::kZigbeeDriverStackSize, NULL, 5, NULL);

    while (true) {
        ESP_LOGI(TAG, "Running...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Private

// End of file
