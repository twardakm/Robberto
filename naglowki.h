#ifndef NAGLOWKI_H_INCLUDED
#define NAGLOWKI_H_INCLUDED

//definicjie do sterowania silnikami
#define DDR_SILNIKOW    DDRA
#define PORT_SILNIKOW   PORTA

#define CNTL_1  0
#define CLOCK_1 1
#define CLOCK_1_BV PA1
#define RESET_1 2
#define KIERUNEK_1  3

#define CNTL_2  7
#define CLOCK_2 6
#define CLOCK_2_BV PA6
#define RESET_2 5
#define KIERUNEK_2  4

//opóźnienie [ms] (później zamienić na jakiś timer)
#define OPOZNIJ 50

void wylacz_JTAG()
{
    MCUCSR |=(1<<JTD);
	MCUCSR |=(1<<JTD);
}

void ustaw_porty_silnika()
{
    DDR_SILNIKOW = 0xff;
    PORT_SILNIKOW = 0xff;

    PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
    PORT_SILNIKOW &= ~(_BV(CLOCK_2_BV));
}

void jedz_przod()
{
    PORT_SILNIKOW |= _BV(CLOCK_1_BV);
    PORT_SILNIKOW |= _BV(CLOCK_2_BV);
    _delay_ms(OPOZNIJ);
    PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
    PORT_SILNIKOW &= ~(_BV(CLOCK_2_BV));
}

#endif // NAGLOWKI_H_INCLUDED
