
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
