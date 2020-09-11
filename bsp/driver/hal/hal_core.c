#include "hal_core.h"
#include "stm32f4xx.h"

void hal_core_systick_init(void)
{
    /* SystemFrequency / 1000 ==> 1ms interrupt */
    /* SystemFrequency / 100000 == > 10us interrupt */
    /* SystemFrequency / 1000000 ==> 1us interrupt */
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }
}

