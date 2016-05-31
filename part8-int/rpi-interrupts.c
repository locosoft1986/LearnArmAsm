#include "rpi-interrupts.h"
#include "gpio.h"
#include "rpi-armtimer.h"

static irq_controller_t* rpiIRQController =
        (irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;



irq_controller_t* GetIrqController(void)
{
    return rpiIRQController;
}        


void DisableAllInterrupt(void)
{
	irq_controller_t* irq_ctrl = GetIrqController();
	irq_ctrl->DISABLE_BASIC_IRQS = 0xffffffff;
	irq_ctrl->DISABLE_IRQS_1 = 0xffffffff;
	irq_ctrl->DISABLE_IRQS_2 = 0xffffffff;
	irq_ctrl->FIQ_CTRL = 0;

	DisableIRQ();
}

void InitVectorTable(void)
{
	extern void* _vector_table_start;
	extern void* _vector_table_end;
	vu32_t *vec = 0;
	vu32_t *p;
	vu32_t *start = (uint32_t *)&_vector_table_start;
	vu32_t *end = (uint32_t *)&_vector_table_end;

	for (p = start; p < end; ++p) {
		*vec = *p;
		++vec;
	}
} 

void __attribute__((interrupt("UNDEF"))) vector_undef_instruction( void )
{

}

void __attribute__((interrupt("SWI"))) vector_swi( void )
{

}

void __attribute__((interrupt("ABORT"))) vector_prefech_abort( void )
{

}

void __attribute__((interrupt("ABORT"))) vector_data_abort( void )
{

}

void __attribute__((interrupt("IRQ"))) vector_interrupt( void )
{
    static int lit = 0;

    /* Clear the ARM Timer interrupt - it's the only interrupt we have
       enabled, so we want don't have to work out which interrupt source
       caused us to interrupt */
    GetArmTimer()->IRQ_CLR = 1;

    /* Flip the LED */
    if( lit )
    {
        LED_OFF();
        lit = 0;
    }
    else
    {
        LED_ON();
        lit = 1;
    }
}


/**
    @brief The FIQ Interrupt Handler

    The FIQ handler can only be allocated to one interrupt source. The FIQ has
    a full CPU shadow register set. Upon entry to this function the CPU
    switches to the shadow register set so that there is no need to save
    registers before using them in the interrupt.

    In C you can't see the difference between the IRQ and the FIQ interrupt
    handlers except for the FIQ knowing it's source of interrupt as there can
    only be one source, but the prologue and epilogue code is quite different.
    It's much faster on the FIQ interrupt handler.

    The prologue is the code that the compiler inserts at the start of the
    function, if you like, think of the opening curly brace of the function as
    being the prologue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers, there's
    nothing we need to save.

    The epilogue is the code that the compiler inserts at the end of the
    function, if you like, think of the closing curly brace of the function as
    being the epilogue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers and so has
    not altered the main set of registers.
*/
void __attribute__((interrupt("FIQ"))) vector_fast_interrupt( void )
{
	while(1) 
	{

	}
}
