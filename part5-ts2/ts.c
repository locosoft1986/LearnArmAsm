#include "ts.h"

volatile PROC 	proc0;
volatile PROC* 	running = &proc0;
volatile uint32_t procSize = sizeof(PROC);

void reschedule()
{
	running = &proc0;
}

void task_switch()
{
    __asm__ __volatile__ (
      "stmfd	sp!,	{r0-r12, lr} \n\t"
      :::"memory"
    );
    __asm__ __volatile__ (
        "mrs    lr,     spsr            \n\t"
        "str    lr,     [%[PREV_SPSR]]  \n\t"
        "mrs    lr,     cpsr            \n\t"
        "str    lr,     [%[PREV_CPSR]]  \n\t"
        "str    sp,     [%[PREV_SP]]    \n\t"
        :
        :[PREV_SPSR] "r" (&running->kSpsr),
            [PREV_CPSR] "r" (&running->kCpsr),
            [PREV_SP]   "r" (&running->kSp)
        :"lr", "memory"
    );
    
    reschedule();
    
    __asm__ __volatile__ (
        "msr    spsr,   %[NEXT_SPSR]    \n\t"
        "msr    cpsr,   %[NEXT_CPSR]    \n\t"
        "ldr    sp,     [%[NEXT_SP]]    \n\t"
        :
        :[NEXT_SPSR] "r" (running->kSpsr),
            [NEXT_CPSR] "r" (running->kCpsr),
            [NEXT_SP]   "r" (&running->kSp)
        :"cc", "memory"
    );
    
    __asm__ __volatile__ (
      "ldmfd	sp!,	{r0-r12, lr} \n\t"
      :::"memory"
    );
}