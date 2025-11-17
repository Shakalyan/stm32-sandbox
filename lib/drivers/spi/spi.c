#include <spi/spi.h>
#include <rcc/rcc.h>
#include <gpio/gpio.h>
#include <addr_map.h>


void spi_init(pspi_t SPI, spi_num_t num)
{
    rcc_spi_enable(num);

    pgpio_t gpioa = (pgpio_t)GPIOA_BASE;
    pgpio_t gpiob = (pgpio_t)GPIOB_BASE;

    gpio_init(gpioa, GPIOA);
    gpio_init(gpiob, GPIOB);

    gpio_set_port_mode(gpioa, 15, GPIO_PORT_MODE_AF);
    gpio_set_port_mode(gpiob, 3, GPIO_PORT_MODE_AF);
    gpio_set_port_mode(gpiob, 4, GPIO_PORT_MODE_AF);
    gpio_set_port_mode(gpiob, 5, GPIO_PORT_MODE_AF);

    gpio_set_port_af(gpioa, 15, 5); // CS
    gpio_set_port_af(gpiob, 3, 5); // SCK
    gpio_set_port_af(gpiob, 4, 5); // MISO
    gpio_set_port_af(gpiob, 5, 5); // MOSI

    gpio_set_port_pupd(gpioa, 15, GPIO_PORT_PUPDR_NO);
    gpio_set_port_pupd(gpiob, 3, GPIO_PORT_PUPDR_NO);
    gpio_set_port_pupd(gpiob, 4, GPIO_PORT_PUPDR_PU);
    gpio_set_port_pupd(gpiob, 5, GPIO_PORT_PUPDR_NO);


}
