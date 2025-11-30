#ifndef _COMMON_TIMER_H_
#define _COMMON_TIMER_H_

#include <config.h>

#ifdef CONFIG_COMMON_TIMER
#define AWAIT(event, ms, tof) \
    do {                      \
        int _ms = ms;         \
        tof = 1;              \
        while (_ms--) {       \
            if (event) {      \
                tof = 0;      \
                break;        \
            }                 \
            mdelay(1);        \
        }                     \
    } while (0)
#else
#define AWAIT(event, ms, tof) \
    do {                      \
        while (!(event));     \
        tof = 0;              \
    } while (0)
#endif


void timer_init();

void mdelay(int ms);


#endif
