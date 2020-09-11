#include "drv_do.h"
#include "board.h"
#include "hal_gpio.h"
#include "assert.h"

void drv_do_off(int idx)
{
    assert(idx < BOARD_DO_NUM);
    hal_gpio_pin_off(do_gpio_list[idx]);
}

void drv_do_on(int idx)
{
    assert(idx < BOARD_DO_NUM);
    hal_gpio_pin_on(do_gpio_list[idx]);
}

void drv_do_all_off(void)
{
    for (int idx = 0; idx < BOARD_DO_NUM; idx++) {
        hal_gpio_pin_off(do_gpio_list[idx]);
    }
}

void drv_do_all_on(void)
{
    for (int idx = 0; idx < BOARD_DO_NUM; idx++) {
        hal_gpio_pin_on(do_gpio_list[idx]);
    }
}

void drv_do_init(void)
{
    for (int idx = 0; idx < BOARD_DO_NUM; idx++) {
        hal_gpio_cfg_output(do_gpio_list[idx]);
    }
}
