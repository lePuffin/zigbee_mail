/*
** Copyright: Copyright (c) 2024 Carlos Estevao
** Author: lePuffin
** Date: 2025-03-08
** Brief: Main File
*/

/****** Includes ******/
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/****** Defines ******/

/****** Functions ******/
// Public

static const char* TAG = "main";

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Hello, ESP32-H2!");

    while (true) {
        ESP_LOGI(TAG, "Running...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Private

// End of file