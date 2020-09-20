#ifndef __BOARD_STM32F405RGT_H
#define __BOARD_STM32F405RGT_H

#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_i2c.h"
#include "hal_rtc.h"

#define BOARD_LED_NUM           2
#define BOARD_LED_LIST          { \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_4, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOA, .port = GPIOA, .pin = GPIO_Pin_15, .active_state = 0 }}

#define BOARD_DO_NUM            4
#define BOARD_DO_LIST           { \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_12, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_13, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_14, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_15, .active_state = 0 }}

#define BOARD_DI_NUM            4
#define BOARD_DI_LIST           { \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOC, .port = GPIOB, .pin = GPIO_Pin_0, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOC, .port = GPIOB, .pin = GPIO_Pin_1, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOC, .port = GPIOB, .pin = GPIO_Pin_2, .active_state = 0 }, \
    { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOC, .port = GPIOB, .pin = GPIO_Pin_3, .active_state = 0 }}

#define BOARD_UART_NUM          1
#define BOARD_UART_LIST         { \
    { .uart = USART2, .clk_cmd = RCC_APB1PeriphClockCmd, .clk = RCC_APB1Periph_USART2, .baudrate = 115200, \
    .tx = { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOA, .port = GPIOA, .pin = GPIO_Pin_2, .active_state = 0 }, \
    .rx = { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOA, .port = GPIOA, .pin = GPIO_Pin_3, .active_state = 0 }, \
    .af = GPIO_AF_USART2, .irq = USART2_IRQn }}
#define BOARD_UART_DBG_IDX      0

#define BOARD_I2C_NUM           1
#define BOARD_I2C_LIST          { \
    { .i2c = I2C1, .clk_cmd = RCC_APB1PeriphClockCmd, .clk = RCC_APB1Periph_I2C1, \
    .scl = { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_6, .active_state = 0 }, \
    .sda = { .clk_cmd = RCC_AHB1PeriphClockCmd, .clk = RCC_AHB1Periph_GPIOB, .port = GPIOB, .pin = GPIO_Pin_7, .active_state = 0 }, \
    .af = GPIO_AF_I2C1, .addr = 0x1, .speed = 400000}}
#define BOARD_I2C_SESNOR_IDX    0

#define BOARD_RTC_CLK_SRC       HAL_RTC_CLK_SRC_LSE
#define BOARD_RTC_ALARM_NUM     2
#define BOARD_RTC_ALARM_LIST    { \
    HAL_RTC_ALARM_A, \
    HAL_RTC_ALARM_B}

#define BOARD_WATCHDOG_ENABLE       0

#define BOARD_FLASH_START_ADDRESS   0x08000000UL
#define BOARD_FLASH_END_ADDRESS     0x080FFFFFUL

#endif /* __BOARD_STM32F405RGT_H */

