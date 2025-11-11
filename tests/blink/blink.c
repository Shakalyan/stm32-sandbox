#include <stdint.h>
#include <gpio/gpio.h>
#include <addr_map.h>

#define LED ((6))

void main(void)
{
    pgpio_t GPIO = (pgpio_t)GPIOA_BASE;
    gpio_init(GPIO, GPIOA);

    gpio_set_port_mode(GPIO, LED, GPIO_PORT_MODE_OUTPUT);

    int delay = 1000000;

    while (1)
    {
        gpio_set_pin(GPIO, LED);
        for (uint32_t i = 0; i < delay; i++);
        gpio_unset_pin(GPIO, LED);
        for (uint32_t i = 0; i < delay; i++);
    }

}
