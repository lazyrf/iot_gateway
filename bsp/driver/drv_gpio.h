#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

#include <stdint.h>
#include "stm32f4xx_gpio.h"

typedef struct {
    void *clk_cmd;
    uint32_t clk;
    GPIO_TypeDef *port;
    uint16_t pin;
    uint16_t active_state;
} gpio_pin_t;

void drv_gpio_cfg_output(gpio_pin_t pin);
void drv_gpio_cfg_input(gpio_pin_t gpio);
void drv_gpio_pin_on(gpio_pin_t gpio);
void drv_gpio_pin_off(gpio_pin_t gpio);
void drv_gpio_pin_toggle(gpio_pin_t gpio);
uint8_t drv_gpio_pin_get_out_state(gpio_pin_t gpio);
uint8_t drv_gpio_pin_get_in_state(gpio_pin_t gpio);

#endif /* __DRV_GPIO_H */
