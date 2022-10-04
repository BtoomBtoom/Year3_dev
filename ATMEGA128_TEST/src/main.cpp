#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); // RX, TX

void setup() {
  UART1.begin(9600);
  while(!UART1);

  
  // put your setup code here, to run once:
}




void loop() {
  UART1.println("Hello mother fucker!!!!!");
  // put your main code here, to run repeatedly:
}