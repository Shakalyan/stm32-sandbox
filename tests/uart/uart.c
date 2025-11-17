#include <uart/uart.h>
#include <addr_map.h>
#include <rcc/rcc.h>
#include <errors.h>
#include <common/log/log.h>


void main(void)
{
    puart_t UART = (puart_t)UART2_BASE;
    int res;

    uart_init(UART, UART2);
    uart_puts(UART, "UART utest\n");
    uart_puts(UART, "UARTDIV: ");
    uart_hex(UART, UART->BRR);
    uart_puts(UART, "\n");
    uart_puts(UART, "ACTUAL SYSCLK: ");
    uart_hex(UART, rcc_get_apb1_freq_khz()*1000);
    uart_puts(UART, "\n");
    uart_uint32(UART, 123);
    pr_debug("UART BRR: %x\n", UART->BRR);

    while (1) ;

}
