#include "aux.h"
#include "gpio.h"

/* Define the system clock frequency in MHz for the baud rate calculation.
   This is clearly defined on the BCM2835 datasheet errata page:
   http://elinux.org/BCM2835_datasheet_errata */
#define SYS_FREQ    250000000

static aux_t* aux = (aux_t*)AUX_BASE;

aux_t* GetAux()
{
    return aux;
}

void AuxMiniUartInit(int baud, int bits)
{
    volatile int i = 0;
    
    aux->ENABLES = AUX_ENABLE_MINIUART;
    aux->MU_IER = 0;
    aux->MU_CNTL = 0;
    if (bits == 8)
    {
        aux->MU_LCR = AUX_MULCR_8BIT_MODE;
    }
    else
    {
        aux->MU_LCR = 0;
    }
    
    aux->MU_MCR = 0;
    
    //[7:6]FIFO enables(Both bits always read as 1 as the FIFOs are always
    //              enabled)
    //[2]Writing with bit 2 set will clear the transmit FIFO
    //[1]Writing with bit 1 set will clear the receive FIFO
    //[0]This bit is clear whenever an interrupt is pending(Reset value 0)
    aux->MU_IIR = 0xC6;//11000110
    
    //Transposed calculation from Section 2.2.1 of the ARM peripherals doc
    aux->MU_BAUD = (SYS_FREQ / (8*baud)) - 1;
    
    SetGpioPinFunction(GPIO14, FS_ALT5);
    SetGpioPinFunction(GPIO15, FS_ALT5);
    
    //See page 101 to enable pin 14 clock
    GetGpio()->GPPUD = 0;
    for( i=0; i<150; i++ ) { }
    GetGpio()->GPPUDCLK0 = (1 << 14);
    
    for( i=0; i<150; i++ ) { }
    GetGpio()->GPPUDCLK0 = 0;
    
    aux->MU_CNTL = AUX_MUCNTL_TX_ENABLE | AUX_MUCNTL_RX_ENABLE;
}

void AuxMiniUartWrite(char c)
{
    while((aux->MU_LSR & AUX_MULSR_TX_EMPTY) == 0);
    
    
    aux->MU_IO = c;
}

char AuxMiniUartRead()
{    
    while((aux->MU_LSR & AUX_MUSTAT_SYMBOL_AV) == 0);
    
    return (char)aux->MU_IO;
}