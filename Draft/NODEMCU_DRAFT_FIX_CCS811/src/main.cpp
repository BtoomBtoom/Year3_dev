#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_CCS811.h>
#include <SPI.h>

Adafruit_CCS811 ccs; 

SoftwareSerial s(3, 1); // RX, TX

void setup()
{
  s.begin(9600);
  s.println("CSS TESTTTTTTTTTTTTTTTTTTTTTTT .................................");
      // put your setup code here, to run once:

  if(!ccs.begin())
  {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1);
  }

  // Wait for the sensor to be ready
  while (!ccs.available());
}

void loop()
{
  s.println("yolo mother fucker");
  if (ccs.available())
  {
    if (!ccs.readData())
    {
      s.print("CO2: ");
      s.print(ccs.geteCO2());
      s.print("ppm, TVOC: ");
      s.println(ccs.getTVOC());
    }
    else
    {
      s.println("ERROR!");
      while (1);
    }
  }
  delay(500);
  // put your main code here, to run repeatedly:
}