
#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Autenticación de la red FLER
const char* ssid = "FLER"; 
//const char* password = "fler123";   //

//Sensores
float hums;
float temps;
float gass;

//Sensores Config
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE);
int INPUT_PIN = A0;


//delay
int timeTracker =0; 
int timeInterval= 1000;

ESP8266WebServer server(80);   

void handleRoot() {
           
        String s = "<> Humedad:  ";
        s += String(hums);
        s += " Temperatura: ";        
        s += String(temps);
        s += " Saturación: ";    
        s += String(gass);
        server.send(200,"text/html",s);     
}


void setup() {
  
  delay(200);                    
  Serial.begin(9600);           
  pinMode(INPUT_PIN, INPUT);
  Serial.setTimeout(2000);
  dht.begin(); 
  Wire.begin();

  //inicialización de comunicación Wifi
  WiFi.softAP(ssid);//, password);      
  IPAddress myIP = WiFi.softAPIP();    
  Serial.print("AP IP address: ");
  Serial.println(myIP);              
  server.on("/DataSensores", handleRoot);   
  server.begin();                     

}

void loop() {
  int currentTime=millis();
  if((currentTime-timeTracker)>timeInterval){
    timeTracker=currentTime;
  
//Inicia de lectura de Sensores
  hums = dht.readHumidity();
  temps = dht.readTemperature();
  gass = analogRead(INPUT_PIN);

  } 
  
  server.handleClient();

}
