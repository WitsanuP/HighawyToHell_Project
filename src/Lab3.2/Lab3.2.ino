#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "sumek.h"
int main(void) {
  max7219_init();
  uint8_t temp[8];
  Serial.begin(9600);
  while (1) {

    uint32_t sctext[] = { 0x7c000000, 0x7e003800, 0x63001800, 0x633c1800, 0x7e661800, 0x7c661800, 0x60661800, 0x603c3c00 };
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
