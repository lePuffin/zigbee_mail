/**
 * @file gpio.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "gpio.hpp"

namespace zigbee_mailbox {

/** @section Defines */

/** @section Functions */
// Public

GPIO::GPIO() {
    Init();
}

GPIO::~GPIO() {
    DeInit();
}

// Private
void Init() {
}

void DeInit() {
}

}  // namespace zigbee_mailbox

// End of file
