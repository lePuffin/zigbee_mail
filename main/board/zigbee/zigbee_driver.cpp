/**
 * @file zigbee_driver.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "zigbee_driver.hpp"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_zigbee_core.h"
#include "ha/esp_zigbee_ha_standard.h"
#include "zcl_utility.h"

namespace zigbee_mailbox {

/** @section Defines */
static const char* TAG = "zigbee_driver";

static const char* kEspManufacturerName = "\x09lePuffin";      /* Customized manufacturer name */
static const char* kEspModelIdentifier  = "\x07ZigbeeMailbox"; /* Customized model identifier */

/** @section Functions */
// Public

ZigbeeDriver::ZigbeeDriver() {
    ESP_LOGI(TAG, "f:ZigbeeDriver::ZigbeeDriver");

    esp_zb_platform_config_t config = {
        .radio_config = {.radio_mode = ZB_RADIO_MODE_NATIVE, .radio_uart_config = {}},
        .host_config  = {.host_connection_mode = ZB_HOST_CONNECTION_MODE_NONE, .host_uart_config = {}},
    };

    ESP_ERROR_CHECK(esp_zb_platform_config(&config));
}

ZigbeeDriver::~ZigbeeDriver() {
    ESP_LOGI(TAG, "f:ZigbeeDriver::~ZigbeeDriver");
}

void ZigbeeDriver::ZigbeeTask(void* pvParameters) {
    ESP_LOGI(TAG, "f:ZigbeeDriver::ZigbeeTask");
    /* Initialize Zigbee stack */

    // clang-format off
    esp_zb_cfg_t zb_nwk_cfg = {
        .esp_zb_role         = ESP_ZB_DEVICE_TYPE_ED,
        .install_code_policy = false,
        .nwk_cfg             = {
            .zed_cfg = {
                .ed_timeout = ESP_ZB_ED_AGING_TIMEOUT_10SEC,
                .keep_alive = 10 * 1000
            }
        },
    };
    // clang-format on

    esp_zb_init(&zb_nwk_cfg);

    /* Create cluster */
    esp_zb_cluster_list_t*      cluster_list = esp_zb_zcl_cluster_list_create();
    esp_zb_on_off_cluster_cfg_t bool_cluster = {
        .on_off = false,
    };

    esp_zb_attribute_list_t* att_list = esp_zb_on_off_cluster_create(&bool_cluster);

    zcl_basic_manufacturer_info_t info = {
        .manufacturer_name = (char*) kEspManufacturerName,
        .model_identifier  = (char*) kEspModelIdentifier,
    };

    esp_zb_basic_cluster_add_attr(att_list, ESP_ZB_ZCL_ATTR_BASIC_MANUFACTURER_NAME_ID, info.manufacturer_name);
    esp_zb_basic_cluster_add_attr(att_list, ESP_ZB_ZCL_ATTR_BASIC_MODEL_IDENTIFIER_ID, info.model_identifier);

    /* Create Endpoint */
    esp_zb_ep_list_t*        ep_list         = esp_zb_ep_list_create();
    esp_zb_endpoint_config_t endpoint_config = {.endpoint           = kBasicEndpoint,
                                                .app_profile_id     = ESP_ZB_AF_HA_PROFILE_ID,
                                                .app_device_id      = ESP_ZB_HA_SIMPLE_SENSOR_DEVICE_ID,
                                                .app_device_version = 1};

    esp_zb_ep_list_add_ep(ep_list, cluster_list, endpoint_config);

    /* Register the device */
    esp_zb_device_register(ep_list);

    /* Config the reporting info  */
    esp_zb_zcl_reporting_info_t reporting_info = {
        .direction                    = ESP_ZB_ZCL_CMD_DIRECTION_TO_SRV,
        .ep                           = kBasicEndpoint,
        .cluster_id                   = ESP_ZB_ZCL_CLUSTER_ID_BASIC,
        .cluster_role                 = ESP_ZB_ZCL_CLUSTER_SERVER_ROLE,
        .attr_id                      = ESP_ZB_ZCL_ATTR_TEMP_MEASUREMENT_VALUE_ID,
        .flags                        = ESP_ZB_ZCL_ATTR_BINARY_INPUT_STATUS_FLAG_ID,
        .run_time                     = 0, /*!< Time to run next reporting activity */
        .dst.profile_id               = ESP_ZB_AF_HA_PROFILE_ID,
        .u.send_info.min_interval     = 1,
        .u.send_info.max_interval     = 0,
        .u.send_info.def_min_interval = 1,
        .u.send_info.def_max_interval = 0,
        .u.send_info.delta.u16        = 100,
        .manuf_code                   = ESP_ZB_ZCL_ATTR_NON_MANUFACTURER_SPECIFIC,
    };

    esp_zb_zcl_update_reporting_info(&reporting_info);

    esp_zb_core_action_handler_register(action_handler_.ActionHandler);
    esp_zb_set_primary_network_channel_set(ESP_ZB_TRANSCEIVER_ALL_CHANNELS_MASK);

    ESP_ERROR_CHECK(esp_zb_start(false));

    esp_zb_stack_main_loop();
}

// Private

}  // namespace zigbee_mailbox

// End of file
