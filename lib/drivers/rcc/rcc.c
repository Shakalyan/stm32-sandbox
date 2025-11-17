#include <rcc/rcc.h>
#include <common.h>
#include <errors.h>
#include <flash/flash.h>
#include <addr_map.h>


prcc_t RCC = (prcc_t)RCC_BASE;


static uint32_t abs(uint32_t x)
{
    return (x < 0) ? -x : x;
}



static int get_clk_src_base_bit(uint32_t clk)
{
    if (clk == RCC_CFGR_CLK_HSI) return 0;
    if (clk == RCC_CFGR_CLK_HSE) return 16;
    return 24;
}


void rcc_turn_on_clk(uint32_t clk)
{
    int base_bit = get_clk_src_base_bit(clk);

    RCC->CR |= (1<<base_bit);

    while (!(RCC->CR & (1<<(base_bit+1))));
}

void rcc_turn_off_clk(uint32_t clk)
{
    int base_bit = get_clk_src_base_bit(clk);

    RCC->CR &= ~(1<<base_bit);

    while (RCC->CR & (1<<(base_bit+1)));
}


void rcc_switch_sysclk_src(uint32_t src)
{
    uint32_t cfgr;

    rcc_turn_on_clk(src);

    cfgr = RCC->CFGR;
    cfgr &= ~0b11;
    cfgr |= src;
    RCC->CFGR = cfgr;

    while ((RCC->CFGR & (0b11<<2)) != (src<<2));
}


static uint32_t get_best_freq(uint32_t desired_freq_khz, uint32_t vco_in, uint32_t *plln, uint32_t *pllp)
{
    uint32_t n, p, vco_out, curr_freq_khz;
    uint32_t best_freq_khz = 0;

    for (n = 50; n < 433; ++n) {
        vco_out = vco_in * n;
        if (vco_out < MHZ_TO_KHZ(100)) continue;
        if (vco_out > MHZ_TO_KHZ(432)) break;

        for (p = 0; p < 4; ++p) {
            curr_freq_khz = vco_out / (2*(p+1));
            if (abs(desired_freq_khz - curr_freq_khz) < abs(desired_freq_khz - best_freq_khz)) {
                best_freq_khz = curr_freq_khz;
                *plln = n;
                *pllp = p;
                if (best_freq_khz == desired_freq_khz)
                    return best_freq_khz;
            }
        }
    }

    return best_freq_khz;
}


// TODO: PLLQ, PLLR, HSE IN
int rcc_set_pll_freq(uint32_t desired_freq_khz, uint32_t *actual_freq_khz)
{
    uint32_t inclk_khz = MHZ_TO_KHZ(INCLK_MHZ);
    uint32_t curr_freq_khz;
    uint32_t vco_in;
    uint32_t plln = 0, pllm = 0, pllp = 0, n, m, p;
    uint32_t pllcfgr;

    *actual_freq_khz = 0;

    if (desired_freq_khz < 0 || desired_freq_khz > MHZ_TO_KHZ(180))
        return SYSCLK_FREQ_NOT_SUPPORTED;

#ifdef CONFIG_PLLM_PRESET
    pllm = inclk_khz / MHZ_TO_KHZ(2);
    if (pllm < 2 || pllm > 63)
        return INCLK_FREQ_NOT_SUPPORTED;

    vco_in = inclk_khz / pllm;
    *actual_freq_khz = get_best_freq(desired_freq_khz, vco_in, &plln, &pllp);
#else
    for (m = 2; m < 64; ++m) {
        vco_in = inclk_khz / m;
        if (vco_in > MHZ_TO_KHZ(2)) continue;
        if (vco_in < MHZ_TO_KHZ(1)) break;

        curr_freq_khz = get_best_freq(desired_freq_khz, vco_in, &n, &p);
        if (abs(desired_freq_khz - curr_freq_khz) < abs(desired_freq_khz - *actual_freq_khz)) {
            *actual_freq_khz = curr_freq_khz;
            plln = n;
            pllp = p;
            pllm = m;
        }
    }
#endif

    // PLLSRC = ...

    pllcfgr = RCC->PLLCFGR;

    pllcfgr &= ~(0x3F<<0);
    pllcfgr |= (pllm<<0);

    pllcfgr &= ~(0x1FF<<6);
    pllcfgr |= (plln<<6);

    pllcfgr &= ~(0x3<<16);
    pllcfgr |= (pllp<<16);

    RCC->PLLCFGR = pllcfgr;

    return SUCCESS;
}


void rcc_set_apb1_prescale(uint32_t prescale)
{
    uint32_t cfgr;

    cfgr = RCC->CFGR;
    cfgr &= ~(0b111<<10);
    cfgr |= prescale<<10;

    RCC->CFGR = cfgr;
    __DSB();
    __ISB();
    __WAIT_TICKS(16);
}


