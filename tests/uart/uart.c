#include <uart/uart.h>
#include <addr_map.h>
#include <rcc/rcc.h>
#include <errors.h>


void main(void)
{
    puart_t UART = (puart_t)UART2_BASE;
    prcc_t RCC = (prcc_t)RCC_BASE;
    int res;

    uart_init(UART, UART2);

    uart_puts(UART, "Before switch to PLL...\n");
    uart_puts(UART, "INCLK: ");
    uart_hex(UART, INCLK_MHZ*1000000);
    uart_puts(UART, "\n");
    uart_puts(UART, "ACTUAL SYSCLK: ");
    uart_hex(UART, rcc_get_sysclk_freq_khz(RCC)*1000);
    uart_puts(UART, "\n");

    res = rcc_init(RCC);
    if (res != SUCCESS) {
        uart_puts(UART, "Error: ");
        uart_hex(UART, res);
        uart_puts(UART, "\n");
        goto Finish;
    }

    uart_init(UART, UART2);
    uart_puts(UART, "UART utest\n");
    uart_puts(UART, "UARTDIV: ");
    uart_hex(UART, UART->BRR);
    uart_puts(UART, "\n");
    uart_puts(UART, "ACTUAL SYSCLK: ");
    uart_hex(UART, rcc_get_apb1_freq_khz(RCC)*1000);
    uart_puts(UART, "\n");

Finish:
    while (1) {
        // uart_puts(UART, "test\n");
        // for (int i = 0; i < 3000000; ++i);
    }

}
