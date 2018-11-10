//Codigo para Conectar el ESP8266 a Internet con los dos sensores  
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
float gass;
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE);

int INPUT_PIN = A0;


void setup()
{
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
  Serial.setTimeout(2000);
  dht.begin(); 
  Wire.begin();
  WiFi.begin(ssid, pass);      
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop(){ 
  
 
  hums = dht.readHumidity();
  temps = dht.readTemperature();
  gass = analogRead(INPUT_PIN);
  Serial.print("Humidity: ");
  Serial.print(hums, 2);
  Serial.print(" Temperature: ");
  Serial.print(temps, 2);
  Serial.print(" Gas: ");
  Serial.print(gass, 2);
  Serial.println();
  client.connect(server, 80);
  client.println (gass,2);
  client.flush();
  delay(100);   
  client.println(hums,2);
  client.flush();
  delay(100);
  client.println(temps,2);
  client.flush();
  delay(1000);
}
