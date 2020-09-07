#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

#include <stdint.h>
#include "stm32f4xx_gpio.h"

typedef struct {
    void *clk_cmd;
    uint32_t clk;
    GPIO_TypeDef *port;
    uint16_t pin;
    uint16_t active;
} gpio_init_t;

#endif /* __DRV_GPIO_H */
