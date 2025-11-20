#include <timer_basic/timer_basic.h>
#include <rcc/rcc.h>
#include <addr_map.h>


void timer_basic_init(timer_basic_t *timer, timer_basic_num_t num)
{
    uint32_t apb1_freq_khz = rcc_get_apb1_freq_khz();
    uint32_t addr;

    rcc_timer_basic_enable(num);

    switch (num) {
        case TIMER_BASIC_6:
            addr = TIMER_BASIC_6_BASE;
            break;
        case TIMER_BASIC_7:
            addr = TIMER_BASIC_7_BASE;
            break;
    }

    timer->regs = (ptimer_basic_regs_t)addr;
    timer->num = num;

    timer->regs->CR1 |= (1<<7); // ARPE
    timer->regs->PSC = apb1_freq_khz-1;
    timer->regs->ARR = 1;
}
