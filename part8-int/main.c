#include "gpio.h"
#include "rpi-aux.h"
#include "util.h"
#include "systimer.h"
#include "rpi-interrupts.h"

#define DEFAULT_BAUD    115200


void cmain(void)
{
    volatile int i = 0;
    rpi_gpio_t* gpio = GetGpio();

    LED_GPFSEL |= (1 << LED_GPFBIT);

    InitVectorTable();
    AuxMiniUartInit(DEFAULT_BAUD, 8);
    
    while(i++ < 5) 
    {
        LED_ON();
        WaitForMicroseconds(200);
        LED_OFF();
        WaitForMicroseconds(200);
    }
    
    printfk("Initialize Complete\r\n");
    printfk("Current i value is %d\r\n", i);
    printfk("Display test: %x, %s \r\n",  1024, "This is test");
    printfk("################################\r\n");
    printfk("#      Locosoftware.Inc        #\r\n");
    printfk("################################\r\n");
    printfk("Ready\r\n>");

    
    while(1)
    {
      char c = kgetc();  
      if(c == 13)
      {
        printfk("\r\n>");
      }
      else
      {
        kputc(c);
      }
      
    }
}
