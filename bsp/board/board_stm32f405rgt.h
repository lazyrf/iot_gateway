#ifndef __BOARD_STM32F405RGT_H
#define __BOARD_STM32F405RGT_H

#include "drv_gpio.h"

#define BOARD_LED_NUM           2
#define BOARD_LED_LIST          { \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_4, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOA, .port = GPIOA, .pin = GPIO_Pin_15, .active_state = 0 }}

#endif /* __BOARD_STM32F405RGT_H */

