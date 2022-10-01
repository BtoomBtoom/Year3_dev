#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Timer.h>
#include <ArduinoJson.h>
#include <string.h>
#include <SPI.h>
#include <math.h>

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX

#include "RTClib.h" 
RTC_DS3231 rtc;

#include "MHZ19.h"  
MHZ19 myMHZ19;

#include "SHT2x.h"  
SHT2x sht;

#include "Adafruit_TCS34725.h"  
Adafruit_TCS34725 tcs34725;

#include <BH1750.h> 
BH1750 bh1750;

Timer t;
const int ID = 4;
float temp = 0, humid = 0;
double CO2 = 0;
uint16_t r = 0, g = 0, b = 0, c = 0;
int light = 0;
int total = 0, motion = 0, now = 0; 
float sound = 0;
float dust = 0;
int CO2_gas = 0, TVOC = 0;
int status = 0;

float RoundUp(float value) 
{
  return ceil(value * 100) / 100; 
}

void readCo2(void *context)
{
  CO2 = myMHZ19.getCO2();
}

void readTH(void *context)
{
  if ( sht.isConnected()  )
  {
    sht.read();
    temp = sht.getTemperature();
    humid = sht.getHumidity();
  }
  else
  {
    sht.reset();
  }
}

void readRGB(void *context)
{
    tcs34725.enable();                      // Enables the device    
    tcs34725.setInterrupt(false);           // Turn on LED
    delay(60);                              // Take 50ms to read
    tcs34725.getRawData(&r, &g, &b, &c);
    tcs34725.setInterrupt(true);            // Turn off LED
    tcs34725.disable();                     // Disables the device (lower power sleep mode)
}

void readLight(void *context)
{
  static unsigned long previousTime = millis();
  if (millis() - previousTime > 5000)
  {   
    previousTime = millis();
    // we use here the maxWait option due fail save
    if (bh1750.measurementReady(true)) 
    {
      light = bh1750.readLightLevel();
      if (light < 0) 
      {
        light = 0;          
      } 
      else 
      {
        if (light > 40000.0) 
        {
          // reduce measurement time - needed in direct sun light
          bh1750.setMTreg(32);
        }
        if (light > 10.0) 
        {
          // typical light environment
          bh1750.setMTreg(69);
        }
        if (light <= 10.0) 
        {
          // very low light environment
          bh1750.setMTreg(138);
        }
      }
    }
  }
}

void readSound(void *context)
{
  unsigned long StartMillis = millis();

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - StartMillis < 50)
  {
    unsigned int sample = analogRead(PIN_PF0);

    if (sample<1024){
      if (sample > signalMax)
      {
        signalMax = sample;
      }
      else if (sample < signalMin)
      {
        signalMin = sample;
      }
    }
  }

  double volts = (signalMax - signalMin)*3.3/1024;

//with the microphone sensivity is -44db, so VRms/PA is 0.006309
  sound = 20.0*log10(volts/0.006309);
}

void readDust(void *context) 
{   
  float voltage = 0;
  digitalWrite(PIN_PF1, LOW);
  delayMicroseconds(280);
  voltage = analogRead(PIN_PA1) * 5.0 / 1023; // dustval*5/1024
  delayMicroseconds(40);
  digitalWrite(PIN_PF1, HIGH);

  if (voltage < 1)
  {
    voltage = 1;
  }  
  if (voltage > 3.55)
  {
    voltage = 3.55;
  }

  dust = (170*voltage - 100)/5; //ug/m3
}

void readMotion(void *context)
{
  unsigned long StartMillis = millis();
  int count = 0, haveMotion = 0;
  while (millis() - StartMillis < 50)
  {
    haveMotion += digitalRead(PIN_PE7);
    count++;
  }
  if(haveMotion*2 > count)
  {
    motion++;
    now = 1;
  }
  else
  {
    now = 0;
  }
  total++;
}

int MOTION()
{
  if (2*motion > total || now == 1)
  {
    motion = 0;
    total = 0;
    return 1;
  }
  else
  {
    motion = 0;
    total = 0;
    return 0;
  }
}

void sendData(void *context)
{
  StaticJsonDocument<500> doc;
  doc["operator"] = "sendData";
  doc["id"] = ID;

  doc["info"]["time"] = rtc.now().unixtime()-7*3600;
  doc["info"]["red"] = r;
  doc["info"]["green"] = g;
  doc["info"]["blue"] = b;
  doc["info"]["clear"] = c;
  doc["info"]["light"] = RoundUp(light);
  doc["info"]["co2"] = RoundUp(CO2);
  doc["info"]["dust"] = RoundUp(dust);
  doc["info"]["tvoc"] = RoundUp(TVOC);
  doc["info"]["motion"] = MOTION();
  doc["info"]["sound"] = RoundUp(sound);
  doc["info"]["temperature"] = RoundUp(temp);
  doc["info"]["humidity"] = RoundUp(humid);

  doc["status"] = status;
  serializeJson(doc, UART1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
/*UART1 for comunication with ESP07*/
  UART1.begin(9600);
  while (!UART1);

/*I2C for */
  Wire.begin();

/*PIN PF1 is led of dust sensor GP2Y1010AU0F, LOW level to turn on IR led*/
  pinMode(PIN_PF1, OUTPUT);
  digitalWrite(PIN_PF1, LOW);

/*RTC DS3231 setup; when lost power, time will have new setup*/
  while(!rtc.begin());
  if (rtc.lostPower())
    rtc.adjust(DateTime(2022, 9, 28, 10, 24, 30));

/*SHT21 setup*/
  sht.begin();

/*BH1750 Setup*/
  while (!bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE));

/*tcs3472534725 setup*/
  while (!tcs34725.begin());
  tcs34725.setIntegrationTime(TCS34725_INTEGRATIONTIME_614MS);
  tcs34725.setGain(TCS34725_GAIN_1X);

/*MHZ19 setup*/
  UART3.begin(9600);
  while (!UART3);
  myMHZ19.begin(UART3);
  myMHZ19.autoCalibration(true);
  // myMHZ19.autoCalibration(false);     // make sure auto calibration is off
  // myMHZ19.getABC();  // now print it's status
  //   /* if you don't need to wait (it's already been this amount of time), remove the 2 lines */
  // delay(12e5);    //  wait this duration
  // myMHZ19.calibrate();    // Take a reading which be used as the zero point for 400 ppm 

/*SETUP_TIMERLOOP: t.every(msforloop, function called, (void*)0)*/
  
  t.every(10000, readCo2, (void*) 0);
  t.every(10000, readTH, (void*) 0);
  t.every(10000, readRGB, (void*) 0);
  t.every(10000, readLight, (void*) 0);
  t.every(1000, readMotion, (void*) 0);
  t.every(10000, readSound, (void*) 0);
  t.every(10000, readDust, (void*) 0);
  t.every(10000, sendData, (void*) 0);
}

void loop(){
  t.update();
}