#ifndef __HAL_CORE_H
#define __HAL_CORE_H

#include "stm32f4xx.h"

void hal_core_nvic_disable(IRQn_Type irq);
void hal_core_nvic_enable(IRQn_Type irq, uint32_t prio);
void hal_core_nvic_init(void);
void hal_core_systick_init(uint32_t period);

#endif /* __HAL_CORE_H */
