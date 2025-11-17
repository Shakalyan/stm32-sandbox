#ifndef _FLASH_H_
#define _FLASH_H_


#include <stdint.h>


typedef volatile struct flash {
    uint32_t ACR;
    uint32_t KEYR;
    uint32_t OPTKEYR;
    uint32_t SR;
    uint32_t CR;
    uint32_t OPTCR;
} flash_t;
typedef volatile flash_t* pflash_t;
extern pflash_t FLASH;


int flash_update_cycles(int new_sysclk_mhz);


#endif
