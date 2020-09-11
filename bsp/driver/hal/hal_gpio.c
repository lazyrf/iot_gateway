#include "hal_gpio.h"

uint8_t hal_gpio_pin_get_in_state(hal_gpio_cfg_t gpio)
{
    return GPIO_ReadInputDataBit(gpio.port, gpio.pin);
}

uint8_t hal_gpio_pin_get_out_state(hal_gpio_cfg_t gpio)
{
    return GPIO_ReadOutputDataBit(gpio.port, gpio.pin);
}

void hal_gpio_pin_toggle(hal_gpio_cfg_t gpio)
{
    gpio.port->ODR ^= gpio.pin;
}

void hal_gpio_pin_off(hal_gpio_cfg_t gpio)
{
    if (gpio.active_state) {
        gpio.port->BSRRH = gpio.pin;
    } else {
        gpio.port->BSRRL = gpio.pin;
    }
}

void hal_gpio_pin_on(hal_gpio_cfg_t gpio)
{
    if (gpio.active_state) {
        gpio.port->BSRRL = gpio.pin;
    } else {
        gpio.port->BSRRH = gpio.pin;
    }
}

void hal_gpio_cfg_input(hal_gpio_cfg_t gpio)
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

void hal_gpio_cfg_output(hal_gpio_cfg_t gpio)
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

void hal_gpio_cfg_af_pp(hal_gpio_cfg_t gpio, uint32_t af)
{
    GPIO_InitTypeDef gpio_cfg;
    void (*rcc_clk_cmd)(uint32_t, FunctionalState);

    /* Enable clock */
    rcc_clk_cmd = gpio.clk_cmd;
    rcc_clk_cmd(gpio.clk, ENABLE);

    /* GPIO init structure */
    gpio_cfg.GPIO_Pin = gpio.pin;
    gpio_cfg.GPIO_Mode = GPIO_Mode_AF;
    gpio_cfg.GPIO_OType = GPIO_OType_PP;
    gpio_cfg.GPIO_PuPd = (gpio.active_state) ? GPIO_PuPd_DOWN : GPIO_PuPd_UP;
    gpio_cfg.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(gpio.port, &gpio_cfg);

    GPIO_PinAFConfig(gpio.port, (31 - __builtin_clz(gpio.pin)), af);
}

void hal_gpio_cfg_af_od(hal_gpio_cfg_t gpio, uint32_t af)
{
    GPIO_InitTypeDef gpio_cfg;
    void (*rcc_clk_cmd)(uint32_t, FunctionalState);

    /* Enable clock */
    rcc_clk_cmd = gpio.clk_cmd;
    rcc_clk_cmd(gpio.clk, ENABLE);

    /* GPIO init structure */
    gpio_cfg.GPIO_Pin = gpio.pin;
    gpio_cfg.GPIO_Mode = GPIO_Mode_AF;
    gpio_cfg.GPIO_OType = GPIO_OType_OD;
    gpio_cfg.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(gpio.port, &gpio_cfg);

    GPIO_PinAFConfig(gpio.port, (31 - __builtin_clz(gpio.pin)), af);
}
