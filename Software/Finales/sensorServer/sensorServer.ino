#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//#define UART_COMMS; //Activa UART ET

#ifdef UART_COMMS
#include <EasyTransfer.h>

EasyTransfer ET;

struct SEND_DATA_STRUCTURE{
  //Exactamente la misma estructura en el otro microcontrolador.
  int16_t valZ;
  int16_t valY;
  int16_t valX;
  int16_t valG;
  int16_t valI;
  int16_t valR;
};
//nombre de la estructura
SEND_DATA_STRUCTURE controlData;

#endif //UART_COMMS


const char* ssid = "FLER";  // SSID of esp8266
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

ESP8266WebServer server(80);    //Specify port for TCP connection

void handleRoot() {
           
        String s = "<> Humedad:  ";
        s += String(hums);
        s += " Temperatura: ";        
        s += String(temps);
        s += " Saturación: ";    
        s += String(gass);
        server.send(200,"text/html",s);      //Reply to the client
}


void setup() {
  delay(200);                           //Stable Wifi
  Serial.begin(9600);                 //Set Baud Rate
  pinMode(2, OUTPUT);                   //Led/Solenoid at pin 2
  pinMode(INPUT_PIN, INPUT);
  Serial.setTimeout(2000);
  dht.begin(); 
  Wire.begin();

  //inicializacion de com Wifi
  WiFi.softAP(ssid);//, password);      //In Access Point Mode
  IPAddress myIP = WiFi.softAPIP();     //Check the IP assigned. Put this Ip in the client host.
  Serial.print("AP IP address: ");
  Serial.println(myIP);                 //Print the esp8266-01 IP(Client must also be on the save IP series)
  server.on("/DataSensores", handleRoot);           //Checking client connection
  server.begin();                       // Start the server
  Serial.println("Server started");

  //UART - EasyTransfer
#ifdef UART_COMMS
  ET.begin(details(controlData),Serial);
#endif UART_COMMS

}

void loop() {
#ifdef UART_COMMS  
  ET.sendData();
#endif

  int currentTime=millis();
  if((currentTime-timeTracker)>timeInterval){
    timeTracker=currentTime;
  
  //Inicia de lectura de Sensores
  hums = dht.readHumidity();
  temps = dht.readTemperature();
  gass = analogRead(INPUT_PIN);

  } 
  // Check if a client has connected. On first connection switch on the Solenoid on next switch off.
  server.handleClient();

}