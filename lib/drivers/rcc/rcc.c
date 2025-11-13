#include <rcc/rcc.h>
#include <rcc/rcc_rmap.h>
#include <common.h>
#include <errors.h>


static uint64_t abs(uint64_t x)
{
    return (x < 0) ? -x : x;
}


static uint64_t get_best_sysclk(uint64_t desired_freq, uint64_t vco_in, uint64_t *plln, uint64_t *pllp)
{
    uint64_t n, p, vco_out, curr_freq;
    uint64_t best_sysclk = 0;

    for (n = 50; n < 433; ++n) {
        vco_out = vco_in * n;
        if (vco_out < MHZ_TO_HZ(100)) continue;
        if (vco_out > MHZ_TO_HZ(432)) break;

        for (p = 0; p < 4; ++p) {
            curr_freq = vco_out / (2*(p+1));
            if (abs(desired_freq - curr_freq) < abs(desired_freq - best_sysclk)) {
                best_sysclk = curr_freq;
                *plln = n;
                *pllp = p;
            }
        }
    }

    return best_sysclk;
}


uint64_t rcc_set_sysclk_freq(prcc_t RCC, uint64_t desired_freq)
{
    uint64_t inclk = MHZ_TO_HZ(INCLK_MHZ);
    uint64_t actual_freq = 0, curr_freq;
    uint64_t vco_in;
    uint64_t plln = 0, pllm = 0, pllp = 0, n, m, p;

    if (desired_freq < 0 || desired_freq > MHZ_TO_HZ(180))
        return SYSCLK_FREQ_NOT_SUPPORTED;

#ifdef CONFIG_PLLM_PRESET
    pllm = inclk / MHZ_TO_HZ(2);
    if (pllm < 2 || pllm > 63)
        return INCLK_FREQ_NOT_SUPPORTED;

    vco_in = inclk / pllm;
    actual_freq = get_best_sysclk(desired_freq, vco_in, &plln, &pllp);
#else
    for (m = 2; m < 64; ++m) {
        vco_in = inclk / m;
        if (vco_in > MHZ_TO_HZ(2)) continue;
        if (vco_in < MHZ_TO_HZ(1)) break;

        curr_freq = get_best_sysclk(desired_freq, vco_in, &n, &p);
        if (abs(desired_freq - curr_freq) < abs(desired_freq - actual_freq)) {
            actual_freq = curr_freq;
            plln = n;
            pllp = p;
        }
    }
#endif

    return actual_freq;
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
