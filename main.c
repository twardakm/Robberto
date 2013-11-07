#include <avr/io.h>
#define F_CPU 1000000UL

//potrzebne do delay w nowych kompilatorach
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>
#include "naglowki.h"


int main(void)
{
    unsigned char dane;

    wylacz_JTAG();
    ustaw_porty_silnika();
    ustaw_porty_USART();
    ustaw_porty_diody();

    init_timer0();
    sei();
    int licznik;
    while(1)
    {
            // for(licznik=0;licznik<100;licznik++)
            jedz_lewo();
            //  for(licznik=0;licznik<100;licznik++)
            //   jedz_tyl();

        /*dane=(USART_Receive());

        if (dane==PRZOD)
            jedz_przod();
        /*
        if (dane==TYL)
            jedz_tyl();*/
        /* if  (dane==STOJ)
             stoj();*/
        /*
        if  (dane==PRAWO)
            jedz_prawo();
        if  (dane == LEWO)
            jedz_lewo();*/

        // _delay_ms(1);
    }

    return 0;
}
