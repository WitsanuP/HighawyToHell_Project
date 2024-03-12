
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