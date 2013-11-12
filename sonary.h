#ifndef SONARY_H_INCLUDED
#define SONARY_H_INCLUDED

#define stala_odleglosciowa 107 //doswiadczalna stala dobrana metoda MNP dla 8mhz=460, dla 1mhz=107;
#define ILEPOMIAROW 10

void getdistance(volatile uint8_t *,volatile uint8_t *, volatile uint8_t *);
void sonar1 ();
void sonar2 ();


volatile char wyslalsygnal = 0;
volatile char zboczerosnace = 1;
volatile uint8_t overflows = 0;
volatile uint16_t odleglosc = 0, sumaodleglosc1=0, sumaodleglosc2=0;


ISR(TIMER0_OVF_vect)
{
    if(zboczerosnace==0)
    {
        overflows++; //zliczaj przepelnienia, 8mhz 1 overflow trwa 32 us
        if (((overflows*256+TCNT0)/stala_odleglosciowa)>99) //max dystanc to 99 cm
        {
            zboczerosnace = 1;
            wyslalsygnal = 0;
            odleglosc = 99; //pokaz 99 gdy dystans >=99
        }
    }
}

ISR(INT1_vect)
{
    if(wyslalsygnal==1) //reaguj tylko gdy sonar wyslal sygnał, eliminuje przypadkowe zmiany stanu
    {
        if(zboczerosnace==1) //reakcja na zbocze rosnace
        {
            zboczerosnace = 0; //udstawia reakcje na opadajce,
            TCNT0 = 0;
            overflows = 0; //zeruje liczniki
        }
        else if(zboczerosnace==0) //reakcja na opadajace zbocze
        {
            wyslalsygnal = 0; //konczy pomiar odleglosci
            odleglosc = (overflows*256+TCNT0)/stala_odleglosciowa; // zapisuje odleglosc w cm do zmiennej odleglosc
            zboczerosnace = 1; //ustawia reakcje na zbocze rosnace
        }
    }
}

void sonar1 ()
{
    PORTD &= ~_BV(TRIGGER1); //wylcz trigger na chwile zeby uspokoic elektrony na pinach
    _delay_us(1);
    PORTD |= _BV(TRIGGER1); //poslij impuls na 10us
    wyslalsygnal = 1; //informuj ze moze sie rozpoczas pomiar czasu
    _delay_us(10);
    PORTD &= ~_BV(TRIGGER1); //zakonc nadawanie
}

void sonar2 ()
{
    PORTD &= ~_BV(TRIGGER2); //wylcz trigger na chwile zeby uspokoic elektrony na pinach
    _delay_us(1);
    PORTD |= _BV(TRIGGER2); //poslij impuls na 10us
    wyslalsygnal = 1; //informuj ze moze sie rozpoczas pomiar czasu
    _delay_us(10);
    PORTD &= ~_BV(TRIGGER2); //zakonc nadawanie
}
void getdistance(volatile uint8_t *odleglosc1,volatile uint8_t *odleglosc2, volatile uint8_t *error)
{
    sumaodleglosc1=0;
   // sumaodleglosc2=0;

    int i;
    _delay_ms(1);
    for(i=0; i<ILEPOMIAROW; i++)
    {
        sonar1(); //robienie sygnalu
        _delay_us(500);
        sumaodleglosc1=sumaodleglosc1+odleglosc;
        *error=1; //zapetlona petla 10-ciokrotnego pomiaru odlegosci z pierwszego sensoru
    }
   /* _delay_ms(1);
    for(i=0; i<ILEPOMIAROW; i++)
    {
        sonar2(); //sonar2
        _delay_us(500);
        sumaodleglosc2=sumaodleglosc2+odleglosc;
        *error=2; //zapetlona petla 10-ciokrotnego pomiaru odlegosci z drugiego sensoru
    }
    */
    *odleglosc1=sumaodleglosc1/ILEPOMIAROW;
   // *odleglosc2=sumaodleglosc2/ILEPOMIAROW;

   *error=0; //wszyskto w porzadku
}
#endif // SONARY_H_INCLUDED
