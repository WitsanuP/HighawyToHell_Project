#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "sumek.h"
int main(void) {
  max7219_init();
  uint8_t temp[8];
  Serial.begin(9600);
  while (1) {
    /*
    for(int i = 0;i<=8;i++){
      max7219_wr(i,0);
    }
    _delay_ms(200);
    */
    uint8_t text[][8]{
      { 0x7c, 0x7e, 0x63, 0x63, 0x7e, 0x7c, 0x60, 0x60 },  //P
      { 0x00, 0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x3c },  //o
      { 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c }   //l
    };
    uint32_t sctext[] = { 0x7c0000, 0x7e0038, 0x630018, 0x633c18, 0x7e6618, 0x7c6618, 0x606618, 0x603c3c };
Serial.println("fjdk");
    for (int j=0; j < 32; j++) {
      Serial.println("no3");
      for(int k = 0;k<8;k++)
      temp[k] = 0xFF & sctext[k] >> j;
      for (int i = 0; i < 8; i++) {
        max7219_wr(i + 1, (temp[i]));
        Serial.println("fjdk32");
      }
      _delay_ms(500);//delay time flame
    }
    //_delay_ms(1000);//delay for end 
  }
  
}
