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
char serial_getc() {    
     char busy;
     do { busy = UCSR0A & 0b10000000; }
     while (busy==0);     
     return(UDR0);  
}