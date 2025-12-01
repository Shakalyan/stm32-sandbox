#include <i2c/i2c.h>
#include <addr_map.h>
#include <errors.h>
#include <rcc/rcc.h>
#include <common.h>
#include <common/log/log.h>
#include <common/timer/timer.h>


int i2c_init(i2c_t *i2c, i2c_num_t num, gpio_t *sda, gpio_t *sck, uint32_t freq_khz)
{
    uint32_t addr, apb1_freq, crr;

    switch (num) {
        case I2C1:
            addr = I2C1_BASE;
            break;
        case I2C2:
            addr = I2C2_BASE;
            break;
        case I2C3:
            addr = I2C3_BASE;
            break;
    }

    i2c->regs = (pi2c_regs_t)addr;
    i2c->num = num;

    rcc_i2c_enable(num);

    apb1_freq = KHZ_TO_MHZ(rcc_get_apb1_freq_khz());
    if (apb1_freq < 2 || apb1_freq > 50) {
        pr_debug("I2C APB1 freq not supported: %dMHz\n", apb1_freq);
        return -I2C_APB1_FREQ_NOT_SUPPORTED;
    }
    SET_REG(i2c->regs->CR2, apb1_freq, I2C_CR2_FREQ_MSK, I2C_CR2_FREQ_OFS);

    if (freq_khz < 1 || freq_khz > 100) {
        pr_debug("I2C freq not supported: %dKHz\n", freq_khz);
        return -I2C_FREQ_NOT_SUPPORTED; // Fm mode not supported yet
    }

    CLR_BIT(i2c->regs->CCR, I2C_CCR_MODE);
    crr = (500 * apb1_freq) / freq_khz;
    SET_REG(i2c->regs->CCR, crr, I2C_CCR_CCR_MSK, I2C_CCR_CCR_OFS);

    SET_REG(i2c->regs->TRISE, apb1_freq+1, I2C_TRISE_TRISE_MSK, I2C_TRISE_TRISE_OFS);

    SET_BIT(i2c->regs->CR1, I2C_CR1_PE);
    __DSB();
    __ISB();

    return 0;
}


int i2c_start(i2c_t *i2c, uint8_t addr)
{
    uint32_t dummy, delay, tof;

    if (i2c->regs->SR2 & I2C_SR2_BUSY) {
        pr_debug("I2C bus is busy\n");
        pr_debug("SR1: %x\n", i2c->regs->SR1);
        pr_debug("SR2: %x\n", i2c->regs->SR2);
        return -I2C_BUSY;
    }

    SET_BIT(i2c->regs->CR1, I2C_CR1_START);

    AWAIT(i2c->regs->SR1 & I2C_SR1_SB, 100, tof);
    if (tof) {
        pr_debug("I2C SR1 SB timeout\n");
        pr_debug("SR1: %x\n", i2c->regs->SR1);
        return -TIMEOUT;
    }

    //addr &= ~(1); // Transmitter mode
    i2c->regs->DR = addr;

    AWAIT(i2c->regs->SR1 & I2C_SR1_ADDR, 100, tof);
    if (tof) {
        pr_debug("I2C SR1 ADDR timeout\n");
        pr_debug("SR1: %x\n", i2c->regs->SR1);
        return -TIMEOUT;
    }

    dummy = i2c->regs->SR2;

    return 0;
}


int i2c_tx(i2c_t *i2c, uint8_t byte)
{
    while (!(i2c->regs->SR1 & I2C_SR1_TXE));
    i2c->regs->DR = byte;
    return 0;
}


int i2c_stop(i2c_t *i2c)
{
    while (!(i2c->regs->SR1 & I2C_SR1_BTF));
    SET_BIT(i2c->regs->CR1, I2C_CR1_STOP);
    while (i2c->regs->SR2 & I2C_SR2_BUSY);
    return 0;
}
