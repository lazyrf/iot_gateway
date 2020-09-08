#ifndef __BOARD_H
#define __BOARD_H

#include "config.h"

#if defined(CONFIG_BOARD_STM32F405RGT)
#include "board_stm32f405rgt.h"
#endif 

void board_leds_init(void);
void board_leds_on(void);
void board_leds_off(void);
void board_leds_toggle(void);

#endif /* __BOARD_H */
