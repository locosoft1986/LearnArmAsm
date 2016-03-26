.section ".text.startup"

.globl _start
_start:
		ldr 	r13, =running
		ldr		r3,	 =procSize
		add 	r13, r3

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
