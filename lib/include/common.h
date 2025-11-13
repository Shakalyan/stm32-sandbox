#ifndef _COMMON_H_
#define _COMMON_H_


#include <config.h>

#define BIT(x) ((1<<x))
#define MHZ_TO_KHZ(f) ((f*1000))

#define __DMB(notused) {{__asm volatile ("dmb sy" ::: "memory");}}
#define __DSB(notused) {{__asm volatile ("dsb sy" ::: "memory");}}
#define __ISB(notused) {{__asm volatile ("isb sy" ::: "memory");}}


#ifndef CONFIG_PLL_ON
#define SYSCLK_MHZ ((16))
#else
#define SYSCLK_MHZ CONFIG_SYSCLK_MHZ
#endif


#ifndef INCLK_MHZ
#define INCLK_MHZ ((16))
#endif


#endif
