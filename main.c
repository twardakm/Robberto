/*
 */

#include <avr/io.h>

int main(void)
{

	MCUCSR |=(1<<JTD);
	MCUCSR |=(1<<JTD);

    return 0;
}
