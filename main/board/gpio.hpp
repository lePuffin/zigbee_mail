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

namespace zigbee_mailbox {

/** @section Defines */

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
