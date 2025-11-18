#include <spi/spi.h>
#include <rcc/rcc.h>
#include <gpio/gpio.h>
#include <addr_map.h>
#include <common.h>


void spi_init(pspi_t SPI, spi_num_t num)
{
    rcc_spi_enable(num);

    pgpio_t GPIO = (pgpio_t)GPIOA_BASE;

    gpio_init(GPIO, GPIOA);

    gpio_set_port_mode(GPIO, 5, GPIO_PORT_MODE_AF);
    gpio_set_port_mode(GPIO, 6, GPIO_PORT_MODE_AF);
    gpio_set_port_mode(GPIO, 7, GPIO_PORT_MODE_AF);

    gpio_set_port_af(GPIO, 5, 5); // SCK
    gpio_set_port_af(GPIO, 6, 5); // MISO
    gpio_set_port_af(GPIO, 7, 5); // MOSI

    gpio_set_port_pupd(GPIO, 5, GPIO_PORT_PUPDR_NO);
    gpio_set_port_pupd(GPIO, 6, GPIO_PORT_PUPDR_PU);
    gpio_set_port_pupd(GPIO, 7, GPIO_PORT_PUPDR_NO);

    SPI->CR1 |= (1<<9) | (1<<8) | (0b111<<3) | (1<<2); // BRR f/128, SSM, SSI=1, MSTR
    SPI->CR1 |= (1<<6); // SPI enable
    __DSB();
    __ISB();
}


uint8_t spi_txrx(pspi_t SPI, uint8_t byte)
{
    while (!(SPI->SR & (1<<1)));
    SPI->DR = byte;
    while (!(SPI->SR & (1<<0)));
    return SPI->DR;
}


void spi_rxb_clear(pspi_t SPI)
{
    uint8_t r;
    while ((SPI->SR & (1<<0)))
        r = SPI->DR;
}


void spi_txb_await_empty(pspi_t SPI)
{
    while (!(SPI->SR & (1<<1)));
}
