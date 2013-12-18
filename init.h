#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#define TRIGGER1 PD4    //NA INT 0
#define TRIGGER2 PD6    // NA INT1


//main/c
volatile uint16_t kat=90;// wykona obrot o 90 stopni
volatile uint8_t lewy=1, prawy=1, error=0;

//krokowe.h
#define DDR_DIODY DDRC
#define PORT_DIODY PORTC

#define LED1    PC0
#define LED2    PC1
#define LED3    PC2
#define LED4    PC3

#define DDR_SILNIKOW    DDRA
#define PORT_SILNIKOW   PORTA


#define IN1A    PA0
#define IN1B    PA1
#define IN2A    PA2
#define IN2B    PA3
#define IN3A    PA5
#define IN3B    PA4
#define IN4A    PA7
#define IN4B    PA6

void check();
void jedz_przod();
void jedz_lewo();

//sonary.h
void getdistance(volatile uint8_t *,volatile uint8_t *, volatile uint8_t *);
void sonar1 ();
void sonar2 ();

volatile char wyslalsygnal1 = 0;
volatile char wyslalsygnal2 = 0;
volatile char zboczerosnace = 1;
volatile uint8_t overflows = 0;
volatile uint16_t odleglosc = 0, sumaodleglosc1=0, sumaodleglosc2=0;

//serwo.h
volatile int8_t katserwo;
void serwokat(volatile int8_t);

//init.h
void USART_Transmit( unsigned char  );
unsigned char USART_Receive( void );
void USART_Flush( void );
void init_timer0();
void init_timer2();
void wylacz_JTAG();
void ustaw_porty_silnika();
void USART_Init( unsigned int  );
void ustaw_porty_USART();
void ustaw_porty_diody();
void serwo_init();
void init_sonary();

void wylacz_JTAG()
{
    MCUCSR |=(1<<JTD);
    MCUCSR |=(1<<JTD);
}

void ustaw_porty_silnika()
{
    DDR_SILNIKOW = 0xff;
    PORT_SILNIKOW = 0xff;

    _delay_ms(5);
}

void USART_Init( unsigned int baud )
{
    /* Set baud rate */
    UBRRH = (unsigned char)(baud>>8);
    UBRRL = (unsigned char)baud;
    /* Enable receiver and transmitter */
    UCSRB = (1<<RXEN)|(1<<TXEN);
    /* Set frame format: 8data, 2stop bit */
    UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void ustaw_porty_USART()
{
    DDRD |= _BV(0);
    DDRD &= ~_BV(1);

    USART_Init(12);
}

void ustaw_porty_diody()
{
    DDR_DIODY = 0xff;
}
void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSRA & (1<<UDRE)) )
        ;
    /* Put data into buffer, sends the data */
    UDR = data;
}

unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) )
        ;
    /* Get and return received data from buffer */
    return UDR;
}

void USART_Flush( void )
{
    unsigned char dummy;
    while ( UCSRA & (1<<RXC) ) dummy = UDR;
}
void init_timer0()
{
    TCCR0 |= (0<<CS02)|(0<<CS01)|(1<<CS00); //brak preskalera na timerze0
    TIMSK |= (1<<TOIE0); //wlaczenie zegarka 0
}
void init_timer2()
{
    TCCR2 |= (0<<CS22)|(0<<CS21)|(1<<CS20); //brak preskalera na timerze2
    TIMSK |= (1<<TOIE2); //wlaczenie zegarka 2
}
void serwo_init()
{
    //port PWM na wyjscie
    TCCR1A = (1<<COM1A1) | (1<<WGM11); //tryb pracy licznika(15), ustawienie prescalera na 1,
    TCCR1B = (1<<CS11)|(1<<WGM12)|(1<<WGM13); //(preskaler=8)|(szybki PWM)
    DDRD |=_BV(5);
    OCR1A=1500;
    ICR1 = 19999; //T=20ms
}
void init_sonary()
{
    DDRD |= _BV(TRIGGER1); //trigger jako wyjscie
    DDRD |= _BV(TRIGGER2);
    //DDRD |= _BV(PD2);
    //DDRD |= _BV(PD3);

    MCUCR |= (0<<ISC11)|(1<<ISC10);
    //ustawinie przerwan na interrupcie 1, reagujacych na opadajace lub rosnace zbocze
    MCUCR |= (0<<ISC01)|(1<<ISC00);
    //ustawinie przerwan na interrupcie 0, reagujacych na opadajace lub rosnace zbocze

    GICR |= (1<<INT1);
    GICR |= (1<<INT0);
}


#endif
