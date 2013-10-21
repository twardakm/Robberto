#ifndef NAGLOWKI_H_INCLUDED
#define NAGLOWKI_H_INCLUDED

//definicjie do sterowania silnikami
#define DDR_SILNIKOW    DDRA
#define PORT_SILNIKOW   PORTA

#define CNTL_1  0
#define CNTL_1_BV PA0
#define CLOCK_1 1
#define CLOCK_1_BV PA1
#define RESET_1 2
#define RESET_1_BV PA2
#define KIERUNEK_1  3
#define KIERUNEK_1_BV PA3

#define CNTL_2  7
#define CNTL_2_BV PA7
#define CLOCK_2 6
#define CLOCK_2_BV PA6
#define RESET_2 5
#define RESET_2_BV PA5
#define KIERUNEK_2  4
#define KIERUNEK_2_BV PA4

#define DDR_DIODY DDRC
#define PORT_DIODY PORTC
#define LED1    PC0
#define LED2    PC1
#define LED3    PC2
#define LED4    PC3

//opóźnienie [ms] (później zamienić na jakiś timer)
#define OPOZNIJ_MS 50
#define OPOZNIJ_US 10

void wylacz_JTAG()
{
    MCUCSR |=(1<<JTD);
	MCUCSR |=(1<<JTD);
}

void ustaw_porty_silnika()
{
    DDR_SILNIKOW = 0xff;
    PORT_SILNIKOW = 0xff;

    DDR_DIODY = 0xff;
    PORT_DIODY = 0xff;

    _delay_ms(OPOZNIJ_MS);
    PORT_DIODY = 0;

    PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
    PORT_DIODY |= _BV(LED4);
    _delay_ms(OPOZNIJ_MS);
    PORT_DIODY &= ~(_BV(LED4));

    /*PORT_SILNIKOW &= ~(_BV(RESET_1_BV));
    PORT_SILNIKOW &= ~(_BV(RESET_2_BV));*/
}

void jedz_przod()
{
    PORT_DIODY |= _BV(LED1);
    PORT_SILNIKOW |= _BV(CLOCK_1_BV);
    _delay_ms(5);
    PORT_DIODY &= ~(_BV(LED1));

    PORT_DIODY |= _BV(LED4);
    PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
    _delay_ms(20);
    PORT_DIODY &= ~(_BV(LED4));

    PORT_SILNIKOW |= _BV(KIERUNEK_1_BV);
    _delay_ms(10);
}

void jedz_przod_2()
{
    PORT_DIODY |= _BV(LED1);
    PORT_SILNIKOW |= _BV(CLOCK_1_BV);
    _delay_ms(5);
    PORT_DIODY &= ~(_BV(LED1));

    PORT_DIODY |= _BV(LED4);
    PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
    _delay_ms(20);
    PORT_DIODY &= ~(_BV(LED4));
    PORT_SILNIKOW &= ~(_BV(KIERUNEK_1_BV));
    _delay_ms(10);
}

#endif // NAGLOWKI_H_INCLUDED
