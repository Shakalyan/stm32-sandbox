#include <gpio/gpio.h>
#include <rcc/rcc.h>
#include <addr_map.h>


void gpio_init(pgpio_t GPIO, gpio_port_t port)
{
    rcc_gpio_enable(port);
}

void gpio_set_port_mode(pgpio_t GPIO, int pin, int mode)
{
    GPIO->MODER &= ~(0b11<<(pin*2));
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

void gpio_set_port_output_type(pgpio_t GPIO, int pin, int type)
{
    GPIO->OTYPER &= ~(1<<pin);
    GPIO->OTYPER |= (type<<pin);
}

void gpio_set_port_pupd(pgpio_t GPIO, int pin, int value)
{
    GPIO->PUPDR &= ~(0b11<<pin);
    GPIO->PUPDR |= value<<pin;
}

void gpio_set_port_speed(pgpio_t GPIO, int pin, int value)
{
    GPIO->OSPEEDER &= ~(0b11<<pin);
    GPIO->OSPEEDER |= value<<pin;
}
