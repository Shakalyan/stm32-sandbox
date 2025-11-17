#ifndef _NVIC_H_
#define _NVIC_H_


#include <stdint.h>


typedef struct isr_vector_table {
    uint32_t STACK_TOP;
    uint32_t ISR_RESET;
    uint32_t ISR_NMI;
    uint32_t ISR_HARD_FAULT;
    uint32_t ISR_MEM_MANAGE;
    uint32_t ISR_BUS_FAULT;
    uint32_t ISR_USAGE_FAULT;
    uint32_t _reserved0x1c[4];
    uint32_t ISR_SV_CALL;
    uint32_t ISR_DEBUG_MONITOR;
    uint32_t _reserved0x34;
    uint32_t ISR_PEND_SV;
    uint32_t ISR_SYSTICK;
    uint32_t ISR_WWDG;
    uint32_t ISR_PVD;
    uint32_t ISR_TAMP_STAMP;
    uint32_t ISR_RTC_WKUP;
    uint32_t ISR_FLASH;
    uint32_t ISR_RCC;
    uint32_t ISR_EXTI[5];
    uint32_t ISR_DMA1_STREAM[7];
    uint32_t ISR_ADC;
    uint32_t ISR_CAN1_TX;
    uint32_t ISR_CAN1_RX0;
    uint32_t ISR_CAN1_RX1;
    uint32_t ISR_CAN1_SCE;
    uint32_t ISR_EXTI9_5;
    uint32_t ISR_TIM1_BRK_TIM9;
    uint32_t ISR_TIM1_UP_TIM10;
    uint32_t ISR_TIM1_TRG_COM_TIM11;
    uint32_t ISR_TIM1_CC;
    uint32_t ISR_TIM2;
    uint32_t ISR_TIM3;
    uint32_t ISR_TIM4;
    uint32_t ISR_I2C1_EV;
    uint32_t ISR_I2C1_ER;
    uint32_t ISR_I2C2_EV;
    uint32_t ISR_I2C2_ER;
    uint32_t ISR_SPI1;
    uint32_t ISR_SPI2;
    uint32_t ISR_USART1;
    uint32_t ISR_USART2;
    uint32_t ISR_USART3;
    uint32_t ISR_EXTI15_10;
    uint32_t ISR_RTC_ALARM;
    uint32_t ISR_OTG_FS_WKUP;
    uint32_t ISR_TIM8_BRK_TIM12;
    uint32_t ISR_TIM8_UP_TIM13;
    uint32_t ISR_TIM8_TRG_COM_TIM14;
    uint32_t ISR_TIM8_CC;
    uint32_t ISR_DMA1_STREAM7;
    uint32_t ISR_FMC;
    uint32_t ISR_SDIO;
    uint32_t ISR_TIM5;
    uint32_t ISR_SPI3;
    uint32_t ISR_UART4;
    uint32_t ISR_UART5;
    uint32_t ISR_TIM6_DAC;
    uint32_t ISR_TIM7;
    uint32_t ISR_DMA2_STREAM[5];
    uint32_t _reserved0x134[2];
    uint32_t ISR_CAN2_TX;
    uint32_t ISR_CAN2_RX0;
    uint32_t ISR_CAN2_RX1;
    uint32_t ISR_CAN2_SCE;
    uint32_t ISR_OTG_FS;
    uint32_t ISR_DMA2_STREAM5;
    uint32_t ISR_DMA2_STREAM6;
    uint32_t ISR_DMA2_STREAM7;
    uint32_t ISR_USART6;
    uint32_t ISR_I2C3_EV;
    uint32_t ISR_I2C3_ER;
    uint32_t ISR_OTG_HS_EP1_OUT;
    uint32_t ISR_OTG_HS_EP1_IN;
    uint32_t ISR_OTG_HS_WKUP;
    uint32_t ISR_OTG_HS;
    uint32_t ISR_DCMI;
    uint32_t _reserved0x17c[2];
    uint32_t ISR_FPU;
    uint32_t _reserved0x188[2];
    uint32_t ISR_SPI4;
    uint32_t _reserved0x194[2];
    uint32_t ISR_SAI1;
    uint32_t _reserved0x1a0[3];
    uint32_t ISR_SAI2;
    uint32_t ISR_QSPI;
    uint32_t ISR_HDMI_CEC;
    uint32_t ISR_SPDIF_RX;
    uint32_t ISR_FMPI2C1;
    uint32_t ISR_FMPI2C1_ERR;
} isr_vector_table_t;

