#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
// sw PD2, led PD4 PD5 PD6
#define LED PD4
int main()
{
	//DDRB |= (1 << PB0);
	DDRD |= 0b01110000;
	DDRD &= ~(1 << PD2);
	while ( 1) {
		if ( !(PIND & (1<<PD2)) ) 
			PORTD |= (1 << LED);

		if ( !(PIND & (1<<PD2)) ) 
			PORTD &= ~(1 << LED);
	}
 
}