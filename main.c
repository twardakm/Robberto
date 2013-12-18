#include <avr/io.h>
#define F_CPU 8000000UL

//potrzebne do delay w nowych kompilatorach
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>

#include "init.h"
#include "sonary.h"
#include "serwo.h"
#include "krokowe.h"



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


    _delay_ms(10);
    PORT_DIODY=0x00;
    int licznik=0;

    while (1)
    {
        _delay_ms(300);
        getdistance(&lewy, &prawy, &error);
        if(lewy<5 && (lewy<prawy))
            serwokat(15) ;
        else if (prawy<5 && (prawy<lewy))
            serwokat(-15);
        else
        serwokat(0);
       // if(prawy<10)
           // serwokat(30);

        /*
        licznik++;
        if(licznik>10)
        {
            licznik=0;
            check();
        }
        jedz_przod();
        */

        /*
        int i;
        //jedz();
        _delay_ms(300);
        PORT_DIODY=0x00;

        getdistance(&lewy, &prawy, &error);

        if(lewy<25)
        {
            PORT_DIODY |= _BV(LED1);
            for(i=0;i<40;i++)
                jedz_lewo();
         }
        else
        {
            for(i=0;i<30;i++)
                jedz_przod();
        }
        serwokat(-30);
        _delay_ms(300);
        serwokat(30);
        _delay_ms(300);
        serwokat(0);

        */




        /* getdistance(&lewy, &prawy, &error);
         _delay_ms(100);

        if(lewy>10)// probna na lewy
        {
            serwokat(0);
        }
         else if(lewy==0)
         {
             jedz_przod(&odleglosc);
         }
         else if(lewy<10)
         {
             serwokat(-30);
         }
         */

        /*
               if(lewy<10 && prawy<10)
        {
            jedz_tyl(&odleglosc);
        }
        else if(lewy<10 && prawy>10)
        {
            serwokat(30);
        }
        else if(lewy>10 && prawy<10)
        {
            serwokat(-30);
        }
        else if(lewy==0)
        {
            jedz_lewo(&kat);
        }

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
