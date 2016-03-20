#include "ts.h"

PROC 	proc0;
PROC* 	running = &proc0;
volatile uint32_t procSize = sizeof(PROC);


void reschedule()
{
	running = &proc0;
}