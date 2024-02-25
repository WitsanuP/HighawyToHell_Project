#define INT0_vect _VECTOR(1)// External Interrupt 
#define TIMER1_OVF _VECTOR(13) //timer 1 overflow
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

char yellow = 0;
char red   = 0;

ISR(INT0_vect){
  red = ~red;
  if (red == 0){
    PORTD = PORTD & ~0x10;
  }
  else {
    PORTD = PORTD | 0x10;
  }
    
}
ISR(TIMER1_OVF_vect){
  yellow= ~yellow;
  if(yellow == 0){
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

  //set INT0
  EICRA = EICRA | 0x02;
  EIMSK = EIMSK | 0x01;

  //set TMR1
  TCCR1A = 0x00;
  TCCR1B = 0x05; //101 set prescale 1024
  TCNT1 = 3036;//65536-62500
  TIMSK1 = 0x01;// overflow interrupt

  sei();//turn on global interrupts

  while(1);

}