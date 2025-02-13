//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
//----------------------------------------Include the ThingSpeak Library, Download here : https://github.com/mathworks/thingspeak-arduino
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <DHT.h>  // Including library for dht
#include <SoftwareSerial.h>
SoftwareSerial serial (0,1);
unsigned long previousMillis = 0;
 
String apiKey = "7U6I3TRHO3GTUBQP";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Tenda_BC78";     // replace with your wifi ssid and wpa2 key
const char *pass =  "zigron@123";
const char* server = "api.thingspeak.com";
 
#define DHTPIN 0 //pin where the dht11 is connected    
#define fan1 2
#define fan2 4
#define fan3 5
#define fan4 12
#define heater1 13
#define heater2 14
unsigned long maxtemp=100;
unsigned long mintemp=0;
unsigned long maxhum=100;
unsigned long minhum=0;
int fanstate1 = LOW;
int fanstate2 = LOW;
int fanstate3 = LOW;
int fanstate4 = LOW;
int heaterstate1 = LOW;
int heaterstate2 = LOW;
 
DHT dht(DHTPIN, DHT22);
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
       Serial.println(F("DHTxx test!"));
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  pinMode(fan3,OUTPUT);
  pinMode(fan4,OUTPUT);
  pinMode(heater1,OUTPUT);
  pinMode(heater2,OUTPUT);
  
   dht.begin();
 
     //  Serial.println("Connecting to ");
     //  Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
    //  while (WiFi.status() != WL_CONNECTED) 
    // {
    //        delay(500);
   //         Serial.print(".");
   //  }
   //   Serial.println("");
   //   Serial.println("WiFi connected");
 
}
 
void loop() 
{

      unsigned long currentMillis = millis();
         if (Serial.available()>0)
  {
    String val = Serial.readStringUntil('\n');
    if ((val[0]>=48)&&(val[0]<=57))
    {
   char delimiter1 = ',';
   char delimiter2 = ';';
   char delimiter3 = ':';
   int delimiterPos1 = val.indexOf(delimiter1);
   int delimiterPos2 = val.indexOf(delimiter2);
   int delimiterPos3 = val.indexOf(delimiter3);
   String substring1 = val.substring(0, delimiterPos1);
   Serial.println(substring1);
   String substring2 = val.substring(delimiterPos1 + 1,delimiterPos2);
   Serial.println(substring2);
   String substring3 = val.substring(delimiterPos2 + 1,delimiterPos3);
   Serial.println(substring3);
   String substring4 = val.substring(delimiterPos3+1);
   Serial.println(substring4);
    
    Serial.println(val);
    maxtemp = substring1.toInt();
    mintemp = substring2.toInt();
    maxhum = substring3.toInt();
    minhum = substring4.toInt();
    }
    if(val[0]==65){
       Serial.println(val);
    fanstate1= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==97){
     Serial.println(val);
    fanstate1= LOW;
     
  }
  if(val[0]==66){
       Serial.println(val);
    fanstate2= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==98){
     Serial.println(val);
    fanstate2= LOW;
     
  }
  if(val[0]==67){
       Serial.println(val);
    fanstate3= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==99){
     Serial.println(val);
    fanstate3= LOW;
     
  }
  if(val[0]==68){
       Serial.println(val);
    fanstate4= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==100){
     Serial.println(val);
    fanstate4= LOW;
     
  }
  if(val[0]==69){
       Serial.println(val);
    heaterstate1= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==101){
     Serial.println(val);
    heaterstate1= LOW;
     
  }
  if(val[0]==70){
       Serial.println(val);
    heaterstate2= HIGH;
     previousMillis = currentMillis;
      
  }
  if (val[0]==102){
     Serial.println(val);
    heaterstate2= LOW;
     
  }
  }
      
      if (currentMillis - previousMillis >= 1000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
      
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                            // Serial.print("Temperature: ");
                             Serial.print(t);
                            // Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                            // Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
         // Serial.println("Waiting...");
         if (h>maxhum){
    fanstate1= HIGH;
    fanstate2= HIGH;
    fanstate3= HIGH;
    fanstate4= HIGH;
    
  }
  if (h<minhum) {
    fanstate1= LOW;
    fanstate2= LOW;
    fanstate3= LOW;
    fanstate4= LOW;
    
  }
  if (t<mintemp){
    heaterstate1= HIGH;
    heaterstate2= HIGH;
  }
  if (t>maxtemp) {
    heaterstate1= LOW;
    heaterstate2= LOW;
  }
  
  }
  
  // thingspeak needs minimum 15 sec delay between updates
  //delay(1000);
  digitalWrite(fan1,fanstate1);
  digitalWrite(fan2,fanstate2);
  digitalWrite(fan3,fanstate3);
  digitalWrite(fan4,fanstate4);
  digitalWrite(heater1,heaterstate1);
  digitalWrite(heater2,heaterstate2);
}
