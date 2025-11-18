#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>


typedef volatile struct spi {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SR;
    uint32_t DR;
    uint32_t CRCPR;
    uint32_t RXCRCR;
    uint32_t TXCRCR;
    uint32_t I2SCFGR;
    uint32_t I2SPR;
} spi_t;
typedef volatile spi_t* pspi_t;

typedef enum spi_num {
    SPI1 = 0,
    SPI2,
    SPI3,
    SPI4
} spi_num_t;


void spi_init(pspi_t SPI, spi_num_t num);

uint8_t spi_txrx(pspi_t SPI, uint8_t byte);

void spi_rxb_clear(pspi_t SPI);

void spi_txb_await_empty(pspi_t SPI);


#endif
