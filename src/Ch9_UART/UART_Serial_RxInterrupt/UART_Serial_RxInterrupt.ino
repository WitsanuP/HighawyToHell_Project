#define F_CPU 16000000UL
#define UART_RX_vect _VECTOR(18)

#include  <avr/io.h>
#include  <util/delay.h>

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
ISR(UART_RX_vect) // Replace serial_getc
{
  char ans;
  
  ans = UDR0;
  serial_putc(ans);
  char tmp = serial_getc();
  serial_puts("\n\n");

  if      ((ans=='y')|(ans=='Y'))  PORTD = PORTD | 0x10; 
  else if ((ans=='n')|(ans=='N'))  PORTD = PORTD & ~0x10;
  else    serial_puts("Wrong Input. Please Try Again \n\n");  
  
  serial_puts("TURN ON LED? (y/n) : ");     
}

int main(void) {
    
    serial_begin();
    DDRD = 0x70;

    serial_puts("TURN ON LED? (y/n) : ");
 
    while(1);     
}