#include <stdint.h>

#define ISR_VECTOR_TABLE_SIZE ((16 + 96))
#define STACK_TOP ((0x20000000U+0x4000U))


extern uint32_t _sdata, _edata, _sbss, _ebss, _etext;

void reset_handler(void);
void main(void);

uint32_t isr_vector[ISR_VECTOR_TABLE_SIZE] __attribute__((section(".isr_vector"))) =
{
    STACK_TOP,
    (uint32_t)&reset_handler
};

void reset_handler(void)
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

    main();
}
