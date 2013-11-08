#ifndef SERWO_H_INCLUDED
#define SERWO_H_INCLUDED

#define SERWODELAY 20 //tymczasowe do zastapienia funkcjami

volatile int8_t nowykatserwo=0, katserwo;
void serwokat(volatile int8_t, volatile int8_t ); // (kat ktory uzyskamy ; o ile zmieniamy -nowykat=prawo +nowykat=lewo
void serwozeruj();

void serwokat( int8_t katserwo,  int8_t nowykatserwo)
{
        while(katserwo<nowykatserwo && OCR1A<=2000)
        {
        OCR1A=OCR1A+11;
        _delay_ms(SERWODELAY); // zamiast tego inne czynnosci np pomiary
        katserwo++;
        }


        while(katserwo>nowykatserwo && OCR1A>=1000)
        {

        OCR1A=OCR1A-11;
        _delay_ms(SERWODELAY); // zamiast tego inne czynnosci np pomiary
        katserwo--;
        }

}

void serwozeruj()
{
 OCR1A=1500;
 katserwo=0;
}
#endif // SERWO_H_INCLUDED
