#include <stdint.h>
#include <nvic/nvic.h>
#include <config.h>

#define STACK_TOP_ADDR ((0x20000000U+0x4000U))

extern uint32_t _sdata, _edata, _sbss, _ebss, _etext;
void run_test(void);


#ifdef CONFIG_DRIVER_NVIC
    isr_vector_table_t isr_vector_table __attribute__((section(".isr_vector"))) =
    {
        .STACK_TOP = STACK_TOP_ADDR,
        .ISR_RESET = (uint32_t)isr_reset,
        .ISR_TIM6_DAC = (uint32_t)isr_tim6_dac
    };
#else

#define ISR_VECTOR_TABLE_SIZE ((16 + 96))
    uint32_t isr_vector[ISR_VECTOR_TABLE_SIZE] __attribute__((section(".isr_vector"))) =
    {
        STACK_TOP_ADDR,
        (uint32_t)isr_reset
    };

    void isr_default(void)
    {
        while (1);
    }
#endif

void isr_reset(void)
{
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *flash_data = (uint8_t*)&_etext;
    uint8_t *sram_data = (uint8_t*)&_sdata;

    uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint8_t *bss = (uint8_t*)&_sbss;

    uint32_t i = 0;

    for (i = 0; i < data_size; ++i)
        sram_data[i] = flash_data[i];

    for (i = 0; i < bss_size; ++i)
        bss[i] = 0;

    run_test();
}
