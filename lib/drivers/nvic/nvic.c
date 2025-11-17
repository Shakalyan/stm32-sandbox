#include <nvic/nvic.h>
#include <common/log/log.h>
#include <addr_map.h>
#include <common.h>


pnvic_t NVIC = (pnvic_t)NVIC_BASE;


void nvic_irq_enable(IRQ_t irq)
{
    NVIC->ISER[irq/32] = (1<<irq%32);
    __DSB();
    __ISB();
}

void nvic_irq_disable(IRQ_t irq)
{
    NVIC->ICER[irq/32] = (1<<irq%32);
    __DSB();
    __ISB();
}

void nvic_irq_set_pending(IRQ_t irq)
{
    NVIC->ICER[irq/32] = (1<<irq%32);
    __DSB();
    __ISB();
}

void nvic_irq_clear_pending(IRQ_t irq)
{
    NVIC->ICPR[irq/32] = (1<<irq%32);
    __DSB();
    __ISB();
}


void isr_default(void)
{
    pr_debug("IRQ default handler\n");
    while (1);
}
