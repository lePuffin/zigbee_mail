/**
 * @file gpio.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "gpio.hpp"
#include "esp_log.h"

namespace zigbee_mailbox {

/** @section Defines */
static const char* TAG = "GPIO";

/** @section Functions */
// Public

GPIO::GPIO() {
    Init();
}

GPIO::~GPIO() {
    DeInit();
}

// Private

// ISR handler function
static void gpio_isr_handler(void* arg) {
    uint32_t gpio_num = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(arg));
    ESP_LOGI(TAG, "GPIO[%d] interrupt triggered", (uint16_t) gpio_num);
}

void GPIO::Init() {
    // Configure the GPIO pin as an input with an interrupt on the rising edge
    gpio_config_t io_conf = {
        .pin_bit_mask  = (1ULL << kGpioNum),
        .mode          = GPIO_MODE_INPUT,
        .pull_up_en    = GPIO_PULLUP_ENABLE,
        .pull_down_en  = GPIO_PULLDOWN_DISABLE,
        .intr_type     = GPIO_INTR_POSEDGE,
        .hys_ctrl_mode = GPIO_HYS_SOFT_DISABLE,
    };

    gpio_config(&io_conf);

    // Register the ISR handler
    gpio_isr_register(gpio_isr_handler, (void*) kGpioNum, 0, nullptr);
}

void GPIO::DeInit() {
    // Remove the ISR handler
    gpio_isr_handler_remove(kGpioNum);
}

}  // namespace zigbee_mailbox

// End of file
