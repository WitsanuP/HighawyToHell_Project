#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int main()
{
	uint16_t  Count;

	DDRD |= (1 << PD5);

	TCCR1A = 0b00000000;
	TCCR1B = 0b00000101; 

	TCNT1 = 0;
	while ( 1) {
		Count = TCNT1;
		if ( (PORTD & (1 << PD5)) && (Count > 2929)) {
			PORTD &= ~(1 << PD5);
			TCNT1 = 0;
			Count = 0;
		}
		if ( !(PORTD & (1 << PD5)) && (Count > 2929)) {
			PORTD |= (1 << PD5);
			TCNT1 = 0;
		}
	}
}