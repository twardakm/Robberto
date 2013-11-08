#ifndef NAGLOWKI_H_INCLUDED
#define NAGLOWKI_H_INCLUDED

#define SERWODELAY 50 //tymczasowe do zastapienia funkcjami

volatile uint8_t kat, nowykat;

void serwo_init();
void serwokat(volatile uint8_t*, volatile uint8_t* );
void serwozeruj(volatile uint8_t*);

void serwokat(volatile uint8_t &kat, volatile uint8_t &nowykat)
{
    if(kat<nowykat)
    {
        while(kat!=nowykat)
        {
        OCR1A=OCR1A+11.111111111;
        _delay_ms(SERWODELAY); // zamiast tego inne czynnosci np pomiary
        kat++;
        }
    }
    else if(kat>nowykat)
    {
        while(kat!=nowykat)
        {
        OCR1A=OCR1A-11.111111111;
        _delay_ms(SERWODELAY); // zamiast tego inne czynnosci np pomiary
        kat--;
        }
    }
}

void serwozeruj(volatile uint8_t &kat)
{
 OCR1A=1500;
 kat=0;
}

void serwo_init()
{
    DDRD |=_BV(5); //port PWM na wyjscie
    TCCR1A = (1<<COM1A1) | (1<<WGM11); //tryb pracy licznika(15), ustawienie prescalera na 1,
    TCCR1B = (1<<CS10)|(1<<WGM12)|(1<<WGM13); //(preskaler=1)|(szybki PWM)
    ICR1 = 19999; //T=20ms
}

