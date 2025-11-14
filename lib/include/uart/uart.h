#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>
#define UART_OVER8 ((0))

typedef volatile struct uart {
    uint32_t SR;
    uint32_t DR;
    uint32_t BRR;
    uint32_t CR1;
    uint32_t CR2;
    uint32_t CR3;
    uint32_t GTPR;
} uart_t;
typedef volatile uart_t* puart_t;

typedef enum uart_num {
    UART1 = 1,
    UART2,
    UART3,
    UART4,
    UART5,
    UART6
} uart_num_t;

void uart_init(puart_t UART, uart_num_t uart_num);

void uart_putc(puart_t UART, uint8_t symbol);

void uart_puts(puart_t UART, char *s);

void uart_hex(puart_t UART, uint32_t value);

void uart_uint32(puart_t UART, uint32_t value);

#endif
