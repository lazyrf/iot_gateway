#include <stdio.h>

#include "board.h"
#include "assert.h"
#include "drv_core.h"

#if BOARD_LED_NUM > 0
drv_gpio_cfg_t led_gpio_list[BOARD_LED_NUM] = BOARD_LED_LIST;

void board_led_toggle(int idx)
{
    assert(idx < BOARD_LED_NUM);
    drv_gpio_pin_toggle(led_gpio_list[idx]);
}

void board_led_off(int idx)
{
    assert(idx < BOARD_LED_NUM);
    drv_gpio_pin_off(led_gpio_list[idx]);
}

void board_led_on(int idx)
{
    assert(idx < BOARD_LED_NUM);
    drv_gpio_pin_on(led_gpio_list[idx]);
}

void board_leds_toggle(void)
{
    for (int idx = 0; idx < BOARD_LED_NUM; idx++) {
        drv_gpio_pin_toggle(led_gpio_list[idx]);
    }
}

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
#endif /* BOARD_LED_NUM > 0 */

#if BOARD_DO_NUM > 0
drv_gpio_cfg_t do_gpio_list[BOARD_DO_NUM] = BOARD_DO_LIST;


void board_do_off(int idx)
{
    assert(idx < BOARD_DO_NUM);
    drv_gpio_pin_off(do_gpio_list[idx]);
}

void board_do_on(int idx)
{
    assert(idx < BOARD_DO_NUM);
    drv_gpio_pin_on(do_gpio_list[idx]);
}

void board_dos_off(void)
{
    for (int idx = 0; idx < BOARD_DO_NUM; idx++) {
        drv_gpio_pin_off(do_gpio_list[idx]);
    }
}

void board_dos_on(void)
{
    for (int idx = 0; idx < BOARD_DO_NUM; idx++) {
        drv_gpio_pin_on(do_gpio_list[idx]);
    }
}

void board_dos_init(void)
{
    for (int idx = 0; idx < BOARD_DO_NUM; idx++) {
        drv_gpio_cfg_output(do_gpio_list[idx]);
    }
}
#endif /* BOARD_DO_NUM > 0 */

#if BOARD_DI_NUM > 0
drv_gpio_cfg_t di_gpio_list[BOARD_DI_NUM] = BOARD_DI_LIST;

uint8_t board_di_status(int idx)
{
    assert(idx < BOARD_DI_NUM);
    return drv_gpio_pin_get_in_state(di_gpio_list[idx]);
}

void board_dis_init(void)
{
    for (int idx = 0; idx < BOARD_DI_NUM; idx++) {
        drv_gpio_cfg_input(di_gpio_list[idx]);
    }
}
#endif /* BOARD_DI_NUM > 0 */

#if BOARD_UART_NUM > 0
drv_uart_cfg_t uart_list[BOARD_UART_NUM] = BOARD_UART_LIST;

int __io_putchar(int ch)
{
    drv_uart_send_byte(uart_list[0], ch);
    return (ch);
}

void board_uarts_init(void)
{
    for (int idx = 0; idx < BOARD_UART_NUM; idx++) {
        drv_uart_init(uart_list[idx]);
    }
}

#endif /* BOARD_UART_NUM > 0 */

void board_init(void)
{
    drv_core_systick_init();

#if BOARD_LED_NUM > 0
    board_leds_init();
#endif /* BOARD_LED_NUM > 0 */

#if BOARD_DO_NUM > 0
    board_dos_init();
#endif /* BOARD_DO_NUM > 0 */

#if BOARD_DI_NUM > 0
    board_dis_init();
#endif /* BOARD_DI_NUM > 0 */

#if BOARD_UART_NUM > 0
    board_uarts_init();
#endif /* BOARD_UART_NUM > 0 */
}
