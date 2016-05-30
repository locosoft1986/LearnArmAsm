#ifndef __RPI_PERIPHERALS_H__
#define __RPI_PERIPHERALS_H__

#include "types.h"

typedef struct {
    vu32_t IRQ;
    vu32_t ENABLES;

    vu32_t reserved1[((0x40 - 0x04) / 4) - 1];

    vu32_t MU_IO;
    vu32_t MU_IER;
    vu32_t MU_IIR;
    vu32_t MU_LCR;
    vu32_t MU_MCR;
    vu32_t MU_LSR;
    vu32_t MU_MSR;
    vu32_t MU_SCRATCH;
    vu32_t MU_CNTL;
    vu32_t MU_STAT;
    vu32_t MU_BAUD;

    vu32_t reserved2[(0x80 - 0x68) / 4 - 1];

    vu32_t SPI0_CNTL0;
    vu32_t SPI0_CNTL1;
    vu32_t SPI0_STAT;
    vu32_t SPI0_IO;
    vu32_t SPI0_PEEK;

    vu32_t reserved3[(0xC0 - 0x94) / 4 - 1];

    vu32_t SPI1_CNTL0;
    vu32_t SPI1_CNTL1;
    vu32_t SPI1_STAT;
    vu32_t SPI1_IO;
    vu32_t SPI1_PEEK;
} aux_t;

typedef struct
{
	vu32_t IRQ_BASIC_PENDING;
	vu32_t IRQ_PENDING_1;
	vu32_t IRQ_PENDING_2;
	vu32_t FIQ_CTRL;
	vu32_t ENABLE_IRQS_1;
	vu32_t ENABLE_IRQS_2;
	vu32_t ENABLE_BASIC_IRQS;
	vu32_t DISABLE_IRQS_1;
	vu32_t DISABLE_IRQS_2;
	vu32_t DISABLE_BASIC_IRQS;
} irq_controller_t;

typedef struct
{
	vu32_t LOAD;
	vu32_t VALUE;
	vu32_t CONTROL;
	vu32_t IRQ_CLR;
	vu32_t RAW_IRQ;
	vu32_t MASKED_IRQ;
	vu32_t RELOAD;
	vu32_t PREDIVIDER;
	vu32_t FREECOUNTER;
} armtimer_t;

typedef struct
{
	vu32_t control_status;
	vu32_t counter_low;	
	vu32_t counter_high;
    vu32_t compare0;
    vu32_t compare1;
    vu32_t compare2;
    vu32_t compare3;
} systimer_t;

#endif