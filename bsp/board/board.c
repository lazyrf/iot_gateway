#include "board.h"
#include "drv_gpio.h"

gpio_pin_t led_gpio_list[BOARD_LED_NUM] = BOARD_LED_LIST;

void board_leds_off(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        drv_gpio_pin_off(led_gpio_list[idx]);
    }
}

void board_leds_on(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        drv_gpio_pin_on(led_gpio_list[idx]);
    }
}

void board_leds_init(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        drv_gpio_cfg_output(led_gpio_list[idx]);
    }
}
