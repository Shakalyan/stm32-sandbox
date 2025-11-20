#include <stdint.h>
#include <gpio/gpio.h>
#include <addr_map.h>

void main(void)
{
    gpio_t gpio;
    gpio_init(&gpio, GPIOA, 6);

    gpio_set_mode(&gpio, GPIO_MODE_OUTPUT);

    gpio_raise(&gpio);

    while (1) {}

}
