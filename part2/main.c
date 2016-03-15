#include "gpio.h"

//GPIO Register set
volatile unsigned int* gpio;

//loop variable
volatile unsigned int tim;


volatile unsigned int* gpioFs1 = (unsigned int*)(GPIO_BASE + 0x04);
volatile unsigned int* gpioFs4 = (unsigned int*)(GPIO_BASE + 0x10);

void cmain(void)
{
  gpio = (unsigned int*) GPIO_BASE;

  gpio[LED_GPFSEL] |= (1 << LED_GPFBIT);

  while(1) {
    for (tim = 0; tim < 500000; ++tim);

    gpio[LED_GPCLR] = (1 << LED_GPIO_BIT);

    for (tim = 0; tim < 500000; ++tim);

    gpio[LED_GPSET] = (1 << LED_GPIO_BIT);
  }
}
