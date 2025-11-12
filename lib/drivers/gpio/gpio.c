#include <gpio/gpio.h>
#include <rcc/rcc_rmap.h>
#include <rcc/rcc.h>
#include <addr_map.h>


void gpio_init(pgpio_t GPIO, enum GPIO_PORT port)
{
    prcc_t RCC = (prcc_t)RCC_BASE;
    volatile uint32_t dummy;

    RCC->AHB1ENR |= (1<<port);
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;
}

void gpio_set_port_mode(pgpio_t GPIO, int pin, int mode)
{
    GPIO->MODER |= (mode<<(pin*2));
}

void gpio_set_pin(pgpio_t GPIO, int pin)
{
    GPIO->ODR |= (1<<pin);
}

void gpio_unset_pin(pgpio_t GPIO, int pin)
{
    GPIO->ODR &= ~(1<<pin);
}

void gpio_set_port_af(pgpio_t GPIO, int pin, int value)
{
    if (pin < 8) {
        GPIO->AFRL &= ~(0b1111<<(4*pin));
        GPIO->AFRL |= (value<<(4*pin));
    }
    else {
        GPIO->AFRH &= ~(0b1111<<(4*pin));
        GPIO->AFRH |= (value<<(4*pin));
    }
}
