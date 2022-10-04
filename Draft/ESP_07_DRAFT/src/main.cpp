#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial s(3,1);
SoftwareSerial UART2(13,15);      //setup UART2 connect to atmega128

void setup() {
  // put your setup code here, to run once:
  s.begin(9600);
  UART2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (UART2.available())
  {
    //  Allocate the JSON document
    //  This one must be bigger than for the sender because it must store the strings
    // size is suggested by https://arduinojson.org/v6/assistant/#/step1
    StaticJsonDocument<512> doc;
    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, UART2.readString());

    if (err == DeserializationError::Ok)
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      char msg[400];
      serializeJson(doc, msg);
      s.println(msg);
    }
    else
    {
      // Print error to the "debug" serial port
      s.print("deserializeJson() returned ");
      s.println(err.c_str());
      // Flush all bytes in the "link" serial port buffer
      while (UART2.available() > 0)
        UART2.read();
    }
  }
}