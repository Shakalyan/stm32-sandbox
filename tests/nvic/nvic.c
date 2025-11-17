#include <nvic/nvic.h>
#include <common/log/log.h>
#include <timer_basic/timer_basic.h>
#include <addr_map.h>
#include <common.h>


void isr_tim6_dac(void)
{
    nvic_irq_clear_pending(IRQ_TIM6_DAC);
    pr_info("TIM6 IRQ\n");
    for (int i = 0; i < 8; ++i) {
        pr_info("ISPR%u: %x\n", i, NVIC->ISPR[i]);
    }
    while (1);
}


void main(void)
{

    ptimer_basic_t TIM6 = (ptimer_basic_t)TIMER_BASIC_6_BASE;
    timer_basic_init(TIM6, TIMER_BASIC_6);

    pr_info("NVIC test\n");
    pr_info("Last IRQ num: %d\n", IRQ_FMPI2C1_ERR);

    TIM6->DIER |= 1; // IRQ en
    nvic_irq_enable(IRQ_TIM6_DAC);

    TIM6->CR1 |= (1<<0); // CEN

    pr_info("No IRQ\n");

    for (int i = 0; i < 8; ++i) {
        pr_info("ISER%u: %x\n", i, NVIC->ISER[i]);
    }
    for (int i = 0; i < 8; ++i) {
        pr_info("ISPR%u: %x\n", i, NVIC->ISPR[i]);
    }

    while (1);
}
