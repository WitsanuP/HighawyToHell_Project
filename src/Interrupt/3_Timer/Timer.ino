#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

char red = 0;
char green = 0;
char button;
/*
PD2 Buttom_1    0x04
PD3 Buttom_2	  0x08

PD4 LED_Red	    0x10
PD5 LED_Yellow	0x20
PD6 LED_Green	  0x40
*/
//serial.begin(9600);
int main (void){
  //set I/O port
  DDRD = 0x70;
Serial.begin(9600);
  //set timer
  TCCR1A = 0x00; 
  TCCR1B = 0b00000101;//bit0-2 set prescale 1024
  /*
  000 no prescaling
  001 1
  010 8 
  011 64
  100 256
  101 1024   max count 65535
  */
  TCNT1 = 0;//16bit counter:MAX 0xFFFF

/*
           time
count = ------------
        prescale *T
*/

  while(1){
    Serial.println(TCNT1,BIN);
    if (TCNT1>=62500)// 4 sec
    {
      Serial.println(green,BIN);
      Serial.print("grene");
      green = ~green;
      if(green == 0){
        PORTD = PORTD &(~0x40);//off PORTD5
      }
      else{
        PORTD = PORTD | 0x40;
      }
      TCNT1 = 0;
    }
  

  button = PIND & 0x04;
    if(button == 0){
     red = ~red;
     if(red == 0){
       PORTD = PORTD & ~0x10;// off led_red
     }
     else{
       PORTD = PORTD | 0x10;// on led_red
     }
     _delay_ms(100);
    }
  }
}