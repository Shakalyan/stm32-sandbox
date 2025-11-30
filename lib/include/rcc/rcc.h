#ifndef _RCC_H_
#define _RCC_H_

#include <stdint.h>
#include <common.h>
#include <gpio/gpio.h>
#include <uart/uart.h>
#include <timer_basic/timer_basic.h>
#include <spi/spi.h>
#include <i2c/i2c.h>


#define RCC_CFGR_CLK_HSI   ((0b00))
#define RCC_CFGR_CLK_HSE   ((0b01))
#define RCC_CFGR_CLK_PLL_P ((0b10))
#define RCC_CFGR_CLK_PLL_R ((0b11))

#define RCC_CFGR_APB_PRESCALE_1  ((0b000))
#define RCC_CFGR_APB_PRESCALE_2  ((0b100))
#define RCC_CFGR_APB_PRESCALE_4  ((0b101))
#define RCC_CFGR_APB_PRESCALE_8  ((0b110))
#define RCC_CFGR_APB_PRESCALE_16 ((0b111))


typedef volatile struct rcc
{
    uint32_t CR;
    uint32_t PLLCFGR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t AHB1RSTR;
    uint32_t AHB2RSTR;
    uint32_t AHB3RSTR;
    uint32_t _RESERVED1;
    uint32_t APB1RSTR;
    uint32_t APB2RSTR;
    uint32_t _RESERVED2;
    uint32_t _RESERVED3;
    uint32_t AHB1ENR;
    uint32_t AHB2ENR;
    uint32_t AHB3ENR;
    uint32_t _RESERVED4;
    uint32_t APB1ENR;
    uint32_t APB2ENR;
    uint32_t _RESERVED5;
    uint32_t _RESERVED6;
    uint32_t AHB1LPENR;
    uint32_t AHB2LPENR;
    uint32_t AHB3LPENR;
    uint32_t _RESERVED7;
    uint32_t APB1LPENR;
    uint32_t APB2LPENR;
    uint32_t _RESERVED8;
    uint32_t _RESERVED9;
    uint32_t BDCR;
    uint32_t CSR;
    uint32_t _RESERVED10;
    uint32_t _RESERVED11;
    uint32_t SSCGR;
    uint32_t PLLI2SCFGR;
    uint32_t PLLSAICFGR;
    uint32_t DCKCFGR;
    uint32_t CKGATENR;
    uint32_t DCKCFGR2;
} rcc_t;
typedef volatile rcc_t* prcc_t;
extern prcc_t RCC;


int rcc_init();

int rcc_set_pll_freq(uint32_t desired_freq_khz, uint32_t *actual_freq_khz);

void rcc_switch_sysclk_src(uint32_t src);

void rcc_turn_on_clk(uint32_t clk);

void rcc_turn_off_clk(uint32_t clk);

void rcc_update_prescales(uint32_t new_freq_mhz);

void rcc_set_apb1_prescale(uint32_t prescale);

void rcc_set_apb2_prescale(uint32_t prescale);

void rcc_uart_enable(uart_num_t uart_num);

void rcc_gpio_enable(gpio_port_t gpio_num);

void rcc_spi_enable(spi_num_t spi_num);

void rcc_timer_basic_enable(timer_basic_num_t num);

void rcc_i2c_enable(i2c_num_t num);

uint32_t rcc_get_sysclk_freq_khz();

uint32_t rcc_get_apb1_freq_khz();

uint32_t rcc_get_apb2_freq_khz();


#endif
