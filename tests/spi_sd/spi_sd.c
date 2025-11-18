#include <spi/spi.h>
#include <addr_map.h>
#include <common/log/log.h>
#include <gpio/gpio.h>
#include <common.h>
#include <timer_basic/timer_basic.h>


pspi_t SPI = (pspi_t)SPI1_BASE;
pgpio_t GPIO = (pgpio_t)GPIOB_BASE;
ptimer_basic_t TIMER = (ptimer_basic_t)TIMER_BASIC_6_BASE;


static void sd_to_idle(void)
{
    int i = 0;

    gpio_set_pin(GPIO, 6);
    __DSB();
    __ISB();
    mdelay(TIMER, 10);
    for (i = 0; i < 80; ++i) {
        spi_txrx(SPI, 0xFF);
    }
}

// static uint8_t sd_send_cmd(uint8_t cmd, uint32_t arg)
// {
//     return 0;
// }

static void sd_send_cmd0(void)
{
    spi_txb_await_empty(SPI);
    spi_rxb_clear(SPI);

    // send CMD0
    gpio_unset_pin(GPIO, 6);
    __DSB();
    __ISB();
    mdelay(TIMER, 10);
    spi_txrx(SPI, 0xFF);
    spi_txrx(SPI, 0xFF);
    spi_txrx(SPI, 0xFF);

    spi_txrx(SPI, 0x40);
    spi_txrx(SPI, 0x00);
    spi_txrx(SPI, 0x00);
    spi_txrx(SPI, 0x00);
    spi_txrx(SPI, 0x00);
    spi_txrx(SPI, 0x95); // CRC

    pr_info("cmd0 ans:\n");
    for (int i = 0; i < 8; ++i) {
        uint8_t r = spi_txrx(SPI, 0xFF);
        pr_info("i:%d, r1 = %x\n", i, (uint32_t)r);
    }
}


static void sd_send_cmd8(void)
{
    // send CMD0
    gpio_unset_pin(GPIO, 6);
    __DSB();
    __ISB();
    mdelay(TIMER, 10);
    spi_txrx(SPI, 0xFF);
    spi_txrx(SPI, 0xFF);
    spi_txrx(SPI, 0xFF);

    spi_txrx(SPI, 0x48);
    spi_txrx(SPI, 0x00);
    spi_txrx(SPI, 0x00);
    spi_txrx(SPI, 0x01);
    spi_txrx(SPI, 0xAA);
    spi_txrx(SPI, 0x87); // CRC
}


void main(void)
{
    pr_info("Start SPI SD test\n");
    gpio_init(GPIO, GPIOB);
    gpio_set_port_mode(GPIO, 6, GPIO_PORT_MODE_OUTPUT);

    timer_basic_init(TIMER, TIMER_BASIC_6);

    spi_init(SPI, SPI1);
    pr_info("SPI init ok\n");

    mdelay(TIMER, 100);
    sd_to_idle();


    int tries = 5;
    while (tries--) {
        sd_send_cmd0();
    }


    while (1);
}
