#include <uart/uart.h>
#include <addr_map.h>
#include <rcc/rcc.h>


void main(void)
{
    puart_t UART = (puart_t)UART2_BASE;

    prcc_t RCC = (prcc_t)RCC_BASE;
    uint32_t actual_freq = rcc_set_sysclk_freq(RCC, MHZ_TO_KHZ(SYSCLK_MHZ));

    uart_init(UART, UART2);

    uart_puts(UART, "UART utest\n");
    uart_puts(UART, "UARTDIV: ");
    uart_hex(UART, UART->BRR);
    uart_puts(UART, "\n");
    uart_puts(UART, "ACTUAL SYSCLK: ");
    uart_hex(UART, actual_freq);
    uart_puts(UART, "\n");

    while (1) {
        // uart_puts(UART, "test\n");
        // for (int i = 0; i < 3000000; ++i);
    }

}
