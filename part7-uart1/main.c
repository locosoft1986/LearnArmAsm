#include "gpio.h"
#include "aux.h"
#include "systimer.h"

#define DEFAULT_BAUD    115200


void cmain(void)
{
    volatile int i = 0;
    rpi_gpio_t* gpio = GetGpio();

    LED_GPFSEL |= (1 << LED_GPFBIT);

    AuxMiniUartInit(DEFAULT_BAUD, 8);
    
    while(i++ < 5) 
    {
        LED_ON();
        WaitForMicroseconds(500);
        LED_OFF();
        WaitForMicroseconds(500);
    }
    
    i = 0;
    while(i++ < 7) 
    {
        AuxMiniUartWrite(0x30 + i);
    }
    
    while(1)
    {
      char c = AuxMiniUartRead();  
      AuxMiniUartWrite(c);
    }
}
