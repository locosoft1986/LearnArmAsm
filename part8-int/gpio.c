#include "gpio.h"

static rpi_gpio_t* rpiGpio = (rpi_gpio_t*)GPIO_BASE;


rpi_gpio_t* GetGpio()
{
    return rpiGpio;
}

void SetGpioPinFunction( rpi_gpio_pin_t gpio, rpi_gpio_alt_function_t func )
{
    vu32_t* fsel_reg = &((vu32_t*)rpiGpio)[ gpio / 10 ];
    vu32_t fsel_copy = *fsel_reg;
    fsel_copy &= ~( FS_MASK << ( ( gpio % 10 ) * 3 ) );
    fsel_copy |= (func << ( ( gpio % 10 ) * 3 ) );
    *fsel_reg = fsel_copy;
}
