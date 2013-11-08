#include <avr/io.h>
#define F_CPU 1000000UL

//potrzebne do delay w nowych kompilatorach
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>
#include "krokowe.h"
#include "init.h"
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
    sei();

    volatile uint16_t kat=90;// wykona obrot o 90 stopni
    volatile uint16_t odleglosc=100; //

     while(1)
    {
       serwozeruj();
        _delay_ms(500);

      jedz_przod(&odleglosc);
        _delay_ms(1000);
      //jedz_lewo(&kat);
     // _delay_ms(1000);


        /*serwokat(katserwo, 10);
        _delay_ms(500);
        serwokat(katserwo, 35);
        _delay_ms(500);
        serwokat(katserwo,-45);
        _delay_ms(500);
         serwokat(katserwo, -10);
        _delay_ms(500);
        serwokat(katserwo, -35);
        _delay_ms(500);
        serwokat(katserwo, 45);
        _delay_ms(500);*/



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
