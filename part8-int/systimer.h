#ifndef __SYSTIMER_H__
#define __SYSTIMER_H__
#include <stdint.h>

#ifdef RPI2
	#define	SYSTIMER_BASE			0x3F003000UL
#else
	#define	SYSTIMER_BASE			0x20003000UL
#endif
typedef struct
{
	volatile uint32_t control_status;
	volatile uint32_t counter_low;	
	volatile uint32_t counter_high;
    volatile uint32_t compare0;
    volatile uint32_t compare1;
    volatile uint32_t compare2;
    volatile uint32_t compare3;
} systimer_t;

extern systimer_t* GetSystemTimer();
extern void WaitForMicroseconds(uint32_t ms);

#endif