#include <timer_basic/timer_basic.h>
#include <common/log/log.h>
#include <addr_map.h>


void main(void)
{
    ptimer_basic_t TIMER = (ptimer_basic_t)TIMER_BASIC_6_BASE;
    timer_basic_init(TIMER, TIMER_BASIC_6);

    while (1) {
        mdelay(TIMER, 3000);
        pr_info("3 seconds...\n");
    }

}
