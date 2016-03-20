#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef RPI2
  #define GPIO_BASE 0x3F200000UL
#else
  #define GPIO_BASE 0x20200000UL
#endif

#define GPIO_GPFSEL0    0
#define GPIO_GPFSEL1    1
#define GPIO_GPFSEL2    2
#define GPIO_GPFSEL3    3
#define GPIO_GPFSEL4    4
#define GPIO_GPFSEL5    5

#define GPIO_GPSET0     7
#define GPIO_GPSET1     8

#define GPIO_GPCLR0     10
#define GPIO_GPCLR1     11



#if defined(RPIPLUS) || defined(RPI2)
  #define LED_GPFSEL    GPIO_GPFSEL4
  #define LED_GPFBIT    21
  #define LED_GPSET     GPIO_GPSET1
  #define LED_GPCLR     GPIO_GPCLR1
  #define LED_GPIO_BIT  15
#else
  #define LED_GPFSEL    GPIO_GPFSEL1
  #define LED_GPFBIT    18
  #define LED_GPSET     GPIO_GPSET0
  #define LED_GPCLR     GPIO_GPCLR0
  #define LED_GPIO_BIT  16
#endif

#define LED_ON()      (gpio[LED_GPSET] = ( 1 << LED_GPIO_BIT ))
#define LED_OFF()     (gpio[LED_GPCLR] = ( 1 << LED_GPIO_BIT ))

#endif