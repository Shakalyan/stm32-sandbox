#include <uart/uart.h>
#include <addr_map.h>


void main(void)
{
    puart_t UART = (puart_t)UART2_BASE;

    uart_init(UART, 115200);

    uart_puts(UART, "Ale eto test\n");

    uart_hex(UART, 170);

    while (1) {
        // uart_puts(UART, "test\n");
        // for (int i = 0; i < 3000000; ++i);
    }

}
