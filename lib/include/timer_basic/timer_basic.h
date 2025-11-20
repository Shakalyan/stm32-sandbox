#ifndef _TIMER_BASIC_H
#define _TIMER_BASIC_H

#include <stdint.h>


typedef volatile struct timer_basic_regs {
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
} timer_basic_regs_t;
typedef volatile timer_basic_regs_t* ptimer_basic_regs_t;

typedef enum timer_basic_num {
    TIMER_BASIC_6 = 0,
    TIMER_BASIC_7
} timer_basic_num_t;

typedef struct timer_basic {
    ptimer_basic_regs_t regs;
    timer_basic_num_t num;
} timer_basic_t;


void timer_basic_init(timer_basic_t *timer, timer_basic_num_t num);


#endif
