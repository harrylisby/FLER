//Client ESP8266


//#include <DHT.h>
//#include <DHT_U.h>
//#include "Wire.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESPUI.h>
#include "Nextion.h"

//const char ssid[] = "FLER";
//const char pass[] = "fler12345";
const char* host = "192, 168, 4, 1";


//Peteción de data
String request;
String data;

//Sensores
float hums;
float temps;
float gass;


void setup() {
//Inicialización de STA
 Serial.begin(9600);
 WiFi.mode(WIFI_STA);
 WiFi.begin("FLER");

while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
Serial.print("");
Serial.print("WiFI Connected");
Serial.print("IP address: ");
Serial.print(WiFi.localIP());
}

void loop() {

Serial.print("connecting to");
Serial.print(host);
WiFiClient client;
const int httpPort = 23;
  if(!client.connect("192.168.4.1", httpPort)){
      Serial.println("connection failed");
      return;
  }
  
 client.print(String("GET ") +"/gass"+" HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "Connection: close\r\n\r\n"); 

//Petecion de valores de cada sensor
  client.println(hums, 2);
  client.flush();
  delay(500);
  client.println(temps, 2);
  client.flush();
  delay(2000);
  client.println(gass, 2);
  client.flush();
  

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
