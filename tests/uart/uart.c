#include <uart/uart.h>
#include <addr_map.h>


void main(void)
{
    puart_t UART = (puart_t)UART2_BASE;

    uart_init(UART, UART2);

    uart_puts(UART, "UART utest\n");
    uart_puts(UART, "UARTDIV: ");
    uart_hex(UART, UART->BRR);
    uart_puts(UART, "\n");

    while (1) {
        // uart_puts(UART, "test\n");
        // for (int i = 0; i < 3000000; ++i);
    }

}
