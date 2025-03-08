/**
 * @file mock_gpio.cpp
 *
 * @copyright Copyright (c) 2024 Carlos Estevao
 * @author lePuffin
 * @date 2025-03-08
 */

/** @section Includes */
#include "mock_gpio.h"
#include <stdio.h>

/** @section Defines */
static gpio_config_t saved_config;
static void (*isr_callback)(void*) = NULL;
static void* isr_arg               = NULL;

/** @section Functions */
// Public

void gpio_config(const gpio_config_t* pGPIOConfig) {
    printf("Mock gpio_config called\n");
    saved_config = *pGPIOConfig;
}

void gpio_isr_register(void (*fn)(void*), void* arg, int intr_alloc_flags, void** handle) {
    printf("Mock gpio_isr_register called\n");
    isr_callback = fn;
    isr_arg      = arg;
}

void gpio_isr_handler_remove(gpio_num_t gpio_num) {
    printf("Mock gpio_isr_handler_remove called\n");
    isr_callback = NULL;
    isr_arg      = NULL;
}

void gpio_set_level(gpio_num_t gpio_num, uint32_t level) {
    printf("Mock gpio_set_level called\n");
    if (isr_callback && (saved_config.pin_bit_mask & (1ULL << gpio_num))) {
        isr_callback(isr_arg);
    }
}

// Private

// End of file
