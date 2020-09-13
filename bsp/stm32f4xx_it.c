#include <stdio.h>

#include "delay.h"

void SysTick_Handler(void)
{
    delay_tick();
}
