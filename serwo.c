#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

#define SERWODELAY 50
//koment
void serwokat(int kat, int nowykat)
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

void serwozeruj(int kat)
{
 OCR1A=1500;
 kat=0;
}

void serwolewo(int kat)
{
    while(kat=45)
    {
    OCR1A=OCR1A-11.111111111;
    kat--;
    _delay_ms(SERWODELAY); // zamiast tego inne czynnosci np pomiary
    }
}

void serwoprawo(int kat)
{
    while(kat>=-45)
    {
    OCR1A=OCR1A+11.111111111;
    kat++;
    _delay_ms(SERWODELAY);
    }
}

void serwo_init()
{
    DDRD |=_BV(5); //port PWM na wyjscie
    TCCR1A = (1<<COM1A1) | (1<<WGM11); //tryb pracy licznika(15), ustawienie prescalera na 1,
    TCCR1B = (1<<CS10)|(1<<WGM12)|(1<<WGM13); //(preskaler=1)|(szybki PWM)
    ICR1 = 19999; //T=20ms
}


int main()
{
serwo_init();
 int kat=0;
 int i;

while(1)
{

}

}
