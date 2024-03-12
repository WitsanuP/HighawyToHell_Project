// input text(1-9) and print on dot matrix
#define F_CPU 16000000UL
#define UART_RX_vect _VECTOR(18)

#include <avr/io.h>
#include <util/delay.h>
#include "sumek.h"
#include "font.h"
uint8_t index = 0;
char text[20] = "1347";
int indexisr = 0;
ISR(UART_RX_vect)  // Replace serial_getc
{
  text[indexisr] = UDR0;
  serial_putc(text[indexisr]);
  indexisr++;
  text[indexisr] = NULL;
  index = 1;
  if (UDR0 == 10) {
    text[indexisr-1] = NULL;
    indexisr = 0;
    serial_putsln("newline");
  }
  /*
  int itmp =0;
  while(text[itmp]!=NULL){
    if(text[itmp]==10)serial_putsln("KUY");
    serial_putc(text[itmp]);
    itmp++;
  }*/
}
int main(void) {
  max7219_init();
  serial_begin();
  //Serial.begin(9600);

  while (1) {
    serial_putc('j');
    while (text[index] != NULL) {
      //Serial.println(text[index]);
      //if(text[index]==NULL)Serial.println("find null");
      for (int j = 0; j < 8; j++) {    //shift flame{}
        for (int i = 0; i < 8; i++) {  // บรรทัด
          if (text[index + 1] != NULL)
            max7219_wr(i + 1, Number[text[index] - '0'][i] << j | Number[text[index + 1] - '0'][i] >> (8 - j));
          else

            max7219_wr(i + 1, Number[text[index] - '0'][i] << j);


          serial_putc('p');
        }
        _delay_ms(200);
      }
      index++;
    }

    index = 0;
  }
}
