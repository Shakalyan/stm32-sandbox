#ifndef _RCC_H_
#define _RCC_H_

#include <stdint.h>
#include <common.h>
#include <gpio/gpio.h>
#include <uart/uart.h>

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


void rcc_uart_enable(prcc_t RCC, uart_num_t uart_num);

void rcc_gpio_enable(prcc_t RCC, gpio_port_t gpio_num);


#endif
