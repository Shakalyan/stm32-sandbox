#include <rcc/rcc.h>
#include <rcc/rcc_rmap.h>
#include <common.h>
#include <errors.h>


static uint32_t abs(uint32_t x)
{
    return (x < 0) ? -x : x;
}


static uint32_t get_best_sysclk(uint32_t desired_freq_khz, uint32_t vco_in, uint32_t *plln, uint32_t *pllp)
{
    uint32_t n, p, vco_out, curr_freq_khz;
    uint32_t best_sysclk_khz = 0;

    for (n = 50; n < 433; ++n) {
        vco_out = vco_in * n;
        if (vco_out < MHZ_TO_KHZ(100)) continue;
        if (vco_out > MHZ_TO_KHZ(432)) break;

        for (p = 0; p < 4; ++p) {
            curr_freq_khz = vco_out / (2*(p+1));
            if (abs(desired_freq_khz - curr_freq_khz) < abs(desired_freq_khz - best_sysclk_khz)) {
                best_sysclk_khz = curr_freq_khz;
                *plln = n;
                *pllp = p;
                if (best_sysclk_khz == desired_freq_khz)
                    return best_sysclk_khz;
            }
        }
    }

    return best_sysclk_khz;
}


uint32_t rcc_set_sysclk_freq(prcc_t RCC, uint32_t desired_freq_khz)
{
    uint32_t inclk_khz = MHZ_TO_KHZ(INCLK_MHZ);
    uint32_t actual_freq_khz = 0, curr_freq_khz;
    uint32_t vco_in;
    uint32_t plln = 0, pllm = 0, pllp = 0, n, m, p;

    if (desired_freq_khz < 0 || desired_freq_khz > MHZ_TO_KHZ(180))
        return SYSCLK_FREQ_NOT_SUPPORTED;

#ifdef CONFIG_PLLM_PRESET
    pllm = inclk_khz / MHZ_TO_KHZ(2);
    if (pllm < 2 || pllm > 63)
        return INCLK_FREQ_NOT_SUPPORTED;

    vco_in = inclk_khz / pllm;
    actual_freq_khz = get_best_sysclk(desired_freq_khz, vco_in, &plln, &pllp);
#else
    for (m = 2; m < 64; ++m) {
        vco_in = inclk_khz / m;
        if (vco_in > MHZ_TO_KHZ(2)) continue;
        if (vco_in < MHZ_TO_KHZ(1)) break;

        curr_freq_khz = get_best_sysclk(desired_freq_khz, vco_in, &n, &p);
        if (abs(desired_freq_khz - curr_freq_khz) < abs(desired_freq_khz - actual_freq_khz)) {
            actual_freq_khz = curr_freq_khz;
            plln = n;
            pllp = p;
        }
    }
#endif

    return actual_freq_khz;
}


int rcc_init(prcc_t RCC)
{
    return 0;
}


void rcc_uart_enable(prcc_t RCC, uart_num_t uart_num)
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


void rcc_gpio_enable(prcc_t RCC, gpio_port_t gpio_num)
{
    RCC->AHB1ENR |= 1<<gpio_num;
    __DSB();
    __ISB();
}
