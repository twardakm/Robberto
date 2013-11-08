#ifndef KROKOWE_H_INCLUDED
#define KROKOWE_H_INCLUDED

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
#define OPOZNIJ_MS_WYSOKIE 38 //312 przy 16mhz, 19=1mhz (turbo mode)
#define OPOZNIJ_MS_NISKIE 54 //437 przy 16mhz 27=1mhz (turbo mode)

//sterowanie
#define PRZOD   8
#define STOJ    5
#define TYL     2
#define PRAWO   6
#define LEWO    4

 #define STALA_OBROTU 31/9 //Dobrana metoda MNP tak by przy podaniu wartosci 'kat'=90 wykonywal obrot o 90 stopni
 #define STALA_ODLEGLOSCI 91/10 //Dobrana metoda MNP tak by przy podaniu wartosci 'odleglosc'=100 pokonywal 100cm

volatile uint16_t przepelnienie=0, krok,licznik;

void jedz_przod(volatile uint16_t *);
void jedz_tyl(volatile uint16_t *);
void jedz_lewo(volatile uint16_t *);
void jedz_prawo(volatile uint16_t *);
void jedz();


void jedz()
{
    while(przepelnienie<OPOZNIJ_MS_WYSOKIE) // 5ms wejdzie w niskie ms
    {
        PORT_SILNIKOW |= _BV(CLOCK_1_BV);
        PORT_SILNIKOW |= _BV(CLOCK_2_BV);
    }
    while(przepelnienie<OPOZNIJ_MS_NISKIE)
    {
        PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
        PORT_SILNIKOW &= ~(_BV(CLOCK_2_BV));
    }
    przepelnienie=0;

}
void jedz_przod(volatile uint16_t *odleglosc)
{
    PORT_SILNIKOW |= (_BV(KIERUNEK_1_BV));
    PORT_SILNIKOW |= (_BV(KIERUNEK_2_BV));
    for(licznik=0;licznik<*odleglosc*STALA_ODLEGLOSCI;licznik++)
        jedz();
}
void jedz_tyl(volatile uint16_t *odleglosc)
{
    PORT_SILNIKOW &= ~(_BV(KIERUNEK_1_BV));
    PORT_SILNIKOW &= ~(_BV(KIERUNEK_2_BV));
    for(licznik=0;licznik<*odleglosc*STALA_ODLEGLOSCI;licznik++)
        jedz();
}
void jedz_lewo(volatile uint16_t *odleglosc)
{
    PORT_SILNIKOW |= (_BV(KIERUNEK_1_BV));
    PORT_SILNIKOW &= ~(_BV(KIERUNEK_2_BV));
    for(licznik=0;licznik<*odleglosc*STALA_OBROTU;licznik++)
        jedz();

}
void jedz_prawo(volatile uint16_t *odleglosc)
{
    PORT_SILNIKOW &= ~(_BV(KIERUNEK_1_BV));
    PORT_SILNIKOW |= (_BV(KIERUNEK_2_BV));
    for(licznik=0;licznik<*odleglosc*STALA_OBROTU;licznik++)
        jedz();
}

ISR(TIMER0_OVF_vect)
{
    przepelnienie++;//1przepelnienie trwa 16us, 5ms=5000/16=312przepelnien
}



#endif // NAGLOWKI_H_INCLUDED
