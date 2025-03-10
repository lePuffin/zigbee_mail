/**
 * @file zigbee_app.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "zigbee_app.hpp"
#include "esp_log.h"

namespace zigbee_mailbox {

/** @section Defines */
static const char* TAG = "zigbee_app";

/** @section Functions */
// Public

ZigbeeApp::ZigbeeApp() {
    ESP_LOGI(TAG, "f:ZigbeeApp::ZigbeeApp");
}

ZigbeeApp::~ZigbeeApp() {
    ESP_LOGI(TAG, "f:ZigbeeApp::~ZigbeeApp");
}

// Private

}  // namespace zigbee_mailbox

// End of file
