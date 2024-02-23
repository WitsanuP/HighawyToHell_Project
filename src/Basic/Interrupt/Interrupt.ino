#define INT0_vect _VECTOR(1)                 // External Interrupt Request 0 
#define TIMER1_OVF_vect _VECTOR(13)       // Timer 1 Overflow 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

ISR(INT0_vect) 
{   
    if (PORTD == 0b00000100) 
    {
        PORTD = 0b00000001; 
    } 
    TCNT1 = 3036; 	
}

ISR(TIMER1_OVF_vect) 
{   
    if (PORTD  == 0b00000001) 
    {
        PORTD = 0b00000010; 
        TCNT1 = 49911;      
    } 
    else if (PORTD == 0b00000010)
    {
        PORTD =  0b00000100;
    }
}

int main() {
  //set port
    DDRD = 0b00000111; 
    //set i/o init
    PORTD = 0b00000100; 
    
    EICRA = EICRA | 0b00000000; //Set the edge trigger mode 
    EIMSK = EIMSK | 0b00000001; // Enable INT0 interrupts

    //set timer
    TCCR1A = 0b00000000;	// norm set
    TCCR1B = 0b00000101;	//Set prescaler to 1024
    TCNT1 = 0;            		// Reset Timer 1 count
    TIMSK1 = 0b00000001; 	// Enable Timer 1 overflow interrupts

    sei();         // Enable global interrupts
    while (1);
}
