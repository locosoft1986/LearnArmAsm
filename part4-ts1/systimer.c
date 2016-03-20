#include "systimer.h"

static systimer_t* rpiSysTimer = (systimer_t*)SYSTIMER_BASE;

systimer_t* GetSystemTimer()
{
	return rpiSysTimer;
}

void WaitForMicroseconds(uint32_t ms)
{
	volatile uint32_t ts = rpiSysTimer->counter_low;

	while((rpiSysTimer->counter_low - ts) < ms * 1000) {}
}