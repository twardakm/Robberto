#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void USART_Transmit( unsigned char  );
unsigned char USART_Receive( void );
void USART_Flush( void );
void init_timer0();
void wylacz_JTAG();
void ustaw_porty_silnika();
void USART_Init( unsigned int  );
void ustaw_porty_USART();
void ustaw_porty_diody();
void serwo_init();

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
    TCCR0 = (0<<CS02)|(0<<CS01)|(1<<CS00); //brak preskalera na timerze0
    TIMSK = (1<<TOIE0); //wlaczenie zegarka 0
}
void serwo_init()
{
    //port PWM na wyjscie
    TCCR1A = (1<<COM1A1) | (1<<WGM11); //tryb pracy licznika(15), ustawienie prescalera na 1,
    TCCR1B = (1<<CS10)|(1<<WGM12)|(1<<WGM13); //(preskaler=1)|(szybki PWM)
    DDRD |=_BV(5);
    ICR1 = 19999; //T=20ms
}


#endif
