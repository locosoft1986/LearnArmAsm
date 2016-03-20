#ifndef __TS_H__
#define __TS_H__

#include <stdint.h>

#define K_STACK_SIZE	(2048 * 1024)
typedef struct proc {
	struct 	 proc* 	  next;
	volatile uint32_t kSp;
	volatile uint32_t kCpsr;
	volatile uint32_t kSpsr;
	volatile uint32_t stack[K_STACK_SIZE];
} PROC;

extern PROC* running;

extern void reschedule();

extern void ts();

#endif