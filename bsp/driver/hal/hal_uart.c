#include "hal_uart.h"

void hal_uart_send_byte(hal_uart_cfg_t uart, uint8_t ch)
{
    USART_SendData(uart.uart, ch);
    while (USART_GetFlagStatus(uart.uart, USART_FLAG_TXE) == RESET);
}

void hal_uart_init(hal_uart_cfg_t uart)
{
    USART_InitTypeDef uart_cfg;
    void (*rcc_clk_cmd)(uint32_t, FunctionalState);

    /* Enable clock */
    rcc_clk_cmd = uart.clk_cmd;
    rcc_clk_cmd(uart.clk, ENABLE);

    /* Config tx and rx gpio */
    hal_gpio_cfg_af_pp(uart.tx, uart.af);
    hal_gpio_cfg_af_pp(uart.rx, uart.af);

    /* Config uart */
    uart_cfg.USART_BaudRate = uart.baudrate;
    uart_cfg.USART_WordLength = USART_WordLength_8b;
    uart_cfg.USART_StopBits = USART_StopBits_1;
    uart_cfg.USART_Parity = USART_Parity_No;
    uart_cfg.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart_cfg.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(uart.uart, &uart_cfg);
    USART_Cmd(uart.uart, ENABLE);
}
