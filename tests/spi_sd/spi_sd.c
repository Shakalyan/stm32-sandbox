#include <spi/spi.h>
#include <addr_map.h>
#include <common/log/log.h>
#include <gpio/gpio.h>
#include <common.h>
#include <timer_basic/timer_basic.h>


pspi_t SPI = (pspi_t)SPI1_BASE;
gpio_t cs;
ptimer_basic_t TIMER = (ptimer_basic_t)TIMER_BASIC_6_BASE;


static void sd_to_idle(void)
{
    int i = 0;

    gpio_raise(&cs);
    __DSB();
    __ISB();
    mdelay(TIMER, 10);
    for (i = 0; i < 50; ++i) {
        spi_txrx(SPI, 0xFF);
    }
}


// static void sd_send_cmd8(void)
// {
//     // send CMD0
//     gpio_lower(GPIO, 6);
//     __DSB();
//     __ISB();
//     mdelay(TIMER, 10);
//     spi_txrx(SPI, 0xFF);
//     spi_txrx(SPI, 0xFF);
//     spi_txrx(SPI, 0xFF);

//     spi_txrx(SPI, 0x48);
//     spi_txrx(SPI, 0x00);
//     spi_txrx(SPI, 0x00);
//     spi_txrx(SPI, 0x01);
//     spi_txrx(SPI, 0xAA);
//     spi_txrx(SPI, 0x87); // CRC
// }


void clear_print_read_buffer()
{
    uint8_t r;
    while ((SPI->SR & (1<<0))) {
        pr_info("rbd: %x\n", SPI->DR);
    }
}


static void sd_cs_down()
{
    gpio_lower(&cs);
    __DSB();
    __ISB();
    mdelay(TIMER, 10);
}

static void sd_cs_up()
{
    gpio_raise(&cs);
    __DSB();
    __ISB();
    mdelay(TIMER, 10);
    spi_txrx(SPI, 0xFF);
}


static int sd_send_cmd(uint8_t cmd, uint32_t arg, uint8_t crc, uint32_t *r)
{
    int i = 0;
    uint8_t byte;

    spi_txb_await_empty(SPI);
    spi_rxb_clear(SPI);
    sd_cs_down();

    spi_txrx(SPI, 0xFF);
    spi_txrx(SPI, 0xFF);
    spi_txrx(SPI, 0xFF);

    spi_txrx(SPI, (cmd | 0x40) & 0x7F);

    for (i = 0; i < 4; ++i) {
        byte = (arg>>(8*(3-i))) & 0xFF;
        spi_txrx(SPI, byte);
    }

    spi_txrx(SPI, crc | 1);

    //clear_print_read_buffer();
    for (i = 0; i < 8; ++i) {
        *r = spi_txrx(SPI, 0xFF);
        //pr_info("r = %x\n", *r);
        if (*r != 0xFF) {
            pr_info("r =  %x\n", *r);
            return 0;
        }
    }

    //sd_cs_up();

    return 0;
}





void main(void)
{
    pr_info("Start SPI SD test\n");
    gpio_init(&cs, GPIOB, 6);
    gpio_set_mode(&cs, GPIO_MODE_OUTPUT);

    timer_basic_init(TIMER, TIMER_BASIC_6);

    spi_init(SPI, SPI1);
    pr_info("SPI init ok\n");

    mdelay(TIMER, 100);
    sd_to_idle();


    int tries = 100, i;
    uint32_t r = 0;
    while ((r != 1) && (tries--)) {
        sd_send_cmd(0, 0, 0x95, &r);
    }

    if (r != 1) {
        pr_info("cmd0 failed\n");
        pr_info("tries left: %d\n", tries);
        goto Finish;
    }

    // sd_send_cmd(8, 0x1AA, 0x87);
    // for (i = 0; i < 16; ++i) {
    //     r = spi_txrx(SPI, 0xFF);
    //     pr_info("cmd8 r: %x\n", r);
    // }


Finish:
    while (1);
}
