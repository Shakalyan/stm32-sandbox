#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>
#include <gpio/gpio.h>


typedef volatile struct i2c_regs {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t OAR1;
    uint32_t OAR2;
    uint32_t DR;
    uint32_t SR1;
    uint32_t SR2;
    uint32_t CCR;
    uint32_t TRISE;
    uint32_t FLTR;
} i2c_regs_t;
typedef volatile i2c_regs_t* pi2c_regs_t;


typedef enum i2c_num {
    I2C1 = 0,
    I2C2,
    I2C3
} i2c_num_t;


typedef struct i2c {
    pi2c_regs_t regs;
    i2c_num_t num;
} i2c_t;


#define I2C_SR1_SB BIT(0)
#define I2C_SR1_ADDR BIT(1)
#define I2C_SR1_BTF BIT(2)
#define I2C_SR1_TXE BIT(7)
#define I2C_SR1_AF BIT(10)

#define I2C_SR2_BUSY BIT(1)

#define I2C_CR1_PE BIT(0)
#define I2C_CR1_START BIT(8)
#define I2C_CR1_STOP BIT(9)

#define I2C_CR2_FREQ_MSK ((0x3F))
#define I2C_CR2_FREQ_OFS ((0))

#define I2C_CCR_MODE BIT(15)
#define I2C_CCR_CCR_MSK ((0xFFF))
#define I2C_CCR_CCR_OFS ((0))

#define I2C_TRISE_TRISE_MSK ((0x3F))
#define I2C_TRISE_TRISE_OFS ((0))


int i2c_init(i2c_t *i2c, i2c_num_t num, gpio_t *sda, gpio_t *sck, uint32_t freq_khz);

int i2c_start(i2c_t *i2c, uint8_t addr);

int i2c_tx(i2c_t *i2c, uint8_t byte);

int i2c_stop(i2c_t *i2c);

#endif
