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

typedef enum gpio_port {
    GPIOA = 0,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH
} gpio_port_t;

#define GPIO_PORT_MODE_INPUT  ((0b00))
#define GPIO_PORT_MODE_OUTPUT ((0b01))
#define GPIO_PORT_MODE_AF     ((0b10))
#define GPIO_PORT_MODE_ANALOG ((0b11))

#define GPIO_PORT_OUTPUT_TYPE_PP ((0))
#define GPIO_PORT_OUTPUT_TYPE_OD ((1))

#define GPIO_PORT_PUPDR_NO ((0b00))
#define GPIO_PORT_PUPDR_PU ((0b01))
#define GPIO_PORT_PUPDR_PD ((0b10))

#define GPIO_PORT_SPEED_LOW    ((0b00))
#define GPIO_PORT_SPEED_MEDIUM ((0b01))
#define GPIO_PORT_SPEED_FAST   ((0b10))
#define GPIO_PORT_SPEED_HIGH   ((0b11))

void gpio_init(pgpio_t GPIO, gpio_port_t port);

void gpio_set_port_mode(pgpio_t GPIO, int pin, int mode);

void gpio_set_pin(pgpio_t GPIO, int pin);

void gpio_unset_pin(pgpio_t GPIO, int pin);

void gpio_set_port_af(pgpio_t GPIO, int pin, int value);

void gpio_set_port_output_type(pgpio_t GPIO, int pin, int type);

void gpio_set_port_pupd(pgpio_t GPIO, int pin, int value);

void gpio_set_port_speed(pgpio_t GPIO, int pin, int value);


#endif
