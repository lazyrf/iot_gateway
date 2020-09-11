#include "drv_di.h"
#include "board.h"
#include "hal_gpio.h"
#include "assert.h"

uint8_t drv_di_status(int idx)
{
    assert(idx < BOARD_DI_NUM);
    return hal_gpio_pin_get_in_state(di_gpio_list[idx]);
}

void drv_di_init(void)
{
    for (int idx = 0; idx < BOARD_DI_NUM; idx++) {
        hal_gpio_cfg_input(di_gpio_list[idx]);
    }
}
