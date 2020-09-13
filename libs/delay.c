#include "delay.h"

#include "stm32f4xx.h"
#include "core_cm4.h"

static uint32_t delay_time;

void delay_tick(void)
{
    if (delay_time != 0) {
        delay_time--;
    }
}

void delay_ms(uint32_t msec)
{
    delay_time = msec;
    while (delay_time != 0);
}
