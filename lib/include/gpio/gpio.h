#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

typedef volatile struct gpio
{
    uint32_t MODER;
    uint32_t OTYPER;
    uint32_t OSPEEDER;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFRL;
    uint32_t AFRH;
} gpio_t;
typedef volatile gpio_t* pgpio_t;

enum GPIO_PORT {
    GPIOA = 0,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH
};

#define GPIO_PORT_MODE_INPUT  ((0b00))
#define GPIO_PORT_MODE_OUTPUT ((0b01))
#define GPIO_PORT_MODE_AF     ((0b10))
#define GPIO_PORT_MODE_ANALOG ((0b11))

void gpio_init(pgpio_t GPIO, enum GPIO_PORT port);

void gpio_set_port_mode(pgpio_t GPIO, int pin, int mode);

void gpio_set_pin(pgpio_t GPIO, int pin);

void gpio_unset_pin(pgpio_t GPIO, int pin);


#endif
