//it not working
#define F_CPU 16000000UL

#include  <avr/io.h>
#include  <util/delay.h>
#include "dot.h"
void adc_init()
{
    // AREF = AVcc
    ADMUX = 0b01000001;
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = 0b10000111;
}

int adc_read(char ch)
{      
  char busy;
  // Set Channel
  ADMUX  = ADMUX & 0b11110000;
  ADMUX  = ADMUX | ch;
  // Start Conversion
  ADCSRA = ADCSRA | 0b01000000;
 
  // wait for conversion to complete
  // ADSC becomes ’0? again  
  do
  {
    busy = ADCSRA & 0b01000000;
  }
  while(busy!=0);
 
  return (ADC);
}

int main(void)
{
  Serial.begin(9600);
  Serial.println("mine");
  
  int adc0;
  dot_init(); 
  Serial.println("hello");
  adc_init();
  //DDRD = 0x70; // PortD Output
   Serial.println("jame");
  
  while(1) {
    
     Serial.println("hi");
     //dot_point(2);
     //Blend285(200);
    dot(1,63);
    adc0 = adc_read(0);
    //PORTD = adc0    & 0b11111111;    
    //PORTB = adc0>>8 & 0b00000011;
    _delay_ms(500); 
    /*
    dot(6,adc0>>8);  
    dot(7,adc0);
    Serial.println(adc0,BIN);
    */
  }

  return(0);
  
}