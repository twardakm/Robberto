/*
 */

#include <avr/io.h>

int main(void)
{

	MCUCSR |=(1<<JTD);
    MCUCSR |=(1<<JTD);

	DDRA = 0xff;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;

	PORTA = 0xff;
	PORTB = 0xff;
	PORTC = 0xff;
	PORTD = 0xff;
	return 0;

    return 0;
}
