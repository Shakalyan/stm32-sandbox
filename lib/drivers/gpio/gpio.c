#include <gpio/gpio.h>
#include <rcc/rcc.h>
#include <addr_map.h>


void gpio_init(gpio_t *gpio, gpio_port_t port, int pin)
{
    uint32_t addr;

    rcc_gpio_enable(port);

    switch (port) {
        case GPIOA:
            addr = GPIOA_BASE;
        case GPIOB:
            addr = GPIOB_BASE;
        case GPIOC:
            addr = GPIOC_BASE;
        case GPIOD:
            addr = GPIOD_BASE;
        case GPIOE:
            addr = GPIOE_BASE;
        case GPIOF:
            addr = GPIOF_BASE;
        case GPIOG:
            addr = GPIOG_BASE;
        case GPIOH:
            addr = GPIOH_BASE;
    }

    gpio->regs = (pgpio_regs_t)addr;
    gpio->port = port;
    gpio->pin = pin;
}

void gpio_set_mode(gpio_t *gpio, gpio_mode_t mode)
{
    gpio->regs->MODER &= ~(0b11<<(gpio->pin*2));
    gpio->regs->MODER |= (mode<<(gpio->pin*2));
}

void gpio_raise(gpio_t *gpio)
{
    gpio->regs->ODR |= (1 << gpio->pin);
}

void gpio_lower(gpio_t *gpio)
{
    gpio->regs->ODR &= ~(1 << gpio->pin);
}

void gpio_set_af(gpio_t *gpio, int value)
{
    int pin = gpio->pin;
    if (pin < 8) {
        gpio->regs->AFRL &= ~(0b1111<<(4*pin));
        gpio->regs->AFRL |= (value<<(4*pin));
    }
    else {
        gpio->regs->AFRH &= ~(0b1111<<(4*pin));
        gpio->regs->AFRH |= (value<<(4*pin));
    }
}

void gpio_set_output_type(gpio_t *gpio, gpio_output_type_t type)
{
    gpio->regs->OTYPER &= ~(1 << gpio->pin);
    gpio->regs->OTYPER |= (type << gpio->pin);
}

void gpio_set_pupd(gpio_t *gpio, gpio_pupd_t value)
{
    gpio->regs->PUPDR &= ~(0b11 << gpio->pin);
    gpio->regs->PUPDR |= (value << gpio->pin);
}

void gpio_set_speed(gpio_t *gpio, gpio_speed_t speed)
{
    gpio->regs->OSPEEDER &= ~(0b11 << gpio->pin);
    gpio->regs->OSPEEDER |= (speed << gpio->pin);
}
