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

    sei();

    while(1)
    {
        baczek();
        //jedz_przod();

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