typedef enum IRQ {
    IRQ_WWDG = 0,
    IRQ_PVD,
    IRQ_TAMP_STAMP,
    IRQ_RTC_WKUP,
    IRQ_FLASH,
    IRQ_RCC,
    IRQ_EXTI0,
    IRQ_EXTI1,
    IRQ_EXTI2,
    IRQ_EXTI3,
    IRQ_EXTI4,
    IRQ_DMA1_STREAM0,
    IRQ_DMA1_STREAM1,
    IRQ_DMA1_STREAM2,
    IRQ_DMA1_STREAM3,
    IRQ_DMA1_STREAM4,
    IRQ_DMA1_STREAM5,
    IRQ_DMA1_STREAM6,
    IRQ_ADC,
    IRQ_CAN1_TX,
    IRQ_CAN1_RX0,
    IRQ_CAN1_RX1,
    IRQ_CAN1_SCE,
    IRQ_EXTI9_5,
    IRQ_TIM1_BRK_TIM9,
    IRQ_TIM1_UP_TIM10,
    IRQ_TIM1_TRG_COM_TIM11,
    IRQ_TIM1_CC,
    IRQ_TIM2,
    IRQ_TIM3,
    IRQ_TIM4,
    IRQ_I2C1_EV,
    IRQ_I2C1_ER,
    IRQ_I2C2_EV,
    IRQ_I2C2_ER,
    IRQ_SPI1,
    IRQ_SPI2,
    IRQ_USART1,
    IRQ_USART2,
    IRQ_USART3,
    IRQ_EXTI15_10,
    IRQ_RTC_ALARM,
    IRQ_OTG_FS_WKUP,
    IRQ_TIM8_BRK_TIM12,
    IRQ_TIM8_UP_TIM13,
    IRQ_TIM8_TRG_COM_TIM14,
    IRQ_TIM8_CC,
    IRQ_DMA1_STREAM7,
    IRQ_FMC,
    IRQ_SDIO,
    IRQ_TIM5,
    IRQ_SPI3,
    IRQ_UART4,
    IRQ_UART5,
    IRQ_TIM6_DAC,
    IRQ_TIM7,
    IRQ_DMA2_STREAM0,
    IRQ_DMA2_STREAM1,
    IRQ_DMA2_STREAM2,
    IRQ_DMA2_STREAM3,
    IRQ_DMA2_STREAM4,
    IRQ_CAN2_TX = 63,
    IRQ_CAN2_RX0,
    IRQ_CAN2_RX1,
    IRQ_CAN2_SCE,
    IRQ_OTG_FS,
    IRQ_DMA2_STREAM5,
    IRQ_DMA2_STREAM6,
    IRQ_DMA2_STREAM7,
    IRQ_USART6,
    IRQ_I2C3_EV,
    IRQ_I2C3_ER,
    IRQ_OTG_HS_EP1_OUT,
    IRQ_OTG_HS_EP1_IN,
    IRQ_OTG_HS_WKUP,
    IRQ_OTG_HS,
    IRQ_DCMI,
    IRQ_FPU = 81,
    IRQ_SPI4 = 84,
    IRQ_SAI1 = 87,
    IRQ_SAI2 = 91,
    IRQ_QSPI,
    IRQ_HDMI_CEC,
    IRQ_SPDIF_RX,
    IRQ_FMPI2C1,
    IRQ_FMPI2C1_ERR,
} IRQ_t;


typedef volatile struct nvic {
    uint32_t _reserved0x000[64];
    uint32_t ISER[8];
    uint32_t _reserved0x120[24];
    uint32_t ICER[8];
    uint32_t _reserved0x1a0[24];
    uint32_t ISPR[8];
    uint32_t _reserved0x220[24];
    uint32_t ICPR[8];
    uint32_t _reserved0x2a0[24];
    uint32_t IABR[8];
    uint32_t _reserved0x320[24];
    uint32_t IPR[60];
    uint32_t _reserved0x4f0[244];
    uint32_t STIR;
} nvic_t;
typedef volatile nvic_t* pnvic_t;
extern pnvic_t NVIC;

void nvic_irq_enable(IRQ_t irq);

void nvic_irq_disable(IRQ_t irq);

void nvic_irq_set_pending(IRQ_t irq);

void nvic_irq_clear_pending(IRQ_t irq);


#define IRQ_HANDLER_ATTRIBUTES __attribute__((weak, interrupt("IRQ")))

void isr_default(void);

void isr_reset(void) IRQ_HANDLER_ATTRIBUTES;

void isr_tim6_dac(void) IRQ_HANDLER_ATTRIBUTES;


#endif
