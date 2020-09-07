#include "drv_gpio.h"

void drv_gpio_cfg_output(gpio_init_t gpio_init)
{
    GPIO_InitTypeDef gpio;
    void (*rcc_clk_cmd)(uint32_t, FunctionalState);

    /* Enable clock */
    rcc_clk_cmd = gpio_init.clk_cmd;
    rcc_clk_cmd(gpio_init.clk, ENABLE);

    /* GPIO init structure */
    gpio.GPIO_Pin = gpio_init.pin;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = (gpio_init.active) ? GPIO_PuPd_DOWN : GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(gpio_init.port, &gpio);
}
