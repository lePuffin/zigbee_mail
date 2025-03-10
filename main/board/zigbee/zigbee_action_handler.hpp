/**
 * @file zigbee_action_handler.hpp
 * @brief Implementation of Zigbee action handler
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

#ifndef _zigbee_action_handler_hpp_
#define _zigbee_action_handler_hpp_

/** @section Includes */
#include "esp_err.h"
#include "esp_zigbee_core.h"

namespace zigbee_mailbox {

/** @section Defines */
static const uint8_t kBasicEndpoint = 1;

/** @section Functions */
// Public
class ZigbeeActionHandler {
  private:
  public:
    ZigbeeActionHandler();
    ~ZigbeeActionHandler();

    static esp_err_t ActionHandler(esp_zb_core_action_callback_id_t callback_id, const void* message);

    static esp_err_t AttributeHandler(const esp_zb_zcl_set_attr_value_message_t* message);
};

// Private

}  // namespace zigbee_mailbox

#endif  // _zigbee_action_handler_hpp_

// End of file
