#include <i2c/i2c.h>
#include <gpio/gpio.h>
#include <common/timer/timer.h>
#include <common/log/log.h>
#include <common.h>

#define SSD1306_CMD_DISPLAY_ONOFF(x) ((0xAE | x))


void main(void)
{
    i2c_t i2c;
    gpio_t sda, scl;
    int err;

    pr_info("i2c ssd1306 test start\n");

    gpio_init(&scl, GPIOB, 8);
    gpio_init(&sda, GPIOB, 9);

    gpio_set_mode(&scl, GPIO_MODE_AF);
    gpio_set_mode(&sda, GPIO_MODE_AF);

    gpio_set_af(&scl, 4);
    gpio_set_af(&sda, 4);

    gpio_set_output_type(&scl, GPIO_OUTPUT_TYPE_OPEN_DRAIN);
    gpio_set_output_type(&sda, GPIO_OUTPUT_TYPE_OPEN_DRAIN);

    gpio_set_speed(&scl, GPIO_SPEED_FAST);
    gpio_set_speed(&sda, GPIO_SPEED_FAST);

    __DSB();
    __ISB();

    // pr_info("GPIO BASE: %x\n", scl.regs);
    // pr_info("GPIO MODER: %x\n", scl.regs->MODER);
    // pr_info("GPIO AFRL: %x\n", scl.regs->AFRL);
    // pr_info("GPIO AFRH: %x\n", scl.regs->AFRH);
    // pr_info("GPIO OTYPER: %x\n", scl.regs->OTYPER);
    // pr_info("GPIO OSPEEDER: %x\n", scl.regs->OSPEEDER);
    // pr_info("GPIO PUPDR: %x\n", scl.regs->PUPDR);

    err = i2c_init(&i2c, I2C1, &sda, &scl, 100);
    if (err) {
        pr_info("I2C init failed\n");
        goto Finish;
    }
    pr_info("I2C init ok\n");

    err = i2c_start(&i2c, 0x78);
    if (err) {
        pr_info("I2C start failed\n");
        goto Finish;
    }
    pr_info("I2C start ok\n");

    i2c_tx(&i2c, SSD1306_CMD_DISPLAY_ONOFF(0));
    mdelay(3000);
    i2c_tx(&i2c, SSD1306_CMD_DISPLAY_ONOFF(1));

    i2c_stop(&i2c);

    pr_info("test finished\n");

Finish:
    pr_info("CR1: %x\n", i2c.regs->CR1);
    pr_info("CR2: %x\n", i2c.regs->CR2);
    pr_info("CCR: %x\n", i2c.regs->CCR);
    pr_info("SR1: %x\n", i2c.regs->SR1);
    pr_info("SR2: %x\n", i2c.regs->SR2);
    while (1);

}
