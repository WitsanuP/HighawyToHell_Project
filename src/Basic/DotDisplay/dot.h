#include <SPI.h>

#define register_Digit(x) (0x1+(x))  //address D15-D8 HEX CODE
#define register_DecodeMode 0x09
#define register_intensity 0x0A
#define register_Scanlimit 0x0B
#define register_Shutdown 0x0C
#define register_Displaytest 0x0F
#define CS 0x0A  // Change to the actual CS pin number
#define MOSI 0x0B
#define CLK 0x0D

const byte c[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void dot_clear();
void senddata(uint8_t address, uint8_t data);
void dot_init(void);
void dot(int row, int col);

void senddata(uint8_t address, uint8_t data) {
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(CS, HIGH);
}

void dot_init(void) {
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);  // Ensure CS is HIGH before SPI initialization
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);  // 88
  SPI.setDataMode(SPI_MODE0);
  senddata(register_Shutdown, 0x00);
  senddata(register_DecodeMode, 0x00);
  senddata(register_intensity, 0x01);
  senddata(register_Scanlimit, 0x07);
  senddata(register_Displaytest, 0x00);
  senddata(register_Shutdown, 0x01);
  // dot_clear();  // You may uncomment this if you want to clear the display during initialization
}

void dot(int row, int col) {
  senddata(row + 1, col);
  // delay(100);  // Depending on your requirements, you may adjust or remove this delay
}

void dot_clear(void) {
  for (int j = 0; j < 8; j++) {
    senddata(j + 1, c[j]);
  }
  // delay(100);  // Depending on your requirements, you may adjust or remove this delay
}
