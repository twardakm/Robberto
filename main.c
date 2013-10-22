#include <avr/io.h>
#define F_CPU 1000000UL

//potrzebne do delay w nowych kompilatorach
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "naglowki.h"

int main(void)
{
    wylacz_JTAG();
    ustaw_porty_silnika();

    while(1)
    {
        jedz_przod();
    }

    return 0;
}
