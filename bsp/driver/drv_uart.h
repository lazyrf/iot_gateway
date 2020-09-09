#ifndef __DRV_UART_H
#define __DRV_UART_H

#include "stm32f4xx_usart.h"
#include "drv_gpio.h"

typedef struct {
    USART_TypeDef *uart;
    void *clk_cmd;
    uint32_t clk;
    uint32_t baudrate;
    drv_gpio_cfg_t tx;
    drv_gpio_cfg_t rx;
    uint32_t af;
    IRQn_Type irq;
} drv_uart_cfg_t;

void drv_uart_send_byte(drv_uart_cfg_t uart, uint8_t ch);
void drv_uart_init(drv_uart_cfg_t uart);

#endif /* __DRV_UART_H */