void rcc_set_apb2_prescale(uint32_t prescale)
{
    uint32_t cfgr;

    cfgr = RCC->CFGR;
    cfgr &= ~(0b111<<13);
    cfgr |= prescale<<13;

    RCC->CFGR = cfgr;
    __DSB();
    __ISB();
    __WAIT_TICKS(16);
}


void rcc_update_prescales(uint32_t new_freq_mhz)
{
    uint32_t prescale, i;

    if (new_freq_mhz <= 45) {
        rcc_set_apb1_prescale(RCC_CFGR_APB_PRESCALE_1);
    }
    else {
        for (i = 0; i < 4; ++i) {
            prescale = 2<<i;
            if (new_freq_mhz / prescale <= 45)
                break;
        }
        rcc_set_apb1_prescale(0b100|i);
    }

    if (new_freq_mhz <= 90) {
        rcc_set_apb2_prescale(RCC_CFGR_APB_PRESCALE_1);
    }
    else {
        for (i = 0; i < 4; ++i) {
            prescale = 2<<i;
            if (new_freq_mhz / prescale <= 90)
                break;
        }
        rcc_set_apb2_prescale(0b100|i);
    }
}


int rcc_init()
{
    uint32_t actual_freq_khz;
    int err;

#ifdef CONFIG_PLL_ON
    rcc_switch_sysclk_src(RCC_CFGR_CLK_HSI);
    rcc_turn_off_clk(RCC_CFGR_CLK_PLL_P);

    err = rcc_set_pll_freq(MHZ_TO_KHZ(SYSCLK_MHZ), &actual_freq_khz);
    if (err != SUCCESS) {
        return err;
    }

    err = flash_update_cycles(KHZ_TO_MHZ(actual_freq_khz));
    if (err != SUCCESS)
        return err;

    rcc_update_prescales(KHZ_TO_MHZ(actual_freq_khz));

    rcc_switch_sysclk_src(RCC_CFGR_CLK_PLL_P);
#endif

    return SUCCESS;
}


uint32_t rcc_get_sysclk_freq_khz()
{
    uint32_t plln, pllm, pllp, pllr;
    uint32_t clk_src = (RCC->CFGR & 0b11<<2)>>2;

    if (clk_src == RCC_CFGR_CLK_HSI ||
        clk_src == RCC_CFGR_CLK_HSE)
        return MHZ_TO_KHZ(INCLK_MHZ);


    pllm = RCC->PLLCFGR & (0x3F<<0);
    plln = (RCC->PLLCFGR & (0x1FF<<6))>>6;

    if (clk_src == RCC_CFGR_CLK_PLL_P) {
        pllp = (RCC->PLLCFGR & (0x3<<16))>>16;

        return (MHZ_TO_KHZ(INCLK_MHZ)*plln) / (pllm*(2*(pllp+1)));
    }

    pllr = (RCC->PLLCFGR & (0x3<<28))>>28;
    return (MHZ_TO_KHZ(INCLK_MHZ)*plln) / (pllm*pllr);
}


uint32_t rcc_get_apb1_freq_khz()
{
    uint32_t sysclk_freq = rcc_get_sysclk_freq_khz();
    uint32_t ppre1 = (RCC->CFGR & (0b111<<10))>>10;
    if ((ppre1 & 0b100) == 0)
        return sysclk_freq;
    return sysclk_freq / (2<<(ppre1&0b11));
}


uint32_t rcc_get_apb2_freq_khz()
{
    uint32_t sysclk_freq = rcc_get_sysclk_freq_khz();
    uint32_t ppre2 = (RCC->CFGR & (0b111<<13))>>13;
    if ((ppre2 & 0b100) == 0)
        return sysclk_freq;
    return sysclk_freq / (2<<(ppre2&0b11));
}


void rcc_uart_enable(uart_num_t uart_num)
{
    if (uart_num == 1) {
        RCC->APB2ENR |= 1<<4;
    }
    else if (uart_num == 6) {
        RCC->APB2ENR |= 1<<5;
        return;
    }
    else {
        RCC->APB1ENR |= 1<<(17+(uart_num-2));
    }
    __DSB();
    __ISB();
}


void rcc_gpio_enable(gpio_port_t gpio_num)
{
    RCC->AHB1ENR |= 1<<gpio_num;
    __DSB();
    __ISB();
}


void rcc_timer_basic_enable(timer_basic_num_t num)
{
    RCC->APB1ENR |= (1<<(4+num));
    __DSB();
    __ISB();
}


void rcc_spi_enable(spi_num_t spi_num)
{
    switch (spi_num) {
        case SPI1:
            RCC->APB2ENR |= (1<<12);
            break;
        case SPI2:
            RCC->APB1ENR |= (1<<14);
            break;
        case SPI3:
            RCC->APB1ENR |= (1<<15);
            break;
        case SPI4:
            RCC->APB2ENR |= (1<<13);
            break;
    }
    __DSB();
    __ISB();
}
