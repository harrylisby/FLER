#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
char ssid[] = "Alonso";
char pass[] = "karla%21";
IPAddress server(192, 168, 1, 1);
WiFiClient client;
float hums;
float temps;
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE);



void setup()
{
  Serial.begin(9600); 
  dht.begin(); 
  Wire.begin();
  //Wire.setClock(400000);
  //mySensor.setI2CAddress(0x76);
 // mySensor.beginI2C();
  WiFi.begin(ssid, pass);      
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop(){ 
  hums = dht.readHumidity();
  temps = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(hums, 2);
  Serial.print(" Temperature: ");
  Serial.print(temps, 2);
  Serial.println();
  client.connect(server, 80);   
  client.println(hums,2);
  client.flush();
  delay(500);
  client.println(temps,2);
  client.flush();
  delay(2000);
}
