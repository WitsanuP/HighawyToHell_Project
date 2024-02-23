#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
/* notice
PD2 Buttom_1
PD3 Buttom_2

PD4 LED_Red
PD5 LED_Yellow
PD6 LED_Green
*/
int main()
{
	DDRD |= (1 << PD5);
	DDRD |= (1 << PD4);

	DDRD &= ~(1 << PD2);
	DDRD &= ~(1 << PD3);

	while ( 1) {
		PORTD &= ~(1 << PD4);
		__builtin_avr_delay_cycles( 1000000 );
		__builtin_avr_delay_cycles( 1000000 );
		__builtin_avr_delay_cycles( 1000000 );
		PORTD |=  (1 << PD4);
		__builtin_avr_delay_cycles( 1000000 );
		__builtin_avr_delay_cycles( 1000000 );
		__builtin_avr_delay_cycles( 1000000 );

		if ( !(PIND & (1<<PD2)) ) 
			PORTD |= (1 << PD5);
		if ( !(PIND & (1<<PD3)) ) 
			PORTD &= ~(1 << PD5);
      
  }
}