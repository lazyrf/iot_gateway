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
void board_led_on(int idx);
void board_led_off(int idx);
void board_led_toggle(int idx);

void board_dos_init(void);
void board_dos_on(void);
void board_dos_off(void);
void board_do_on(int idx);
void board_do_off(int idx);

void board_init(void);
uint8_t board_di_status(int idx);

void board_init(void);
#endif /* __BOARD_H */
