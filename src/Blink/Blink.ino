#include <avr/io.h>
#include <avr/sleep.h>

int main() {
	DDRD |= (1 << PD4);
  DDRD |= (1 << PD5);
  DDRD |= (1 << PD6);
	while ( 1) {
		PORTD &= ~(1 << PD6);
		__builtin_avr_delay_cycles( 10000000 );

		PORTD |=  (1 << PD6);
		__builtin_avr_delay_cycles( 10000000 );
  }
}
