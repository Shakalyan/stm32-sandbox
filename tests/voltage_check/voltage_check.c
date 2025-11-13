#include <stdint.h>
#include <gpio/gpio.h>
#include <addr_map.h>

#define LED ((6))

void main(void)
{
    pgpio_t GPIO = (pgpio_t)GPIOA_BASE;
    gpio_init(GPIO, GPIOA);

    gpio_set_port_mode(GPIO, LED, GPIO_PORT_MODE_OUTPUT);

    gpio_set_pin(GPIO, LED);

    while (1) {}

}
