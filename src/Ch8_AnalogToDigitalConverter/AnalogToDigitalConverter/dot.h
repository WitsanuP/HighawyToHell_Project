#include <SPI.h>

#define register_Digit(x) (0x1+(x))  //address D15-D8 HEX CODE
#define register_DecodeMode 0x09
#define register_intensity 0x0A
#define register_Scanlimit 0x0B
#define register_Shutdown 0x0C
#define register_Displaytest 0x0F
#define CS 0x0A
#define MOSI 0x0B
#define CLK 0x0D
const byte c[8]={0,0,0,0,0,0,0,0};

const byte tri[]={0x80,0xC0,0xA0,0x90,0x88,0x84,0x82,0xFF};

void dot_clear();
void senddata(uint8_t address, uint8_t data);
void dot_init(void);
void dot(int row,int col);

void senddata(uint8_t address, uint8_t data){  //Serial-data(16bit)
digitalWrite(CS, LOW);
SPI.transfer(address);//D15-D8  //SPI.transfer(val)
SPI.transfer(data);//D7-D0
digitalWrite(CS, HIGH);
}
void dot_init(void){
  //debug
  pinMode(CS, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);//88
  SPI.setDataMode(SPI_MODE0);
  senddata(register_Shutdown, 0x00);
  senddata(register_DecodeMode, 0x00);
  senddata(register_intensity, 0x01);
  senddata(register_Scanlimit, 0x07);
  senddata(register_Displaytest, 0x00);
  senddata(register_Shutdown, 0x01);
  dot_clear();
}

void dot(int row,int col){
  senddata(row+1, col);
}

void dot_clear(void){
  for (int j=0;j<8;j++){
      senddata(j+1, c[j]);
    }
    delay(100);
}

