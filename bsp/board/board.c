#include <stdio.h>

#include "board.h"
#include "assert.h"
#include "hal_core.h"
#include "drv_led.h"
#include "drv_di.h"
#include "drv_do.h"
#include "drv_uart_dbg.h"

#if BOARD_LED_NUM > 0
hal_gpio_cfg_t led_gpio_list[BOARD_LED_NUM] = BOARD_LED_LIST;
#endif /* BOARD_LED_NUM > 0 */

#if BOARD_DO_NUM > 0
hal_gpio_cfg_t do_gpio_list[BOARD_DO_NUM] = BOARD_DO_LIST;
#endif /* BOARD_DO_NUM > 0 */

#if BOARD_DI_NUM > 0
hal_gpio_cfg_t di_gpio_list[BOARD_DI_NUM] = BOARD_DI_LIST;
#endif /* BOARD_DI_NUM > 0 */

#if BOARD_UART_NUM > 0
hal_uart_cfg_t uart_list[BOARD_UART_NUM] = BOARD_UART_LIST;
#endif /* BOARD_UART_NUM > 0 */

#if BOARD_I2C_NUM > 0
hal_i2c_cfg_t i2c_list[BOARD_I2C_NUM] = BOARD_I2C_LIST;
#endif /* BOARD_I2C_NUM > 0 */

#if BOARD_RTC_ALARM_NUM > 0
hal_rtc_alarm_t rtc_alarm_list[BOARD_RTC_ALARM_NUM] = BOARD_RTC_ALARM_LIST;
#endif /* BOARD_RTC_ALARM_NUM > 0 */

void board_init(void)
{
    hal_core_systick_init(1000);

#if BOARD_LED_NUM > 0
    drv_led_init();
#endif /* BOARD_LED_NUM > 0 */

#if BOARD_DO_NUM > 0
    drv_do_init();
#endif /* BOARD_DO_NUM > 0 */

#if BOARD_DI_NUM > 0
    drv_di_init();
#endif /* BOARD_DI_NUM > 0 */

#if BOARD_UART_NUM > 0
    drv_uart_dbg_init();
#endif /* BOARD_UART_NUM > 0 */
}
