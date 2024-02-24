#define TIMER1_OVF _VECTOR(13) //timer 1 overflow
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

char green = 0;

ISR(TIMER1_OVF_vect){
  green = ~green;
  if(green == 0){
    PORTD = PORTD & ~0x20;//off
  }
  else{
    PORTD = PORTD | 0x20;//on
  }
  TCNT1 = 3036;
}

int main(){
  //set I/O port
  DDRD = 0x70;
  //set TMR1
  TCCR1A = 0x00;
  TCCR1B = 0x05; //101 set prescale 1024
  TCNT1 = 3036;//65536-62500
  TIMSK1 = 0x01;// overflow interrupt

  sei();//turn on global interrupts

  while(1);

}