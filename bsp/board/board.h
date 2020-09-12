#ifndef __BOARD_H
#define __BOARD_H

#include "config.h"

#if defined(CONFIG_BOARD_STM32F405RGT)
#include "board_stm32f405rgt.h"
#endif

#if BOARD_LED_NUM > 0
extern hal_gpio_cfg_t led_gpio_list[BOARD_LED_NUM];
#endif /* BOARD_LED_NUM > 0 */

#if BOARD_DO_NUM > 0
extern hal_gpio_cfg_t do_gpio_list[BOARD_DO_NUM];
#endif /* BOARD_DO_NUM > 0 */

#if BOARD_DI_NUM > 0
extern hal_gpio_cfg_t di_gpio_list[BOARD_DI_NUM];
#endif /* BOARD_DI_NUM > 0 */

#if BOARD_UART_NUM > 0
extern hal_uart_cfg_t uart_list[BOARD_UART_NUM];
#endif /* BOARD_UART_NUM > 0 */

#if BOARD_I2C_NUM > 0
extern hal_i2c_cfg_t i2c_list[BOARD_I2C_NUM];
#endif /* BOARD_I2C_NUM > 0 */

#if BOARD_RTC_ALARM_NUM > 0
extern hal_rtc_alarm_t rtc_alarm_list[BOARD_RTC_ALARM_NUM];
#endif /* BOARD_RTC_ALARM_NUM > 0 */

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
