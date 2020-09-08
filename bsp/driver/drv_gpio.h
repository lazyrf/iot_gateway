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
} drv_gpio_cfg_t;

void drv_gpio_cfg_output(drv_gpio_cfg_t pin);
void drv_gpio_cfg_input(drv_gpio_cfg_t gpio);
void drv_gpio_pin_on(drv_gpio_cfg_t gpio);
void drv_gpio_pin_off(drv_gpio_cfg_t gpio);
void drv_drv_gpio_cfg_toggle(drv_gpio_cfg_t gpio);
uint8_t drv_gpio_pin_get_out_state(drv_gpio_cfg_t gpio);
uint8_t drv_gpio_pin_get_in_state(drv_gpio_cfg_t gpio);

#endif /* __DRV_GPIO_H */
