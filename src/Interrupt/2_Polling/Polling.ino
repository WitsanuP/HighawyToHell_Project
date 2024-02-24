#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

char red = 0;
char button;
/* 
PD2 Buttom_1
PD3 Buttom_2

PD4 LED_Red
PD5 LED_Yellow
PD6 LED_Green
*/
int main (void){
  
  DDRD = 0b00110000;
  // PD4,5 output
  // PD2   input

  while(1){

    PORTD = PORTD & 0b11011111;//off
    _delay_ms(1000);
    PORTD = PORTD | 0b00100000; //on
    _delay_ms(1000);

    button = PIND & 0b00000100;

    if(button == 0){
      red = ~red;
      
      if(red==0){
        PORTD = PORTD & 0b11101111; //off
      }
        
      else {
        PORTD = PORTD | 0b00010000; //on
      }
    }
  }
}