#include "ts.h"
#include "gpio.h"
#include "systimer.h"

//GPIO Register set
volatile unsigned int* gpio;

volatile PROC 	proc[NPROC];
volatile PROC* 	running;
volatile uint32_t procSize = sizeof(PROC);

void body0()  __attribute__((naked));
void body0() 
{
    int c = 0;
    while(1)
    {
        c = 0;
        while(c++ < 3)
        {
            LED_ON();
            WaitForMicroseconds(500);
            LED_OFF();
            WaitForMicroseconds(500);
        }
        task_switch(); 
        c = 0;
        while(c++ < 4)
        {
            LED_ON();
            WaitForMicroseconds(100);
            LED_OFF();
            WaitForMicroseconds(100);
        }      
    }
}

void body1()  __attribute__((naked));
void body1()
{
    int c = 0;
    while(1)
    {
        c = 0;
        while(c++ < 3)
        {
            LED_ON();
            WaitForMicroseconds(3000);
            LED_OFF();
            WaitForMicroseconds(500);
        }
        task_switch();  
        c = 0;
        while(c++ < 6)
        {
            LED_ON();
            WaitForMicroseconds(200);
            LED_OFF();
            WaitForMicroseconds(1000);
        }      
    } 
}

void init()
{
    gpio = (unsigned int*) GPIO_BASE;

    gpio[LED_GPFSEL] |= (1 << LED_GPFBIT);

    volatile PROC* p;
    int i, j;
    int nextId;
    for(i = 0; i < NPROC; ++i)
    {
        p = &proc[i];
        p->pid = i;
        nextId = i + 1;
        if(nextId >= NPROC)
        {
            nextId = 0;
        }
        p->next = &proc[nextId];
        
        if(i > 0) 
        {
            for(j = 1; j < 15; ++j) 
            {
                p->stack[K_STACK_SIZE - j] = 0;
            }
            
            p->stack[K_STACK_SIZE - 1] = (i % 2) ? ((uint32_t)body0) : ((uint32_t)body1);
            p->kSp = &(p->stack[K_STACK_SIZE - 14]);
        }
    }
    running = &proc[0];
}

void reschedule()
{
	running = running->next;
}

void task_switch() __attribute__((naked));
void task_switch()
{
    __asm__ __volatile__ (
      "stmfd	sp!,	{lr} \n\t"
      :::"memory"
    );
    __asm__ __volatile__ (
      "stmfd	sp!,	{r0-r12} \n\t"
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
      "ldmfd	sp!,	{r0-r12} \n\t"
      :::"memory"
    );
    __asm__ __volatile__ (
      "ldmfd	sp!,	{pc} \n\t"
      :::"memory"
    );
}