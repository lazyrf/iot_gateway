#include "board.h"
#include "drv_gpio.h"

gpio_init_t led_gpio_list[BOARD_LED_NUM] = BOARD_LED_LIST;

void board_led_init(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        drv_gpio_cfg_output(led_gpio_list[idx]);
    }
}
