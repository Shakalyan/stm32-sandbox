#include <stdint.h>
#include <gpio/gpio.h>
#include <addr_map.h>


void main(void)
{
    gpio_t led;
    gpio_init(&led, GPIOA, 6);

    gpio_set_mode(&led, GPIO_MODE_OUTPUT);

    int delay = 1000000;

    while (1)
    {
        gpio_raise(&led);
        for (uint32_t i = 0; i < delay; i++);
        gpio_lower(&led);
        for (uint32_t i = 0; i < delay; i++);
    }

}
