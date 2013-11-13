#ifndef SERWO_H_INCLUDED
#define SERWO_H_INCLUDED

#define SERWODELAY 20 //tymczasowe do zastapienia funkcjami

volatile int8_t katserwo;
void serwokat(volatile int8_t);


void serwokat( int8_t katserwo)
{
    if(katserwo>=-45 && katserwo<=45)
        OCR1A=1500+katserwo*11.111111111;
}

#endif // SERWO_H_INCLUDED
