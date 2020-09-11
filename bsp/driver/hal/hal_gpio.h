#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#include <stdint.h>
#include "stm32f4xx_gpio.h"

typedef struct {
    void *clk_cmd;
    uint32_t clk;
    GPIO_TypeDef *port;
    uint16_t pin;
    uint16_t active_state;
} hal_gpio_cfg_t;

void hal_gpio_cfg_output(hal_gpio_cfg_t pin);
void hal_gpio_cfg_input(hal_gpio_cfg_t gpio);
void hal_gpio_cfg_af_pp(hal_gpio_cfg_t gpio, uint32_t af);
void hal_gpio_pin_on(hal_gpio_cfg_t gpio);
void hal_gpio_pin_off(hal_gpio_cfg_t gpio);
void hal_gpio_pin_toggle(hal_gpio_cfg_t gpio);
uint8_t hal_gpio_pin_get_out_state(hal_gpio_cfg_t gpio);
uint8_t hal_gpio_pin_get_in_state(hal_gpio_cfg_t gpio);

#endif /* __HAL_GPIO_H */
