#include "rpi-armtimer.h"

static armtimer_t* rpiArmTimer = (armtimer_t*)RPI_ARMTIMER_BASE;

armtimer_t* GetArmTimer(void)
{
    return rpiArmTimer;
}