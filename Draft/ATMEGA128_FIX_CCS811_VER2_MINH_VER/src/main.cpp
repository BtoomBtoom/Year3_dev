/**
 * @authors
 *
 * @brief read and send data from sensors to esp07
 *
 */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Timer.h>
#include <ArduinoJson.h>
#include <string.h>
#include <SPI.h>
#include <math.h>
#include "lib.cpp"

/*set softSerial: UART1 for comunicating with Esp07, UART3 for reading data from CO2 sensor MHZ19*/
SoftwareSerial UART1(PIN_PD2, PIN_PD3); // RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); // RX, TX

/*include library for sensors*/

Adafruit_CCS811 ccs;

/*global variables for mesured values*/
Timer t;
const int ID = 8;
float temp = 0, humid = 0;
int CO2 = 0;
uint16_t r = 0, g = 0, b = 0, c = 0;
int light = 0;
int total = 0, motion = 0, now = 0; // total count times of read, motion count time had
float sound = 0;
float dust = 0;
int CO2_gas = 0, TVOC = 0;
int status = 0;

float ccs811C02 = 0, ccs811Tvoc = 0;



/*Round value to 2 decimal*/
float RoundUp(float value)
{
   return ceil(value * 100) / 100;
}

/*read Co2 from MHZ19*/

void sendData(void *context)
{
   StaticJsonDocument<500> doc;
   doc["infor"]["test"] = "---------------------------";
   doc["infor"]["CCS811Co2"] = ccs811C02;
   doc["infor"]["CCS811Tvoc"] = ccs811Tvoc;
   // doc["operator"] = "sendData";
   // doc["id"] = ID;

   // doc["info"]["time"] = rtc.now().unixtime()-7*3600;    //unix timestamp
   // doc["info"]["red"] = r;                               // 16 bit
   // doc["info"]["green"] = g;                               // 16 bit
   // doc["info"]["blue"] = b;                              // 16 bit
   // doc["info"]["clear"] = c;                             // 16 bit
   // doc["info"]["light"] = RoundUp(light);                // lux
   // doc["info"]["co2"] = CO2;                             // ppm
   // doc["info"]["dust"] = RoundUp(dust);                  // ug/m3
   // doc["info"]["tvoc"] = RoundUp(TVOC);
   // doc["info"]["motion"] = MOTION();                     // logic
   // doc["info"]["sound"] = RoundUp(sound);                // db
   // doc["info"]["temperature"] = RoundUp(temp);           // cencius
   // doc["info"]["humidity"] = RoundUp(humid);             // %

   // doc["status"] = status;
   serializeJson(doc, UART1);
}

JsonObject mes;

    //////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{

   
   /*UART1 for comunication with ESP07*/
   UART1.begin(9600);
   while (!UART1);

}

void loop()
{
   if (ccs.available())
   {
      if (!ccs.readData())
      {
         mes["eco2"] = ccs.geteCO2();
         mes["tvoc"] = ccs.getTVOC();
      }
   }
   serializeJson(mes, UART1);
}