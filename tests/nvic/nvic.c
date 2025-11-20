#include <nvic/nvic.h>
#include <common/log/log.h>
#include <timer_basic/timer_basic.h>
#include <addr_map.h>
#include <common.h>


void isr_tim6_dac(void)
{
    ptimer_basic_regs_t TIM6 = (ptimer_basic_regs_t)TIMER_BASIC_6_BASE;

    TIM6->SR = 0;
    nvic_irq_clear_pending(IRQ_TIM6_DAC);
    pr_info("ICPR addr: %x\n", &NVIC->ICPR);
    pr_info("TIM6 IRQ\n");
    for (int i = 0; i < 8; ++i) {
        pr_info("ISPR%u: %x\n", i, NVIC->ISPR[i]);
    }
    //while (1);
}


void main(void)
{
    timer_basic_t timer;
    timer_basic_init(&timer, TIMER_BASIC_6);

    pr_info("NVIC test\n");
    pr_info("Last IRQ num: %d\n", IRQ_FMPI2C1_ERR);

    timer.regs->DIER |= 1; // IRQ en
    nvic_irq_enable(IRQ_TIM6_DAC);

    timer.regs->CR1 |= (1<<3) | (1<<0); // OPM + CEN

    pr_info("No IRQ\n");

    for (int i = 0; i < 8; ++i) {
        pr_info("ISER%u: %x\n", i, NVIC->ISER[i]);
    }
    for (int i = 0; i < 8; ++i) {
        pr_info("ISPR%u: %x\n", i, NVIC->ISPR[i]);
    }

    while (1);
}
