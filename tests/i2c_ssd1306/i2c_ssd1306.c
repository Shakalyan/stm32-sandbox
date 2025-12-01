#include <i2c/i2c.h>
#include <gpio/gpio.h>
#include <common/timer/timer.h>
#include <common/log/log.h>
#include <common.h>

#define SSD1306_CMD_DISPLAY_ONOFF(x) ((0xAE | x))

#define SSD1306_CB_CO BIT(7)
#define SSD1306_CB_DC BIT(6)

typedef enum tx_type {
    TX_COMMAND,
    TX_DATA
} tx_type_t;


int ssd1306_tx(i2c_t *i2c, tx_type_t tx_type, uint8_t data)
{
    int err;
    err = i2c_start(i2c, 0x78);
    if (err) {
        pr_error("I2C: failed to send SB\n");
        return err;
    }

    if (tx_type == TX_COMMAND)
        i2c_tx(i2c, SSD1306_CB_CO);
    else
        i2c_tx(i2c, SSD1306_CB_CO | SSD1306_CB_DC);
    i2c_tx(i2c, data);

    i2c_stop(i2c);
    return 0;
}


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

    // ssd1306_tx(&i2c, TX_COMMAND, SSD1306_CMD_DISPLAY_ONOFF(1));

    // ssd1306_tx(&i2c, TX_COMMAND, 0x21); // column
    // ssd1306_tx(&i2c, TX_COMMAND, 0x00);
    // ssd1306_tx(&i2c, TX_COMMAND, 0x00);

    // ssd1306_tx(&i2c, TX_COMMAND, 0x22); // page
    // ssd1306_tx(&i2c, TX_COMMAND, 0x00);
    // ssd1306_tx(&i2c, TX_COMMAND, 0x00);

    // ssd1306_tx(&i2c, TX_DATA, 0xFF);

    // SLEEP MODE
    ssd1306_tx(&i2c, TX_COMMAND, SSD1306_CMD_DISPLAY_ONOFF(0));

    // CLK div
    ssd1306_tx(&i2c, TX_COMMAND, 0xD5);
    ssd1306_tx(&i2c, TX_COMMAND, 0x80);

    // MUX ratio
    ssd1306_tx(&i2c, TX_COMMAND, 0xA8);
    ssd1306_tx(&i2c, TX_COMMAND, 0x3F);

    // Display offset
    ssd1306_tx(&i2c, TX_COMMAND, 0xD3);
    ssd1306_tx(&i2c, TX_COMMAND, 0x00);

    // Start line
    ssd1306_tx(&i2c, TX_COMMAND, 0x40);

    // Charge pump
    ssd1306_tx(&i2c, TX_COMMAND, 0x8D);
    ssd1306_tx(&i2c, TX_COMMAND, 0x14);

    // Horizontal mode
    ssd1306_tx(&i2c, TX_COMMAND, 0x20);
    ssd1306_tx(&i2c, TX_COMMAND, 0x00);

    // Column remap
    ssd1306_tx(&i2c, TX_COMMAND, 0xA0);
    ssd1306_tx(&i2c, TX_COMMAND, 0x00);

    // Scan direction
    ssd1306_tx(&i2c, TX_COMMAND, 0xC8);

    // COM conf
    ssd1306_tx(&i2c, TX_COMMAND, 0xDA);
    ssd1306_tx(&i2c, TX_COMMAND, 0x12);

    // Contrast
    ssd1306_tx(&i2c, TX_COMMAND, 0x81);
    ssd1306_tx(&i2c, TX_COMMAND, 0xCF);

    // Precharge
    ssd1306_tx(&i2c, TX_COMMAND, 0xD9);
    ssd1306_tx(&i2c, TX_COMMAND, 0xF1);

    // VCOM deselect level
    ssd1306_tx(&i2c, TX_COMMAND, 0xDB);
    ssd1306_tx(&i2c, TX_COMMAND, 0x40);

    // Display on resume
    ssd1306_tx(&i2c, TX_COMMAND, 0xA4);

    // Normal display
    ssd1306_tx(&i2c, TX_COMMAND, 0xA6);

    // On
    ssd1306_tx(&i2c, TX_COMMAND, 0xAF);

    //ssd1306_tx(&i2c, TX_DATA, 0xFF);

    mdelay(10000);
    ssd1306_tx(&i2c, TX_COMMAND, SSD1306_CMD_DISPLAY_ONOFF(0));

    pr_info("test finished\n");

Finish:
    pr_info("CR1: %x\n", i2c.regs->CR1);
    pr_info("CR2: %x\n", i2c.regs->CR2);
    pr_info("CCR: %x\n", i2c.regs->CCR);
    pr_info("SR1: %x\n", i2c.regs->SR1);
    pr_info("SR2: %x\n", i2c.regs->SR2);
    while (1);

}
