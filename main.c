#include <avr/io.h>
#define F_CPU 1000000UL

//potrzebne do delay w nowych kompilatorach
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>
#include "krokowe.h"
#include "init.h"
#include "sonary.h"
#include "serwo.h"


int main(void)
{
    unsigned char dane;

    wylacz_JTAG();
    ustaw_porty_silnika();
    ustaw_porty_USART();
    ustaw_porty_diody();

    serwo_init();
    init_timer0();
    init_timer2();
    init_sonary();

    sei();

    volatile uint16_t kat=90;// wykona obrot o 90 stopni
    volatile uint16_t odleglosc=5; //odleglosc w cm
    volatile uint8_t lewy=1, prawy=0, error=0;


    _delay_ms(1000);
    while (1)
    {
        getdistance(&lewy, &prawy, &error);
        _delay_ms(100);
        if(lewy>=10)
        {
            jedz_przod(&odleglosc);
        }
        else if(lewy==0)
        {
            jedz_lewo(&kat);
        }
        else if(lewy<10)
        {
            jedz_tyl(&odleglosc);
        }
        /*serwokat(30);
        _delay_ms(500);
        serwokat(-30);
        _delay_ms(500);
        serwokat(45);
        _delay_ms(500);
        serwokat(0);
        _delay_ms(500);
        */

    }

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

    return 0;
}
