#include <uart/uart.h>
#include <rcc/rcc.h>
#include <addr_map.h>
#include <gpio/gpio.h>

#define SYSCLK ((8000000)) // TODO: calculate

void uart_init(puart_t UART, uint16_t baud)
{
    prcc_t RCC = (prcc_t)RCC_BASE;
    pgpio_t GPIO = (pgpio_t)GPIOA_BASE;

    RCC->APB1ENR |= (1<<17);

    gpio_init(GPIO, GPIOA);
    gpio_set_port_mode(GPIO, 2, GPIO_PORT_MODE_AF);
    gpio_set_port_mode(GPIO, 3, GPIO_PORT_MODE_AF);
    gpio_set_port_af(GPIO, 2, 7);
    gpio_set_port_af(GPIO, 3, 7);

    //USART->BRR = (uint16_t)(SYSCLK / baud);
    UART->BRR = 0x8B; //0x45; // 115200
    UART->CR1 = (1<<13) | (1<<3) | (1<<2);
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
