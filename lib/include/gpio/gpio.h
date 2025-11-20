#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

typedef volatile struct gpio_regs
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
} gpio_regs_t;
typedef volatile gpio_regs_t* pgpio_regs_t;

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

typedef struct gpio {
    pgpio_regs_t regs;
    gpio_port_t port;
    int pin;
} gpio_t;


// Regs values

typedef enum gpio_mode {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_AF,
    GPIO_MODE_ANALOG
} gpio_mode_t;

typedef enum gpio_output_type {
    GPIO_OUTPUT_TYPE_PUSH_PULL = 0,
    GPIO_OUTPUT_TYPE_OPEN_DRAIN
} gpio_output_type_t;

typedef enum gpio_pupd {
    GPIO_PUPDR_NO = 0,
    GPIO_PUPDR_PU,
    GPIO_PUPDR_PD
} gpio_pupd_t;

typedef enum gpio_speed {
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_FAST,
    GPIO_SPEED_HIGH
} gpio_speed_t;

void gpio_init(gpio_t *gpio, gpio_port_t port, int pin);

void gpio_set_mode(gpio_t *gpio, gpio_mode_t mode);

void gpio_raise(gpio_t *gpio);

void gpio_lower(gpio_t *gpio);

void gpio_set_af(gpio_t *gpio, int value);

void gpio_set_output_type(gpio_t *gpio, gpio_output_type_t type);

void gpio_set_pupd(gpio_t *gpio, gpio_pupd_t value);

void gpio_set_speed(gpio_t *gpio, gpio_speed_t speed);


#endif
