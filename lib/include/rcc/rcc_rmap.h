#ifndef _RCC_RMAP_H_
#define _RCC_RMAP_H_


#include <stdint.h>


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
        uint32_t DMA2EN : 2;
        uint32_t _RESERVED4 : 6;
        uint32_t OTGHSEN : 1;
        uint32_t OTGHSULPIEN : 1;
        uint32_t _RESERVED5 : 1;
    } bit;

    uint32_t all;

} RCC_AHB1ENR;


#endif
