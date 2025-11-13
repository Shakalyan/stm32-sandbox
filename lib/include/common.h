#ifndef _COMMON_H_
#define _COMMON_H_

#include <config.h>

#define BIT(x) ((1<<x))

#define __DMB(notused) {{__asm volatile ("dmb sy" ::: "memory");}}
#define __DSB(notused) {{__asm volatile ("dsb sy" ::: "memory");}}
#define __ISB(notused) {{__asm volatile ("isb sy" ::: "memory");}}

#ifdef CONFIG_SYSCLK_16MHZ
#define SYSCLK_MHZ ((16))
#endif

#endif
