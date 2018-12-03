//Client ESP8266


#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESPUI.h>
#include "Nextion.h"

const char ssid[] = "FLER";
const char pass[] = "fler12345";
IPAddress server(192, 168, 4, 2);
WiFiClient client;

//Peteción de data
String request;
String data;

//Sensores
float hums;
float temps;
float gass;


void setup() {
//Inicialización de STA

 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, pass);


}

void loop() {

//Petecion de valores de cada sensor
  client.connect(server, 80);   
  client.println(hums,2);
  client.flush();
  delay(500);
  client.println(temps,2);
  client.flush();
  delay(2000);

//Impresión de datos a LCD

  data = "temps.txt=\"" + String(temps, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  data = "hums.txt=\"" + String(hums, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  data = "gass.txt=\"" + String(gass, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  data = "temps.txt=\"" + String(temps, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  
}
