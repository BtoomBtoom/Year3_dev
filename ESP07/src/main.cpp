#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <string.h>
#include <ArduinoJson.h>

const char* ssid = "MINHCHAU_2.4";
const char* password = "ETHANhunt(-)123";

// const char* ssid = "Nha Tro 21B_T3";
// const char* password = "dotienhai";

// const char* ssid = "Tang 6";
// const char* password = "66666666";

// const char* ssid = "iPAC_Lab";
// const char* password = "biogaslab";

// const char* mqtt_server = "broker.mqttdashboard.com";

const char* mqtt_server = "broker.hivemq.com";

//const char* mqtt_server = "192.168.31.215";
// const char* mqtt_server = "192.168.0.100"
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


#define topic "DATA 3"

SoftwareSerial UART2(13, 15); //  uart2 comuinicates with atmega128P

void setup_wifi()
{
  /*
     Initializing Wifi connections
     When wifi is connected, turn 2 off.
  */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(2, LOW);
    delay(250);
    digitalWrite(2, HIGH);
    delay(250);
  }
}

void reconnect() {
  /* Connecting to MQTT server*/
  // Loop until we're reconnected
  while (!client.connected())
  {
    // Signalizing a MQTT connection
    digitalWrite(2, LOW);
    delay(50);
    digitalWrite(2, HIGH);
    delay(50);

    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      /* If connection to MQTT server is successful, turn 2 on */
      digitalWrite(2, LOW);
      // Resubscribe to topic
      client.subscribe(topic);
    }
    else
    {
      /* If connection to MQTT server is failed, turn 2 off */
      digitalWrite(2, HIGH);
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  // Connecting to Wifi
  pinMode(2, OUTPUT);
  setup_wifi();

  // Connecting to MQTT server
  client.setServer(mqtt_server, mqtt_port);
  UART2.begin(9600);
  Serial.begin(9600);

}

void loop()
{
  // Reconnecting to MQTT server
  if (!client.connected()) {
    reconnect(); 
  }
  client.loop();

  /* Publishing a message to MQTT server */
  digitalWrite(2, HIGH);

  /* nhan du lieu tu uart */
  /* Finishing publish */
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
      client.publish(topic, msg);
    }
    else
    {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());
      // Flush all bytes in the "link" serial port buffer
      while (UART2.available() > 0)
        UART2.read();
    }
  }
}