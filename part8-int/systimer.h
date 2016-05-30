#ifndef __SYSTIMER_H__
#define __SYSTIMER_H__
#include "rpi-peripherals.h"
#include "rpi-base.h"

#ifdef RPI2
	#define	SYSTIMER_BASE			(DEVICE_BASE + 0x00003000UL)
#else
	#define	SYSTIMER_BASE			(DEVICE_BASE + 0x00003000UL)
#endif


extern systimer_t* GetSystemTimer();
extern void WaitForMicroseconds(uint32_t ms);

#endif