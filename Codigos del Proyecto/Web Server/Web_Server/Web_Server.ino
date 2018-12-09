///server ESP8266

#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


//Configuración Wifi
const char* ssid = "FLER";
//const char pass[] = "fler12345";

ESP8266WebServer server(23);

void handleRoot(){
  String s = "\r\n\r\n <!DOCTYPE>\r\n<html><h1>Esp8266 Communication</h1>";
  s += "<p>Success!!!</html\r\n\r\n";
  server.send(200,"text/html",s); 
}



//Almacenamiento de Sensores
float hums;
float temps;
float gass;



//Configuración de Sensores
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE);
int INPUT_PIN = A0;

//Delay
int timeTracker =0; 
int timeInterval= 1000;


void setup() {


//Iniciar Sensores

  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
  Serial.setTimeout(2000);
  dht.begin(); 
  Wire.begin();
  
//Inicialización  de Access Point
 //WiFi.mode(WIFI_AP);
 // WiFi.hostname(ssid);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(myIP);
  server.on("/gass", handleRoot);
  server.begin();
  Serial.println("Server Started ");

//server.begin();
}

void loop() {

  int currentTime=millis();
  if((currentTime-timeTracker)>timeInterval){
    timeTracker=currentTime;
  

  //Inicia de lectura de Sensores
  hums = dht.readHumidity();
  temps = dht.readTemperature();
  gass = analogRead(INPUT_PIN);

  //Impresión de Valores en Monitor Serial
  Serial.print("Humidity: ");
  Serial.print(hums, 2);
  Serial.print(" Temperature: ");
  Serial.print(temps, 2);
  Serial.print(" Gas: ");
  Serial.print(gass, 2);
  Serial.println();

  //Revisa si el client esta conectado
  server.handleClient();
  }
}
