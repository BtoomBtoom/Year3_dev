#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Timer.h>
#include <ArduinoJson.h>
#include <string.h>
#include <SPI.h>
#include <math.h>

#include "RTClib.h" //DS3231 library
RTC_DS3231 rtc;

#include "MHZ19.h"  // MHZ19 library
MHZ19 myMHZ19;

#include "SHT2x.h"  //SHT21 library
SHT2x sht;

#include "Adafruit_TCS34725.h"  //TCS34725 - Sensor RGB
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

#include <BH1750.h> //BH1750 library - light sensor
BH1750 lightMeter;

#include "Adafruit_CCS811.h"  // CCS811 library - Gas senssor
Adafruit_CCS811 ccs;

SoftwareSerial UART1(PIN_PD2, PIN_PD3); //RX, TX
SoftwareSerial UART3(PIN_PE4, PIN_PE5); //RX, TX

Timer t;

// variable for data
int ID = 8;
String Time_Stamp;
float temp = 0, humid = 0;
double CO2 = 0;
uint16_t r = 0, g = 0, b = 0, c = 0, colorTemp, lux;
float light = 0;
bool motion = 0; float motiontime = 0, totalread = 0;
int sound = 0;
float dust = 0;
int CO2_gas = 0, TVOC = 0;

// function run follow timer
void Read_Co2(void *context){
  CO2 = myMHZ19.getCO2();
}

void Read_temp_humid(void *context){
   if ( sht.isConnected()  )
  {
    sht.read();

    sht.getError();
    sht.getStatus();

    temp = sht.getTemperature();
    humid = sht.getHumidity();
  }
  else
  {
    Serial.print("\tNot connected:\t");
    sht.reset();
  }
}

void Read_RGB(void *context){
  tcs.getRawData(&r, &g, &b, &c);

  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
}

void Read_Light(void *context){
    if (lightMeter.measurementReady()) {
    light = 2*lightMeter.readLightLevel();}

}


void Read_Gas(void *context){
  if(ccs.available()){
    if(!ccs.readData()){
      TVOC = ccs.getTVOC();
    }
    else{
      Serial.println("ERROR CCS811!");
    }
  }
}

void Motion(void *context) {
  if (digitalRead(PIN_PE7))   // PIR pin is PE7
    motiontime++;

  totalread++;
}

void Read_Sound(void *context)
{
  sound = analogRead(PIN_PF0);// MAX9814 Pin is PF0
}

void Read_Dust(void *context) {   

  int dustVal = 0;
  float voltage = 0;
  float dustdensity = 0;
  
  digitalWrite(PIN_PF1, LOW); // power on the LED PF1
  delayMicroseconds(280);
  dustVal = analogRead(PIN_PA1); // read the dust value
  delayMicroseconds(40);
  digitalWrite(PIN_PF1, HIGH); // turn the LED off

  voltage = dustVal * 0.0049; //dustval*5/1024
  dustdensity = 0.172 * voltage - 0.1;

  if (dustdensity < 0)
    dustdensity = 0;
  if (dustdensity > 0.5)
    dustdensity = 0.5;
    
  dust = dustdensity * 1000;
}

void Send_Data(void *context)
{
    if (motiontime/totalread >= 0.5) 
    {motion = true;}
  else
    {motion = false;}
    
    motiontime = 0;
    totalread = 0;

  DateTime time = rtc.now();


  StaticJsonDocument<500> doc;
    doc["operator"] = "sendData";
    doc["id"] = ID;
  
    doc["info"]["time"] = time.unixtime()-7*3600;
    doc["info"]["red"] = r;
    doc["info"]["green"] = g;
    doc["info"]["blue"] = b;
    doc["info"]["c"] = c;
    doc["info"]["Colortemp"] = colorTemp;
    doc["info"]["lux"] = lux;
    doc["info"]["light"] = light;
    doc["info"]["co2"] = CO2;
    doc["info"]["dust"] = dust;
    doc["info"]["tvoc"] = TVOC;
    doc["info"]["motion"] = motion;
    doc["info"]["sound"] = sound;
    doc["info"]["temperature"] = temp;
    doc["info"]["huimidity"] = humid;

    doc["status"] = 0;
  serializeJson(doc, UART1);


}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
/************************************SETUP_BASE************************************/
  Wire.begin();
  UART1.begin(9600);
  while (!UART1){};
  pinMode(PIN_PB4, OUTPUT);

/************************************SETUP_MHZ19***********************************/
  UART3.begin(9600);  // begin UART for CO2 sensor MHZ19
  while (!UART3){};
  myMHZ19.begin(UART3);

/************************************SETUP_SHT21***********************************/
  sht.begin();  // begin SHT sensor

/************************************SETUP_RTC_DS3231******************************/
  if (! rtc.begin()) {
    while (1);
  }

  if (rtc.lostPower()) {
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // 2022-06-25T17:07:00 you would call:
    rtc.adjust(DateTime(2022, 6, 29, 22, 15, 00));
  }

/************************************SETUP_TCS34725_RGB*****************************/
  // if (tcs.begin()) {
  //   // Serial.println("Found sensor");
  // } else {
  //   // Serial.println("No TCS34725 found ... check your connections");
  //  }

/************************************SETUP_BH1750_LIGHT*****************************/
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);

/************************************SETUP_BH1750_LIGHT*****************************/
  ccs.begin();

/************************************SETUP_TIMERLOOP********************************/
  t.every(10000, Send_Data, (void*) 0);  // t.every(msforloop, function called, (void*)0)
  t.every(10000, Read_Co2, (void*) 0);
  t.every(5000, Read_temp_humid, (void*) 0);
  t.every(15000, Read_RGB, (void*) 0);
  t.every(20000, Read_Light, (void*) 0);
  t.every(25000, Read_Gas, (void*) 0);
  t.every(1000, Motion, (void*) 0);
  t.every(30000, Read_Sound, (void*) 0);
  t.every(35000, Read_Dust, (void*) 0);
}

void loop(){
  t.update();
}