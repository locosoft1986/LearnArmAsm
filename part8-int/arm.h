#ifndef __ARM_H__
#define __ARM_H__

#define ARM_MODE_USER	0x10
#define ARM_MODE_SYS	0x1f
#define ARM_MODE_FIQ	0x11
#define ARM_MODE_IRQ	0x12
#define ARM_MODE_SVR	0x13
#define ARM_MODE_ABORT	0x17
#define ARM_MODE_UNDEF	0x1B

#define ARM_DISABLE_IRQ	(1 << 7)
#define ARM_DISABLE_FIQ (1 << 6)

#endif