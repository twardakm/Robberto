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
#define OPOZNIJ_MS_WYSOKIE 5
#define OPOZNIJ_MS_NISKIE 2

//sterowanie
#define PRZOD   8
#define STOJ    5
#define TYL     2
#define PRAWO   6
#define LEWO    4

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

  //  PORT_SILNIKOW &= ~(_BV(KIERUNEK_1_BV));

    _delay_ms(OPOZNIJ_MS_NISKIE);
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

void jedz_przod()
{
    PORT_SILNIKOW |= _BV(CLOCK_1_BV);
    PORT_SILNIKOW |= _BV(CLOCK_2_BV);
    _delay_ms(OPOZNIJ_MS_WYSOKIE);

    PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
    PORT_SILNIKOW &= ~(_BV(CLOCK_2_BV));
    _delay_ms(OPOZNIJ_MS_NISKIE);
}

void baczek()
{
    PORT_SILNIKOW |= _BV(CLOCK_1_BV);
    PORT_SILNIKOW |= _BV(CLOCK_2_BV);
    _delay_ms(OPOZNIJ_MS_WYSOKIE);

    PORT_SILNIKOW &= ~(_BV(CLOCK_1_BV));
    PORT_SILNIKOW &= ~(_BV(CLOCK_2_BV));
    _delay_ms(OPOZNIJ_MS_NISKIE);
}


void stoj()
{

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


#endif // NAGLOWKI_H_INCLUDED
