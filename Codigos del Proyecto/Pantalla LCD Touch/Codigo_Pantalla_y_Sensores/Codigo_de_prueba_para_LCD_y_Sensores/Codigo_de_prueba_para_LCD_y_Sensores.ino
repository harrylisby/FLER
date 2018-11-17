#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
#include <ESPUI.h>
#include "Nextion.h"



//Configuración Wifi
const char ssid[] = "FLER";
const char pass[] = "fler12345";


//Almacenamiento de Sensores
float hums;
float temps;
float gass;
String data;


//Configuración de Sensores
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE);
int INPUT_PIN = A0;

//Delay
int timeTracker =0; 
int timeInterval= 1000;

//Declaracion de objetos en la pantalla


//void padExample(Control sender, int value) {
//  switch (value) {
//  case P_LEFT_DOWN:
//    Serial.print("left down");
//    break;
//  case P_LEFT_UP:
//    Serial.print("left up");
//    break;
//  case P_RIGHT_DOWN:
//    Serial.print("right down");
//    break;
//  case P_RIGHT_UP:
//    Serial.print("right up");
//    break;
//  case P_FOR_DOWN:
//    Serial.print("for down");
//    break;
//  case P_FOR_UP:
//    Serial.print("for up");
//    break;
//  case P_BACK_DOWN:
//    Serial.print("back down");
//    break;
//  case P_BACK_UP:
//    Serial.print("back up");
//    break;
//  case P_CENTER_DOWN:
//    Serial.print("center down");
//    break;
//  case P_CENTER_UP:
//    Serial.print("center up");
//    break;
//  } 
//  Serial.print(" ");
//  Serial.println(sender.id);
//}

void setup(){
  //Iniciar Sensores
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
  Serial.setTimeout(2000);
  dht.begin(); 
  Wire.begin();

  //Inicialización  de Access Point
  WiFi.mode(WIFI_AP);
  WiFi.hostname(ssid);
  WiFi.softAP(ssid, pass);
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  //Inicialización de Interfaz Web               
  ESPUI.label("Humedad:", COLOR_WETASPHALT, "0");
  ESPUI.label("Temperatura:", COLOR_WETASPHALT, "0");
  ESPUI.label("Saturación:", COLOR_WETASPHALT, "0");
  //ESPUI.pad ("Controlador", true, &padExample, COLOR_WETASPHALT);
  ESPUI.begin("FLER: Interfaz Web");
 

  }


void loop(){ 
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

  //Impresión Interfaz Web
  ESPUI.print("Humedad:", String(hums));
  ESPUI.print("Temperatura:", String (temps));
  ESPUI.print("Saturación:", String(gass));


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
}   
