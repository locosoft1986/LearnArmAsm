#ifndef __RPI_ARMTIMER_H__
#define __RPI_ARMTIMER_H__

#include "rpi-peripherals.h"
#include "rpi-base.h"

#define RPI_ARMTIMER_BASE               ( DEVICE_BASE + 0xB400 )

/** @brief 0 : 16-bit counters - 1 : 32-bit counter */
#define RPI_ARMTIMER_CTRL_32BIT         ( 1 << 1 )

#define RPI_ARMTIMER_CTRL_PRESCALE_1    ( 0 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_16   ( 1 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_256  ( 2 << 2 )

/** @brief 0 : Timer interrupt disabled - 1 : Timer interrupt enabled */
#define RPI_ARMTIMER_CTRL_INT_ENABLE    ( 1 << 5 )
#define RPI_ARMTIMER_CTRL_INT_DISABLE   ( 0 << 5 )

/** @brief 0 : Timer disabled - 1 : Timer enabled */
#define RPI_ARMTIMER_CTRL_ENABLE        ( 1 << 7 )
#define RPI_ARMTIMER_CTRL_DISABLE       ( 0 << 7 )

extern armtimer_t* GetArmTimer( void );

#endif