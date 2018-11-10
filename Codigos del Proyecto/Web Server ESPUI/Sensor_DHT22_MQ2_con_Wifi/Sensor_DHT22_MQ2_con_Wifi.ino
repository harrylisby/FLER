#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESPUI.h>

const char ssid[] = "FLER";
const char pass[] = "fler12345";


ESP8266WebServer server(80); 
float hums;
float temps;
float gass;
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE);

int INPUT_PIN = A0;


void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("");
  
  
  pinMode(INPUT_PIN, INPUT);
  Serial.setTimeout(2000);
  dht.begin(); 
  Wire.begin();


  WiFi.mode(WIFI_AP);
  WiFi.hostname(ssid);
  //WiFi.softAP(ssid);
  WiFi.softAP(ssid, pass);
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

                 
  ESPUI.label("Humedad:", COLOR_TURQUOISE, String(hums));
  ESPUI.label("Temperatura:", COLOR_EMERALD, String(temps) );
  ESPUI.label("Saturación:", COLOR_WETASPHALT, String(gass) );
  ESPUI.begin("ESPUI Control");
  }


void loop(){ 

  server.handleClient(); 
  
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
//  client.connect(server, 80);
//  client.println (gass,2);
//  client.flush();
//  delay(100);   
//  client.println(hums,2);
//  client.flush();
//  delay(100);
//  client.println(temps,2);
//  client.flush();
 delay(1000);
}
