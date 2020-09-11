#include "drv_led.h"
#include "board.h"
#include "hal_gpio.h"
#include "assert.h"

void drv_led_toggle(int idx)
{
    assert(idx < BOARD_LED_NUM);
    hal_gpio_pin_toggle(led_gpio_list[idx]);
}

void drv_led_off(int idx)
{
    assert(idx < BOARD_LED_NUM);
    hal_gpio_pin_off(led_gpio_list[idx]);
}

void drv_led_on(int idx)
{
    assert(idx < BOARD_LED_NUM);
    hal_gpio_pin_on(led_gpio_list[idx]);
}

void drv_led_all_toggle(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        hal_gpio_pin_toggle(led_gpio_list[idx]);
    }
}

void drv_led_all_off(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        hal_gpio_pin_off(led_gpio_list[idx]);
    }
}

void drv_led_all_on(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        hal_gpio_pin_on(led_gpio_list[idx]);
    }
}

void drv_led_init(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        hal_gpio_cfg_output(led_gpio_list[idx]);
    }
}
