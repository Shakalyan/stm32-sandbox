#include <spi/spi.h>
#include <rcc/rcc.h>
#include <gpio/gpio.h>
#include <addr_map.h>
#include <common.h>


void spi_init(pspi_t SPI, spi_num_t num)
{
    rcc_spi_enable(num);

    gpio_t sck, miso, mosi;

    gpio_init(&sck, GPIOA, 5);
    gpio_init(&miso, GPIOA, 6);
    gpio_init(&mosi, GPIOA, 7);

    gpio_set_mode(&sck, GPIO_MODE_AF);
    gpio_set_mode(&miso, GPIO_MODE_AF);
    gpio_set_mode(&mosi, GPIO_MODE_AF);

    gpio_set_af(&sck, 5);
    gpio_set_af(&miso, 5);
    gpio_set_af(&mosi, 5);

    gpio_set_pupd(&sck, GPIO_PUPDR_NO);
    //gpio_set_pupd(&miso, GPIO_PUPDR_PU);
    gpio_set_pupd(&miso, GPIO_PUPDR_NO);
    gpio_set_pupd(&mosi, GPIO_PUPDR_NO);

    SPI->CR1 |= (1<<9) | (1<<8) | (0b111<<3) | (1<<2); // BRR f/256, SSM, SSI=1, MSTR
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
