/**
 * @file zigbee_driver.hpp
 * @brief Implementation of Zigbee task
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

#ifndef _zigbee_driver_hpp_
#define _zigbee_driver_hpp_

/** @section Includes */
#include <cstdint>
#include "zigbee_action_handler.hpp"

namespace zigbee_mailbox {

/** @section Defines */
static const uint32_t kZigbeeDriverStackSize = 4096;

/** @section Functions */
// Public
class ZigbeeDriver {
  private:
    static ZigbeeActionHandler action_handler_;

  public:
    ZigbeeDriver();
    ~ZigbeeDriver();

    static void ZigbeeTask(void* pvParameters);
};

// Private

}  // namespace zigbee_mailbox

#endif  // _zigbee_driver_hpp_

// End of file
