#ifndef __GPIO_H__
#define __GPIO_H__
#include "types.h"

#include "rpi-base.h"


typedef enum {
    FS_INPUT = 0,
    FS_OUTPUT,
    FS_ALT5,
    FS_ALT4,
    FS_ALT0,
    FS_ALT1,
    FS_ALT2,
    FS_ALT3,
    } rpi_gpio_alt_function_t;

/* A mask to be able to clear the bits in the register before setting the
   value we require */
#define FS_MASK     (7)

typedef enum {
    GPIO0 = 0,
    GPIO1,
    GPIO2,
    GPIO3,
    GPIO4,
    GPIO5,
    GPIO6,
    GPIO7,
    GPIO8,
    GPIO9,
    GPIO10 = 10,
    GPIO11,
    GPIO12,
    GPIO13,
    GPIO14,
    GPIO15,
    GPIO16,
    GPIO17,
    GPIO18,
    GPIO19,
    GPIO20 = 20,
    GPIO21,
    GPIO22,
    GPIO23,
    GPIO24,
    GPIO25,
    GPIO26,
    GPIO27,
    GPIO28,
    GPIO29,
    GPIO30 = 30,
    GPIO31,
    GPIO32,
    GPIO33,
    GPIO34,
    GPIO35,
    GPIO36,
    GPIO37,
    GPIO38,
    GPIO39,
    GPIO40 = 40,
    GPIO41,
    GPIO42,
    GPIO43,
    GPIO44,
    GPIO45,
    GPIO46,
    GPIO47,
    GPIO48,
    GPIO49,
    GPIO50 = 50,
    GPIO51,
    GPIO52,
    GPIO53,
} rpi_gpio_pin_t;


/** The GPIO Peripheral is described in section 6 of the BCM2835 Peripherals
    documentation.

    There are 54 general-purpose I/O (GPIO) lines split into two banks. All
    GPIO pins have at least two alternative functions within BCM. The
    alternate functions are usually peripheral IO and a single peripheral
    may appear in each bank to allow flexibility on the choice of IO voltage.
    Details of alternative functions are given in section 6.2. Alternative
    Function Assignments.

    The GPIO peripheral has three dedicated interrupt lines. These lines are
    triggered by the setting of bits in the event detect status register. Each
    bank has its’ own interrupt line with the third line shared between all
    bits.

    The Alternate function table also has the pull state (pull-up/pull-down)
    which is applied after a power down. */
typedef struct {
    vu32_t          GPFSEL0;
    vu32_t          GPFSEL1;
    vu32_t          GPFSEL2;
    vu32_t          GPFSEL3;
    vu32_t          GPFSEL4;
    vu32_t          GPFSEL5;
    const_vu32_t    Reserved0;
    vu32_t          GPSET0;
    vu32_t          GPSET1;
    const_vu32_t    Reserved1;
    vu32_t          GPCLR0;
    vu32_t          GPCLR1;
    const_vu32_t    Reserved2;
    vu32_t          GPLEV0;
    vu32_t          GPLEV1;
    const_vu32_t    Reserved3;
    vu32_t          GPEDS0;
    vu32_t          GPEDS1;
    const_vu32_t    Reserved4;
    vu32_t          GPREN0;
    vu32_t          GPREN1;
    const_vu32_t    Reserved5;
    vu32_t          GPFEN0;
    vu32_t          GPFEN1;
    const_vu32_t    Reserved6;
    vu32_t          GPHEN0;
    vu32_t          GPHEN1;
    const_vu32_t    Reserved7;
    vu32_t          GPLEN0;
    vu32_t          GPLEN1;
    const_vu32_t    Reserved8;
    vu32_t          GPAREN0;
    vu32_t          GPAREN1;
    const_vu32_t    Reserved9;
    vu32_t          GPAFEN0;
    vu32_t          GPAFEN1;
    const_vu32_t    Reserved10;
    vu32_t          GPPUD;
    vu32_t          GPPUDCLK0;
    vu32_t          GPPUDCLK1;
    const_vu32_t    Reserved11;
} rpi_gpio_t;



#if defined(RPIPLUS) || defined(RPI2)
  #define LED_GPFSEL    GetGpio()->GPFSEL4
  #define LED_GPFBIT    21
  #define LED_GPSET     GetGpio()->GPSET1
  #define LED_GPCLR     GetGpio()->GPCLR1
  #define LED_GPIO_BIT  15
#else
  #define LED_GPFSEL    GetGpio()->GPFSEL1
  #define LED_GPFBIT    18
  #define LED_GPSET     GetGpio()->GPSET0
  #define LED_GPCLR     GetGpio()->GPCLR0
  #define LED_GPIO_BIT  16
#endif

#define LED_ON()      (LED_GPSET = ( 1 << LED_GPIO_BIT ))
#define LED_OFF()     (LED_GPCLR = ( 1 << LED_GPIO_BIT ))


extern rpi_gpio_t* GetGpio();

extern void SetGpioPinFunction( rpi_gpio_pin_t gpio, rpi_gpio_alt_function_t func );
#endif