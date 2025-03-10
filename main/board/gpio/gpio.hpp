/**
 * @file gpio.hpp
 * @brief Brief description of the file
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

#ifndef _gpio_hpp_
#define _gpio_hpp_

/** @section Includes */

#ifdef __ESP_LINUX__
#include "../../../host/mocks/driver/mock_gpio.h"
#else
#include "driver/gpio.h"
#endif

namespace zigbee_mailbox {

/** @section Defines */
static const gpio_num_t kGpioNum = GPIO_NUM_0;

/** @section Functions */
// Public

class GPIO {
  private:
    void Init();
    void DeInit();

  public:
    GPIO();
    ~GPIO();
};

// Private

}  // namespace zigbee_mailbox

#endif  // _gpio_hpp_

// End of file
