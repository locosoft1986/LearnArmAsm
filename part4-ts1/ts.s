.globl ts
ts:
_save:
		stmfd	r13!,	{r0-r12, r14}
		ldr		r14, 	=running
		mrs		r0,		cpsr
		mrs		r1,		spsr
		str		r13,	[r14, #4]
		str		r0,		[r14, #8]
		str		r1,		[r14, #12]

_find:
		bl		reschedule

_resume:
		ldr		r14, 	=running
		ldr		r1,		[r14, #12]
		ldr		r0,		[r14, #8]
		ldr		r13,	[r14, #4]
		msr		spsr,	r1		
		msr 	cpsr,	r0
		ldmfd	r13!,	{r0-r12, r15}
