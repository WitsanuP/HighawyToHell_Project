#define INT0_vect _VECTOR(1)    // External Interrupt
#define INT1_vect _VECTOR(2)    // External Interrupt
#define TIMER1_OVF _VECTOR(13)  //timer 1 overflow
//#define time_ms(t) t*16000/1024
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
//declaer function
void serial_begin();
void serial_putc(char data);
void serial_puts(char *data);
uint32_t time2counter(uint32_t t);
uint32_t counter2time(uint32_t t);

//LEd green yellow red
uint8_t led = 0b001;
uint8_t status_led = 0;  //up or down
uint16_t speed = 0xFFFF-1-time2counter(200);//65535-3125;
char txt[50];

ISR(INT0_vect) {
  status_led = ~status_led;
  if(status_led){
    sprintf(txt, "Red -> Yellow -> Green : %u ms\n", counter2time(0xFFFF-speed));
    serial_puts(txt);
  }
  else{
    sprintf(txt, "Green -> Yellow -> Red : %u ms\n", counter2time(0xFFFF-speed));
    serial_puts(txt);
  }
}

ISR(INT1_vect) {
 speed -= time2counter(200);
 
 if(counter2time(0xFFFF-speed)>1000)speed = 0xFFFF-1-time2counter(200);
  if(status_led){
    sprintf(txt, "Red -> Yellow -> Green : %u ms\n", counter2time(0xFFFF-speed));
    serial_puts(txt);
  }
  else{
    sprintf(txt, "Green -> Yellow -> Red : %u ms\n", counter2time(0xFFFF-speed));
    serial_puts(txt);
  }
}


ISR(TIMER1_OVF_vect) {
  PORTD = PORTD & ~0x70;
  //up and down
  if (status_led) {
    led = led << 1;
    if (led == 0b1000) led = 0b001;
  }
  else{
    led = led >> 1;
    if (led == 0b000) led = 0b100;
  }
  //turn on led with state
  if (led == 0b001) {
    PORTD = PORTD | 0x10;  
  } else if (led == 0b010) {
    PORTD = PORTD | 0x20;  
  } else if (led == 0b100) {
    PORTD = PORTD | 0x40; 
  }

  TCNT1 = speed;  //1518;//3036;
}

int main() {
  serial_begin();
  //set I/O port
  DDRD = 0x70;

  //set INT
  EICRA = EICRA | 0x02;//mode of INT0
  EICRA = EICRA | 0x08;//mode of INT1 
  EIMSK = EIMSK | 0x03;//Enable : INT0 = 0x01, INT1 = 0x02, both INT = 0x03

  //set TMR1
  TCCR1A = 0x00;
  TCCR1B = 0x05;  //101 set prescale 1024
  TCNT1 = 65535-3125;   //65536-62500
  TIMSK1 = 0x01;  // overflow interrupt

  sei();  //turn on global interrupts


  while (1);
  
}

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
void serial_puts(char *data) {
    while (*data){
       serial_putc(*data++);
    }    
}

uint32_t time2counter(uint32_t t){
  return t*16000/1024;
}
uint32_t counter2time(uint32_t t){
  return t*1024/16000;
}