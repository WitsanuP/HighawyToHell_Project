#define F_CPU 16000000UL

#include  <avr/io.h>
#include  <util/delay.h>
#include "dot.h"
#include "print.h"
char text[50];

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 
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
  serial_begin();
  serial_puts("start\n");
  dot_init();
  dot_clear();
  int adc0;

  adc_init();

   
  while(1) {
    dot(0,0b11011010);
    dot(1,0b11011010);
    dot(2,0b10011011);
    dot(4,0xFF);
    
    adc0 = adc_read(1);
    //PORTD = adc0    & 0b11111111;    
    //PORTB = adc0>>8 & 0b00000011;
    dot(6,adc0>>8);  
    dot(7,adc0);
    sprintf(text, BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(adc0>>8),BYTE_TO_BINARY(adc0));
    serial_puts(text+6);

    _delay_ms(1000); 

  }

  return(0);
  
}