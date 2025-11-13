#include <uart/uart.h>
#include <rcc/rcc.h>
#include <addr_map.h>
#include <gpio/gpio.h>
#include <common.h>


void uart_init(puart_t UART, uart_num_t uart_num)
{
    prcc_t RCC = (prcc_t)RCC_BASE;
    pgpio_t GPIO = (pgpio_t)GPIOA_BASE;
    uint32_t mant = 0, frac = 0;
    uint32_t sysclk = rcc_get_apb1_freq_khz(RCC)*1000; // TODO: fix
    uint32_t div = (8*(2-UART_OVER8)*CONFIG_UART_BAUD_RATE);
    uint32_t prec = 100;

    rcc_uart_enable(RCC, uart_num);

    gpio_init(GPIO, GPIOA);
    gpio_set_port_mode(GPIO, 2, GPIO_PORT_MODE_AF);
    gpio_set_port_mode(GPIO, 3, GPIO_PORT_MODE_AF);
    gpio_set_port_af(GPIO, 2, 7);
    gpio_set_port_af(GPIO, 3, 7);

    mant = sysclk / div;

    frac = (((sysclk*prec / div) % prec)*16 + (prec/2)) / prec;
    if (frac > 15) frac = 15;
    frac = frac & (0b1111>>UART_OVER8);

    UART->BRR = ((mant<<(4-UART_OVER8)) + frac);
    UART->CR1 = (1<<13) | (1<<3) | (1<<2); // UART + TX + RX
    __DSB();
    __ISB();
}

void uart_putc(puart_t UART, uint8_t symbol)
{
    while (!(UART->SR & (1<<7)));
    UART->DR = symbol;
}

void uart_puts(puart_t UART, char *s)
{
    while (*s) {
        if (*s == '\n')
            uart_putc(UART, '\r');
        uart_putc(UART, *s++);
    }
}

void uart_hex(puart_t UART, uint64_t value)
{
    uint64_t shift = 0, i = 0;
    uint8_t byte = 0;

    for (i = 0; i < 16; ++i) {
        shift = (16-i-1)*4;
        byte = (value & (0xFULL<<shift)) >> shift;
        if (byte < 10)
            uart_putc(UART, '0'+byte);
        else
            uart_putc(UART, 'A'+(byte%10));
    }
}
