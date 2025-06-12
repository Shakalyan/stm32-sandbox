#include <stdint.h>


#define RCC_BASE ((0x40023800))
#define RCC_AHB1_REG (*((volatile uint32_t*)(RCC_BASE + 0x30)))

#define GPIOA_BASE ((0x40020000))
#define GPIOA_MODER_REG (*((volatile uint32_t*)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR_REG (*((volatile uint32_t*)(GPIOA_BASE + 0x14)))

#define LED ((6))

void main(void)
{
    RCC_AHB1_REG |= (1 << 0);

    volatile uint32_t dummy;
    dummy = RCC_AHB1_REG;
    dummy = RCC_AHB1_REG;

    GPIOA_MODER_REG |= (1 << (LED*2));

    while (1)
    {
        GPIOA_ODR_REG ^= (1 << LED);
        for (uint32_t i = 0; i < 1000000; i++);
    }

}
