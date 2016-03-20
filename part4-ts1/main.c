#include "gpio.h"
#include "systimer.h"
#include "ts.h"

//GPIO Register set
volatile unsigned int* gpio;


volatile unsigned int* gpio_FS1 = (unsigned int*)(GPIO_BASE + 0x04);
volatile unsigned int* gpio_FS4 = (unsigned int*)(GPIO_BASE + 0x10);

void cmain(void)
{
	
  gpio = (unsigned int*) GPIO_BASE;

  gpio[LED_GPFSEL] |= (1 << LED_GPFBIT);

  while(1) {
  	LED_ON();
    WaitForMicroseconds(500);
    ts();
    LED_OFF();
    WaitForMicroseconds(500);
    
  }
}
