#ifndef __RPI_INTERRUPTS_H__
#define __RPI_INTERRUPTS_H__

#include "rpi-base.h"
#include "rpi-peripherals.h"

/** @brief See Section 7.5 of the BCM2836 ARM Peripherals documentation, the base
    address of the controller is actually xxxxB000, but there is a 0x200 offset
    to the first addressable register for the interrupt controller, so offset the
    base to the first register */
#define RPI_INTERRUPT_CONTROLLER_BASE   ( DEVICE_BASE + 0xB200 )

/** @brief Bits in the Enable_Basic_IRQs register to enable various interrupts.
    See the BCM2835 ARM Peripherals manual, section 7.5 */
#define RPI_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define RPI_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define RPI_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define RPI_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define RPI_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define RPI_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define RPI_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define RPI_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)
#define RPI_BASIC_PENDING_REG_1_SET	    (1 << 8)
#define RPI_BASIC_PENDING_REG_2_SET	    (1 << 9)

#define RPI_BASIC_GPU_IRQ_7			    (1 << 10)
#define RPI_BASIC_GPU_IRQ_9			    (1 << 11)
#define RPI_BASIC_GPU_IRQ_10		    (1 << 12)
#define RPI_BASIC_GPU_IRQ_18		    (1 << 13)
#define RPI_BASIC_GPU_IRQ_19		    (1 << 14)
#define RPI_BASIC_GPU_IRQ_53		    (1 << 15)
#define RPI_BASIC_GPU_IRQ_54		    (1 << 16)
#define RPI_BASIC_GPU_IRQ_55		    (1 << 17)
#define RPI_BASIC_GPU_IRQ_56		    (1 << 18)
#define RPI_BASIC_GPU_IRQ_57		    (1 << 19)
#define RPI_BASIC_GPU_IRQ_62		    (1 << 20)

#define RPI_FIQ_CTRL_ENABLE				(0x80)


extern irq_controller_t* GetIrqController(void);   

extern void DisableAllInterrupt(void);
extern void InitVectorTable(void); 

/* from boot.S */
extern void EnableIRQ(void);
extern void DisableIRQ(void);

#endif