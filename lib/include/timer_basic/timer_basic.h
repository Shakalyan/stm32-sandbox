#ifndef _TIMER_BASIC_H
#define _TIMER_BASIC_H

#include <stdint.h>


typedef volatile struct timer_basic {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t _reserved0x08;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t _reserved0x18[3];
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
} timer_basic_t;
typedef volatile timer_basic_t* ptimer_basic_t;

typedef enum timer_basic_num {
    TIMER_BASIC_6 = 0,
    TIMER_BASIC_7
} timer_basic_num_t;


void timer_basic_init(ptimer_basic_t TIMER, timer_basic_num_t num);

void mdelay(ptimer_basic_t TIMER, int ms);


#endif
