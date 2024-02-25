#define F_CPU 16000000UL

#include  <avr/io.h>
#include  <util/delay.h>

void serial_begin()
{
  UBRR0  = 103;
  UCSR0A = 0x00;
  UCSR0B = 0x18;
  UCSR0C = 0x06;
}

void serial_putc(char data) {      
    char busy;
    do { busy = UCSR0A & 0b00100000; }
    while (busy==0);  
    UDR0 = data;         
}

char serial_getc() {    
     char busy;
     do { busy = UCSR0A & 0b10000000; }
     while (busy==0);     
     return(UDR0);  
}

void serial_puts(char *data) {
    while (*data){
       serial_putc(*data++);
    }    
}

int main(void) {
    char ans;  
    
    serial_begin();
    DDRD = 0x70;
    while(1)
    {
       serial_puts("TURN ON LED? (y/n) : ");
       ans = serial_getc();
       char tmp = serial_getc();
       serial_putc(ans);
       
       serial_puts("\n\n");
       if      (ans=='y') PORTD = PORTD | 0x10;
       else if (ans=='n') PORTD = PORTD & ~0x10; 
       
       else    serial_puts("Wrong Input. Please Try Again \n\n");   
    }      
}