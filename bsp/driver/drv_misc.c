#include "drv_misc.h"
#include "board.h"
#include "hal_iwdg.h"
#include "hal_core.h"

#if BOARD_WATCHDOG_ENABLE
void drv_misc_iwdg_feed(void)
{
    hal_iwdg_feed();
}
#endif /* BOARD_WATCHDOG_ENABLE */

void drv_misc_init(void)
{
    hal_core_nvic_init();

#if !CONFIG_RTOS_FREERTOS
    hal_core_systick_init(1000);
#endif /* !CONFIG_RTOS_FREERTOS */

#if BOARD_WATCHDOG_ENABLE
    hal_iwdg_init();
#endif /* BOARD_WATCHDOG_ENABLE */
}
