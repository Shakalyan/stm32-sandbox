#include <timer_basic/timer_basic.h>
#include <rcc/rcc.h>
#include <addr_map.h>


void timer_basic_init(ptimer_basic_t TIMER, timer_basic_num_t num)
{
    uint32_t apb1_freq_khz = rcc_get_apb1_freq_khz();

    rcc_timer_basic_enable(num);

    TIMER->CR1 |= (1<<7); // ARPE
    TIMER->PSC = apb1_freq_khz-1;
    TIMER->ARR = 1;
}

void mdelay(ptimer_basic_t TIMER, int ms)
{
    while (ms--) {
        TIMER->CR1 |= (1<<0); // CEN
        while (!(TIMER->SR & 1));
        TIMER->SR = 0;
    }
}
