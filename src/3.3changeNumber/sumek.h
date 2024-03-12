
void spi_init(void){
  //Ser MOSI, SCK,Reset as Output
  DDRB= 0x2E;
  //Enable SPI,Ser as Master
  //Clock = 1MHz, F/16, Mode 0
  SPCR = 0x51;
  //Reset
  PORTB = PORTB & (0XFF-2);
  _delay_ms(100);
  PORTB = PORTB | 0x02;
  /*bug poteus
  PORTB = PORTB & 0b111111011;;
  _delay_ms(100);
  PORTB = PORTB | 0x02;
  */
}
void spi_putc(uint8_t data){
  char busy;
  //Load data into the buffer
  SPDR = data;
  //Wait until transmission complet
  do{ busy = SPSR & 0b10000000;}
  while(busy == 0 );

}
void max7219_wr(uint8_t addr,uint8_t data){
  PORTB = PORTB & (0xFF - 4);//SS = 0, SS is active low
  spi_putc(addr);
  spi_putc(data);
  PORTB = PORTB | 0x04;//SS = 1
}
void max7219_init(void){
  spi_init();
  max7219_wr(0x0C, 0); //Shutdown Mode
  max7219_wr(0x09, 0); //decoding mode OFF
  max7219_wr(0x0A, 15); //light intensity (0-15)
  max7219_wr(0x0B, 7); //scan limit: all digits ON
  max7219_wr(0x0C, 1); //turn ON MAX7219
}
///////////////////////////serial
void serial_begin()
{
  UBRR0  = 103;               
  UCSR0A = 0b00000000;
  UCSR0B = 0b10011000;  // Enable RXCIE Rx Interrupt
  UCSR0C = 0b00000110;

  sei();  // Enable Global Interrupt
}

void serial_putc(char data) {      
    char busy;
    do { busy = UCSR0A & 0b00100000; }
    while (busy==0);  
    UDR0 = data;         
}

void serial_puts(char *data) {
    while (*data){
       serial_putc(*data++);
    }    
}
void serial_putsln(char *data) {
    while (*data){
       serial_putc(*data++);
    }    
    serial_putc(10);
}
char serial_getc() {    
     char busy;
     do { busy = UCSR0A & 0b10000000; }
     while (busy==0);     
     return(UDR0);  
}

void TextScrolling(int TimeDelay, const char *text, ...) {//scrolling text<TimeShow><text> <format, ... >
  //byte ArrayText[CountRealLetter(text)][8];
  //resize array
  ArrayText = (byte**)malloc(CountRealLetter(text) * sizeof(byte*));
  for (int i = 0; i < CountRealLetter(text); i++) {
    ArrayText[i] = (byte*)malloc(8 * sizeof(byte));
  }

  if (text == NULL) return 0; //check case without text

  va_list valist;
  va_start(valist, text);

  int num = 0;

  int i = 0; //index รวม%
  int j = 0;//index ไม่รวม%_
  int len = strlen(text);
  int found = 0;
  while ( text[i] != NULL)
  {
    num = 0;
    found = 0;

    if ( ( text[i] == '%' ) && ( ( i + 1 ) < len ) ) {
      switch ( text[i + 1] ) {
        case 's': {//sign 0-4
            found = 1;
            num = va_arg(valist, int);
            CopyArray(j, num, Sign);
            j++;
          }
          break;

        case 'p': {//pic 0-10
            found = 1;
            num = va_arg(valist, int);
            CopyArray(j, num, Pic);
            j++;
          }
          break;

        case 't': {//triagle
            found = 1;
            for (int i = 0; i < 8; i++) {
              ArrayText[j][i] = tri[i];
            }
            j++;
          }
          break;

      }
      if ( found != 0 ) {
        i += 2;
        continue;
      }
    }
    if (( 'a' <= text[i]) && ('z' >= text[i])) {
      CopyArray(j, text[i] - 'a', SmallLetter);
    }
    else if (( 'A' <= text[i]) && ('Z' >= text[i])) {
      CopyArray(j , text[i] - 'A', CapLetter);
    }
    else if (( '0' <= text[i]) && ('9' >= text[i])) {
      CopyArray(j , text[i] - '0', Num);
    }
    else if (text[i] == ' ') {
      for (int i = 0; i < 8; i++) {
        ArrayText[j][i] = c[i];
      }
    }
    j++;
    i++;
  }
  va_end(valist);
  //display scrolling text
  byte tmp[8];

  for (int i = 0; i < CountRealLetter(text) ; i++) { //loop word

    for (int j = 0; j < 8; j++) {
      for (int m = 0; m < 8; m++) {
        if (i + 1 >= CountRealLetter(text))
          tmp[m] = (ArrayText[i][m] << j) | (ArrayText[0][m] >> (8 - j)); //make frame
        else
          tmp[m] = (ArrayText[i][m] << j) | (ArrayText[i + 1][m] >> (8 - j)); //make frame
      }
      for (int k = 0; k < 8; k++) {
        SendPackets(k + 1, tmp[k]);// show each frame
      }
      delay (TimeDelay);
    }
    Clear();
  }
  //free mem
  for (int i = 0; i < CountRealLetter(text); i++)
    free(ArrayText[i]);
  free(ArrayText);
}