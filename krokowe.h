#ifndef KROKOWE_H_INCLUDED
#define KROKOWE_H_INCLUDED

#define DELAY 10
#define ACHTUNG 5

//volatile uint16_t przepelnienie=0;

void jedz_przod()
{

    PORT_SILNIKOW |= _BV(IN1A);
    PORT_SILNIKOW &= ~_BV(IN1B);

    PORT_SILNIKOW |= _BV(IN2A);
    PORT_SILNIKOW &= ~_BV(IN2B);


    PORT_SILNIKOW &= ~_BV(IN3A);
    PORT_SILNIKOW |= _BV(IN3B);

    PORT_SILNIKOW &= ~_BV(IN4A);
    PORT_SILNIKOW |= _BV(IN4B);

    _delay_ms(DELAY);

    PORT_SILNIKOW &= ~_BV(IN1A);
    PORT_SILNIKOW |= _BV(IN1B);

    PORT_SILNIKOW |= _BV(IN2A);
    PORT_SILNIKOW &= ~_BV(IN2B);


    PORT_SILNIKOW |= _BV(IN3B);
    PORT_SILNIKOW &= ~_BV(IN3A);

    PORT_SILNIKOW &= ~_BV(IN4B);
    PORT_SILNIKOW |= _BV(IN4A);

    _delay_ms(DELAY);

    PORT_SILNIKOW &= ~_BV(IN1A);
    PORT_SILNIKOW |= _BV(IN1B);

    PORT_SILNIKOW &= ~_BV(IN2A);
    PORT_SILNIKOW |= _BV(IN2B);

    PORT_SILNIKOW &= ~_BV(IN3B);
    PORT_SILNIKOW |= _BV(IN3A);

    PORT_SILNIKOW &= ~_BV(IN4B);
    PORT_SILNIKOW |= _BV(IN4A);

    _delay_ms(DELAY);

    PORT_SILNIKOW |= _BV(IN1A);
    PORT_SILNIKOW &= ~_BV(IN1B);

    PORT_SILNIKOW &= ~_BV(IN2A);
    PORT_SILNIKOW |= _BV(IN2B);

    PORT_SILNIKOW |= _BV(IN3A);
    PORT_SILNIKOW &= ~_BV(IN3B);

    PORT_SILNIKOW &= ~_BV(IN4A);
    PORT_SILNIKOW |= _BV(IN4B);
    _delay_ms(DELAY);

}
void checkandturn()
{
    int i, test=0;
    lewy=0;
    getdistance(&lewy, &prawy, &error);
    while(lewy<ACHTUNG)
    {
        for(i=0; i<20; i++)
            jedz_lewo();
        lewy=0;
       getdistance(&lewy, &prawy, &error);
       test=1;
    }
    if(test==1)
    {
    serwokat(-30);
    _delay_ms(300);
    serwokat(30);
    _delay_ms(300);
    serwokat(0);
    _delay_ms(300);
    test=0;
    }
}
void check()
{
        checkandturn();


       /* serwokat(-30);
        _delay_ms(300);
        checkandturn();

        serwokat(30);
        _delay_ms(300);
        checkandturn();
        serwokat(0);
        */
}


void jedz_lewo()
{
    PORT_SILNIKOW |= _BV(IN1A);
    PORT_SILNIKOW &= ~_BV(IN1B);

    PORT_SILNIKOW |= _BV(IN2A);
    PORT_SILNIKOW &= ~_BV(IN2B);


    PORT_SILNIKOW |= _BV(IN3A);
    PORT_SILNIKOW &= ~_BV(IN3B);

    PORT_SILNIKOW |= _BV(IN4A);
    PORT_SILNIKOW &= ~_BV(IN4B);

    _delay_ms(DELAY);

    PORT_SILNIKOW &= ~_BV(IN1A);
    PORT_SILNIKOW |= _BV(IN1B);

    PORT_SILNIKOW |= _BV(IN2A);
    PORT_SILNIKOW &= ~_BV(IN2B);


    PORT_SILNIKOW &= ~_BV(IN3A);
    PORT_SILNIKOW |= _BV(IN3B);

    PORT_SILNIKOW |= _BV(IN4A);
    PORT_SILNIKOW &= ~_BV(IN4B);

    _delay_ms(DELAY);

    PORT_SILNIKOW &= ~_BV(IN1A);
    PORT_SILNIKOW |= _BV(IN1B);

    PORT_SILNIKOW &= ~_BV(IN2A);
    PORT_SILNIKOW |= _BV(IN2B);

    PORT_SILNIKOW &= ~_BV(IN3A);
    PORT_SILNIKOW |= _BV(IN3B);

    PORT_SILNIKOW &= ~_BV(IN4A);
    PORT_SILNIKOW |= _BV(IN4B);

    _delay_ms(DELAY);

    PORT_SILNIKOW |= _BV(IN1A);
    PORT_SILNIKOW &= ~_BV(IN1B);

    PORT_SILNIKOW &= ~_BV(IN2A);
    PORT_SILNIKOW |= _BV(IN2B);

    PORT_SILNIKOW |= _BV(IN3A);
    PORT_SILNIKOW &= ~_BV(IN3B);

    PORT_SILNIKOW &= ~_BV(IN4A);
    PORT_SILNIKOW |= _BV(IN4B);
    _delay_ms(DELAY);

}



ISR(TIMER2_OVF_vect)
{
    // przepelnienie++;//1przepelnienie trwa 16us, 5ms=5000/16=312przepelnien
}

#endif // NAGLOWKI_H_INCLUDED
