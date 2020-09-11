#include "drv_uart_dbg.h"
#include "board.h"
#include "hal_uart.h"
#include "assert.h"

int __io_putchar(int ch)
{
    hal_uart_send_byte(uart_list[BOARD_UART_DBG_IDX], ch);
    return (ch);
}

void drv_uart_dbg_init(void)
{
    hal_uart_init(uart_list[BOARD_UART_DBG_IDX]);
}
