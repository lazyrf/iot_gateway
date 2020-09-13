#include "hal_core.h"

void hal_core_nvic_disable(IRQn_Type irq)
{
    NVIC_DisableIRQ(irq);
}

void hal_core_nvic_enable(IRQn_Type irq, uint32_t prio)
{
    NVIC_SetPriority(irq, prio);
    NVIC_EnableIRQ(irq);
}

void hal_core_systick_init(uint32_t period)
{
    uint32_t tick;
    uint32_t clk_mega;

    clk_mega = SystemCoreClock / 1000000;
    tick = clk_mega * period;
    SysTick_Config(tick);
}

