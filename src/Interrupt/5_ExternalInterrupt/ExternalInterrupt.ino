#define INT0_vect _VECTOR(1)
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

char red = 0;

ISR(INT0_vect){
  red = ~red;
  if(red == 0){
    PORTD = PORTD & ~0x10;//off
  }
  else {
    PORTD = PORTD | 0x10;//on
  }
}
  int main(){
    //set I/O port
    DDRD = 0x70;
    // Interrupt on Falling Edge, INT0
    EICRA = EICRA | 0x02;
    // Enable INT0
    EIMSK = EIMSK | 0x01;
    // Turn on global interrupts
    sei();
    
    while(1){
      
    }
  }

