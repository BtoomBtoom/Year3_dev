#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial s(3, 1); // RX, TX

void setup() {
  s.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  s.println("yolo mother fucker");
  // put your main code here, to run repeatedly:
}