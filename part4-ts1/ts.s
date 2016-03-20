.globl ts
ts:
_save:
		stmfd	r13!,	{r0-r12, r14}
		mov		r0,		r13
		bl		saveSp

		mrs		r0,		cpsr
		bl		saveCpsr

		mrs		r0,		spsr
		bl		saveSpsr
		

_find:
		bl		reschedule

_resume:
		bl		loadSpsr
		msr 	spsr,	r0

		bl		loadCpsr
		msr 	cpsr,	r0

		bl		loadSp
		mov		r13,	r0

		ldmfd	r13!,	{r0-r12, r15}
