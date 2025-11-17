#include <flash/flash.h>
#include <config.h>
#include <stdint.h>
#include <errors.h>
#include <common.h>
#include <addr_map.h>


pflash_t FLASH = (pflash_t)FLASH_BASE;


static uint32_t get_ws(int sysclk_mhz, int step)
{
    if (sysclk_mhz % step == 0)
        return sysclk_mhz/step - 1;

    return sysclk_mhz/step;
}


static void update_cycles(int sysclk_mhz, int step)
{
    uint32_t ws = get_ws(sysclk_mhz, step);
    uint32_t acr = FLASH->ACR;

    acr &= ~0xF;
    acr |= ws;

    FLASH->ACR = acr;
    acr = FLASH->ACR;
    __DSB();
    __ISB();
}


int flash_update_cycles(int new_sysclk_mhz)
{
    uint32_t ws = 0;

    if (new_sysclk_mhz < 0 || new_sysclk_mhz > 180)
        return SYSCLK_FREQ_NOT_SUPPORTED;

#ifdef CONFIG_VOLTAGE_3_3V
    update_cycles(new_sysclk_mhz, 30);
    return SUCCESS;
#endif

    return VOLTAGE_NOT_SUPPORTED;
}
