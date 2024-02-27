#define F_CPU 16000000UL
#define UART_RX_vect _VECTOR(18)
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
  ((byte)&0x80 ? '1' : '0'), \
    ((byte)&0x40 ? '1' : '0'), \
    ((byte)&0x20 ? '1' : '0'), \
    ((byte)&0x10 ? '1' : '0'), \
    ((byte)&0x08 ? '1' : '0'), \
    ((byte)&0x04 ? '1' : '0'), \
    ((byte)&0x02 ? '1' : '0'), \
    ((byte)&0x01 ? '1' : '0')

#include <avr/io.h>
#include <util/delay.h>
#include "dot.h"

//function declear
void serial_begin();
void serial_putc(char data);
void serial_puts(char *data);
char serial_getc();
void adc_init();
int adc_read(char ch);
char text[50];
int adc0;
ISR(UART_RX_vect)  // Replace serial_getc
{
  char ans;
  char digi[20];
  ans = UDR0;
  //serial_putc(ans);
  char tmp = serial_getc();
  serial_puts("\n\n");
  float volt = 5-float(adc0) / 1024 * 5;
  float resistance = 10 / ((5 / volt) - 1);
  float amp = volt / resistance;
  if (ans == '1') {
    char tmp[5];
    sprintf(digi, BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(adc0 >> 8), BYTE_TO_BINARY(adc0));

    dtostrf(resistance, 5, 2, tmp);

    sprintf(text, "Digital Value is %s, Resistance is %s kohm", digi + 6, tmp);
    serial_puts(text);
  } 
  else if (ans == '2') {

    char tmp[5];
    sprintf(digi, BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(adc0 >> 8), BYTE_TO_BINARY(adc0));
    dtostrf(volt, 5, 2, tmp);

    sprintf(text, "Digital Value is %s, Voltage is %s V", digi + 6, tmp);
    serial_puts(text);
  } 
  else if (ans == '3') {
    char tmp[5];
    sprintf(digi, BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(adc0 >> 8), BYTE_TO_BINARY(adc0));
    dtostrf(amp, 5, 2, tmp);

    sprintf(text, "Digital Value is %s, Current is %s mA", digi + 6, tmp);
    serial_puts(text);
  } else serial_puts("Wrong Input. Please Try Again \n\n");

  serial_puts("\n Select Ohmmeter (1), Voltmeter (2), Ammeter (3)");
}
int main() {
  serial_begin();
  serial_puts("\n======================================================\n\
  Select Ohmmeter (1), Voltmeter (2), Ammeter (3)\n");
  dot_init();
  dot_clear();
  adc_init();
  while (1) {
    adc0 = adc_read(1);
    dot(6,adc0>>8);  
    dot(7,adc0);
  }
}
////////////////////////////////////////////////////////////////

void serial_begin() {
  UBRR0 = 103;
  UCSR0A = 0b00000000;
  UCSR0B = 0b10011000;  // Enable RXCIE Rx Interrupt
  UCSR0C = 0b00000110;
  sei();  // Enable Global Interrupt
}

void serial_putc(char data) {
  char busy;
  do { busy = UCSR0A & 0b00100000; } while (busy == 0);
  UDR0 = data;
}

void serial_puts(char *data) {
  while (*data) {
    serial_putc(*data++);
  }
}
char serial_getc() {
  char busy;
  do { busy = UCSR0A & 0b10000000; } while (busy == 0);
  return (UDR0);
}
void adc_init() {
  // AREF = AVcc
  ADMUX = 0b01000001;
  // ADC Enable and prescaler of 128
  // 16000000/128 = 125000
  ADCSRA = 0b10000111;
}
int adc_read(char ch) {
  char busy;
  // Set Channel
  ADMUX = ADMUX & 0b11110000;
  ADMUX = ADMUX | ch;
  // Start Conversion
  ADCSRA = ADCSRA | 0b01000000;

  // wait for conversion to complete
  // ADSC becomes ’0? again
  do {
    busy = ADCSRA & 0b01000000;
  } while (busy != 0);

  return (ADC);
}
