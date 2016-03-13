#ifdef RPI2
  #define GPIO_BASE 0x3F200000UL
#else
  #define GPIO_BASE 0x20200000UL
#endif

volatile unsigned int* gpioFs1 = (unsigned int*)(GPIO_BASE + 0x04);
volatile unsigned int* gpioFs4 = (unsigned int*)(GPIO_BASE + 0x10);

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

//GPIO Register set
volatile unsigned int* gpio;

//loop variable
volatile unsigned int tim;

int main(void) __attribute__((naked));
int main(void)
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
