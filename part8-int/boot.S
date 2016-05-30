#include "config.h"
#include "arm.h"

.section ".text.startup"

.globl _start
_start:
		mov r3, #(ARM_MODE_IRQ | ARM_DISABLE_IRQ | ARM_DISABLE_FIQ)
		msr cpsr, r3
		mov sp, #(PA_IRQ_STACK)

		mov r3, #(ARM_MODE_SVR | ARM_DISABLE_IRQ | ARM_DISABLE_FIQ)
		msr cpsr, r3
		mov sp, #(PA_KERNEL_STACK)

		ldr		r4, =__bss_start__
		ldr		r9, =__bss_end__
		mov		r5, #0
		mov		r6, #0
		mov		r7, #0
		mov		r8, #0
		b  		is_done
loop:
		stmia	r4!, {r5-r8}
is_done:
		cmp 	r4, r9
		blo  	loop
		bl 		cmain

inf_loop:
		b inf_loop

.global _vector_table_start
.global _vector_table_end
_vector_table_start:
		ldr pc, _reset_h_
		ldr pc, _undefine_instruction_h_
		ldr pc, _software_interrupt_h_
		ldr pc, _prefetch_abort_h_
		ldr pc, _data_abort_h_
		ldr pc, _reserved_h_
		ldr pc, _interrupt_h_
		ldr pc, _fast_interrupt_h_

_reset_h_:					.word _start
_undefine_instruction_h_:	.word vector_undef_instruction
_software_interrupt_h_:		.word vector_swi
_prefetch_abort_h_:			.word vector_prefech_abort
_data_abort_h_:				.word vector_data_abort
_reserved_h_:				.word _start
_interrupt_h_:				.word vector_interrupt
_fast_interrupt_h_:			.word vector_fast_interrupt

_vector_table_end:
		mov r0, r0			//nop, to fill the ARM pipeline


.global EnableIRQ
EnableIRQ:
	mrs	r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c,r0
	mov pc, lr


.global DisableIRQ
DisableIRQ:
	mrs	r0, cpsr
	orr	r0, r0, #0x80
	msr	cpsr_c, r0
	mov pc, lr
