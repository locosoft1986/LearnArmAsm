#include "ts.h"

volatile PROC 	proc0;
volatile PROC* 	running = &proc0;
volatile uint32_t procSize = sizeof(PROC);

void reschedule()
{
	running = &proc0;
}

void saveCpsr(uint32_t val)
{
	running->kCpsr = val;
}

uint32_t loadCpsr()
{
	return running->kCpsr;
}

void saveSpsr(uint32_t val)
{
	running->kSpsr = val;
}

uint32_t loadSpsr()
{
	return running->kSpsr;
}

void saveSp(uint32_t val)
{
	running->kSp = val;
}

uint32_t loadSp()
{
	return running->kSp;
}