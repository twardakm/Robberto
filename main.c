#include <avr/io.h>
#define F_CPU 1000000UL

//potrzebne do delay w nowych kompilatorach
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>
#include "krokowe.h"
#include "init.h"


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
    volatile uint16_t kat=90;// wykona obrot o 90 stopni
    volatile uint16_t odleglosc=910; //
   // while(1)
    {
        _delay_ms(1000);
        jedz_przod(&odleglosc);

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
