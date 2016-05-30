#ifndef __RPI_BASE_H__
#define __RPI_BASE_H__

#ifdef RPI2
  #define DEVICE_BASE   0x3F000000UL
#else
  #define DEVICE_BASE   0x20000000UL
#endif 

#define GPIO_BASE       (DEVICE_BASE + 0x200000UL)

#endif