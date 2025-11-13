#include <rcc/rcc.h>
#include <rcc/rcc_rmap.h>
#include <common.h>


void rcc_uart_enable(prcc_t RCC, uart_num_t uart_num)
{
    if (uart_num == 1) {
        RCC->APB2ENR |= 1<<4;
    }
    else if (uart_num == 6) {
        RCC->APB2ENR |= 1<<5;
        return;
    }
    else {
        RCC->APB1ENR |= 1<<(17+(uart_num-2));
    }
    __DSB();
    __ISB();
}

void rcc_gpio_enable(prcc_t RCC, gpio_port_t gpio_num)
{
    RCC->AHB1ENR |= 1<<gpio_num;
    __DSB();
    __ISB();
}
