#include <common/timer/timer.h>
#include <timer_basic/timer_basic.h>

timer_basic_t timer;

void timer_init()
{
    timer_basic_init(&timer, TIMER_BASIC_6);
}

void mdelay(int ms)
{
    while (ms--) {
        timer.regs->CR1 |= (1<<0); // CEN
        while (!(timer.regs->SR & 1));
        timer.regs->SR = 0;
    }
}

