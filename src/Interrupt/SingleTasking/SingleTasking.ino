#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main (void){
  DDRB = 0b00100000;//D13 or LED_bult-in
  while(1){
    PORTB = PORTB & 0b11011111;//off
    _delay_ms(1000);
    PORTB = PORTB | 0b00100000;//on
    _delay_ms(1000);
  }
}