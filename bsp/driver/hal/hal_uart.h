#ifndef __HAL_UART_H
#define __HAL_UART_H

#include "stm32f4xx_usart.h"
#include "hal_gpio.h"

typedef struct {
    USART_TypeDef *uart;
    void *clk_cmd;
    uint32_t clk;
    uint32_t baudrate;
    hal_gpio_cfg_t tx;
    hal_gpio_cfg_t rx;
    uint32_t af;
    IRQn_Type irq;
} hal_uart_cfg_t;

void hal_uart_send_byte(hal_uart_cfg_t uart, uint8_t ch);
void hal_uart_init(hal_uart_cfg_t uart);

#endif /* __HAL_UART_H */
