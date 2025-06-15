#ifndef _RCC_RMAP_H_
#define _RCC_RMAP_H_


#include <stdint.h>


#define RCC_BASE ((0x40023800))


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

volatile rcc_t *RCC = (volatile rcc_t*)RCC_BASE;


// REGISTERS

typedef union RCC_AHB1ENR
{
    struct
    {
        uint32_t GPIOAEN : 1;
        uint32_t GPIOBEN : 1;
        uint32_t GPIOCEN : 1;
        uint32_t GPIODEN : 1;
        uint32_t GPIOEEN : 1;
        uint32_t GPIOFEN : 1;
        uint32_t GPIOGEN : 1;
        uint32_t GPIOHEN : 1;
        uint32_t _RESERVED1 : 4;
        uint32_t CRCEN : 1;
        uint32_t _RESERVED2 : 5;
        uint32_t BKPSRAMEN : 1;
        uint32_t _RESERVED3 : 2;
        uint32_t DMA1EN : 1;
        uint32_t DMA1EN : 2;
        uint32_t _RESERVED4 : 6;
        uint32_t OTGHSEN : 1;
        uint32_t OTGHSULPIEN : 1;
        uint32_t _RESERVED5 : 1;
    } bit;

    uint32_t all;

} RCC_AHB1ENR;



#endif
