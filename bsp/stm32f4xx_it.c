#include <stdio.h>

#include "config.h"

#if CONFIG_RTOS_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif /* CONFIG_RTOS_FREERTOS */

#include "delay.h"

void SysTick_Handler(void)
{
#if CONFIG_RTOS_FREERTOS
extern void xPortSysTickHandler( void );
#if (INCLUDE_xTaskGetSchedulerState == 1)
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
#endif /* INCLUDE_xTaskGetSchedulerState */
        xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1)
    }
#endif /* INCLUDE_xTaskGetSchedulerState */
#endif /* CONFIG_RTOS_FREERTOS */

    delay_tick();
}
