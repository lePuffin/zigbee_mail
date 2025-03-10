/**
 * @file zigbee_action_handler.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "zigbee_action_handler.hpp"
#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"

namespace zigbee_mailbox {

/** @section Defines */
static const char* TAG = "zigbee_action_handler";

/** @section Functions */
// Public
ZigbeeActionHandler::ZigbeeActionHandler() {
}

ZigbeeActionHandler::~ZigbeeActionHandler() {
}

esp_err_t ZigbeeActionHandler::ActionHandler(esp_zb_core_action_callback_id_t callback_id,
                                             const void*                      message) {
    esp_err_t ret = ESP_OK;
    switch (callback_id) {
        case ESP_ZB_CORE_SET_ATTR_VALUE_CB_ID:
            ret = AttributeHandler((esp_zb_zcl_set_attr_value_message_t*) message);
            break;
        default:
            ESP_LOGW(TAG, "Receive Zigbee action(0x%x) callback", callback_id);
            break;
    }
    return ret;
}

esp_err_t ZigbeeActionHandler::AttributeHandler(
    const esp_zb_zcl_set_attr_value_message_t* message) {
    esp_err_t ret         = ESP_OK;
    bool      light_state = 0;

    ESP_RETURN_ON_FALSE(message, ESP_FAIL, TAG, "Empty message");
    ESP_RETURN_ON_FALSE(message->info.status == ESP_ZB_ZCL_STATUS_SUCCESS, ESP_ERR_INVALID_ARG, TAG,
                        "Received message: error status(%d)", message->info.status);
    ESP_LOGI(TAG, "Received message: endpoint(%d), cluster(0x%x), attribute(0x%x), data size(%d)",
             message->info.dst_endpoint, message->info.cluster, message->attribute.id,
             message->attribute.data.size);
    if (message->info.dst_endpoint == kHaEspSwitchEndpoint) {
        if (message->info.cluster == ESP_ZB_ZCL_CLUSTER_ID_ON_OFF) {
            if (message->attribute.id == ESP_ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID &&
                message->attribute.data.type == ESP_ZB_ZCL_ATTR_TYPE_BOOL) {
                light_state = message->attribute.data.value ? *(bool*) message->attribute.data.value
                                                            : light_state;
                ESP_LOGI(TAG, "Light sets to %s", light_state ? "On" : "Off");
                // light_driver_set_power(light_state);
            }
        }
    }
    return ret;
}

// Private

}  // namespace zigbee_mailbox

// End of file
