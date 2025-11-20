//#include <timer_basic/timer_basic.h>
#include <common/timer/timer.h>
#include <common/log/log.h>
#include <addr_map.h>


void main(void)
{
    // timer_basic_t timer;
    // timer_basic_init(&timer, TIMER_BASIC_6);

    while (1) {
        mdelay(3000);
        pr_info("3 seconds...\n");
    }

}
