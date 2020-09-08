#include "drv_gpio.h"

uint8_t drv_gpio_pin_get_in_state(gpio_pin_t gpio)
{
    return GPIO_ReadInputDataBit(gpio.port, gpio.pin);
}

uint8_t drv_gpio_pin_get_out_state(gpio_pin_t gpio)
{
    return GPIO_ReadOutputDataBit(gpio.port, gpio.pin);
}

void drv_gpio_pin_toggle(gpio_pin_t gpio)
{
    gpio.port->ODR ^= gpio.pin;
}

void drv_gpio_pin_off(gpio_pin_t gpio)
{
    if (gpio.active_state) {
        gpio.port->BSRRH = gpio.pin;
    } else {
        gpio.port->BSRRL = gpio.pin;
    }
}

void drv_gpio_pin_on(gpio_pin_t gpio)
{
    if (gpio.active_state) {
        gpio.port->BSRRL = gpio.pin;
    } else {
        gpio.port->BSRRH = gpio.pin;
    }
}

void drv_gpio_cfg_input(gpio_pin_t gpio)
{
    GPIO_InitTypeDef gpio_cfg;
    void (*rcc_clk_cmd)(uint32_t, FunctionalState);

    /* Enable clock */
    rcc_clk_cmd = gpio.clk_cmd;
    rcc_clk_cmd(gpio.clk, ENABLE);

    /* GPIO init structure */
    gpio_cfg.GPIO_Pin = gpio.pin;
    gpio_cfg.GPIO_Mode = GPIO_Mode_IN;
    gpio_cfg.GPIO_PuPd = (gpio.active_state) ? GPIO_PuPd_DOWN : GPIO_PuPd_UP;
    GPIO_Init(gpio.port, &gpio_cfg);
}

void drv_gpio_cfg_output(gpio_pin_t gpio)
{
    GPIO_InitTypeDef gpio_cfg;
    void (*rcc_clk_cmd)(uint32_t, FunctionalState);

    /* Enable clock */
    rcc_clk_cmd = gpio.clk_cmd;
    rcc_clk_cmd(gpio.clk, ENABLE);

    /* GPIO init structure */
    gpio_cfg.GPIO_Pin = gpio.pin;
    gpio_cfg.GPIO_Mode = GPIO_Mode_OUT;
    gpio_cfg.GPIO_OType = GPIO_OType_PP;
    gpio_cfg.GPIO_PuPd = (gpio.active_state) ? GPIO_PuPd_DOWN : GPIO_PuPd_UP;
    gpio_cfg.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(gpio.port, &gpio_cfg);
}
