#include <DHT.h>
#include <DHT_U.h>
#include "Wire.h"
#include <ESP8266WiFi.h>
#include <ESPUI.h>

//Configuración WiFi
const char ssid[] = "FLER";
const char pass[] = "fler12345";

//Almacenamiento de sensores
float hums;
float temps;
float gass;

//Configuración de sensores
#define DHTTYPE DHT22
#define DHTPIN  D4
DHT dht(DHTPIN, DHTTYPE);
int INPUT_PIN = A0;

//Delay
int timeTracker = 0; //Tiempo transcurrido
int timeInterval = 1000; //Milisegundos entre cada ejecución de programa


void padExample(Control sender, int value) {
  switch (value) {
  case P_LEFT_DOWN:
    Serial.print("left down");
    break;
  case P_LEFT_UP:
    Serial.print("left up");
    break;
  case P_RIGHT_DOWN:
    Serial.print("right down");
    break;
  case P_RIGHT_UP:
    Serial.print("right up");
    break;
  case P_FOR_DOWN:
    Serial.print("for down");
    break;
  case P_FOR_UP:
    Serial.print("for up");
    break;
  case P_BACK_DOWN:
    Serial.print("back down");
    break;
  case P_BACK_UP:
    Serial.print("back up");
    break;
  case P_CENTER_DOWN:
    Serial.print("center down");
    break;
  case P_CENTER_UP:
    Serial.print("center up");
    break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}

void setup(){

  //Iniciar serial y sensores
  Serial.begin(115200);
  pinMode(INPUT_PIN, INPUT);
  Serial.setTimeout(2000);
  dht.begin(); 
  Wire.begin();

  //Inicialización de access point
  WiFi.mode(WIFI_AP);
  WiFi.hostname(ssid);
  WiFi.softAP(ssid, pass);
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  //Inicialización de bloques de interfaz
  ESPUI.label("Humedad:", COLOR_WETASPHALT, "0");
  ESPUI.label("Temperatura:", COLOR_WETASPHALT, "0");
  ESPUI.label("Saturación:", COLOR_WETASPHALT, "0");
  ESPUI.pad("Controlador", true, &padExample, COLOR_WETASPHALT);
  //ESPUI.pad("Controlador2", false, &padExample, COLOR_WETASPHALT);
  
  ESPUI.begin("ESPUI Control");
}


void loop(){ 
  int currentTime=millis();  //Ejecuta el código sin uso de delay
  if((currentTime-timeTracker)>timeInterval){
    timeTracker=currentTime;

    //Inicio del programa
    //Lectura de sensores
    hums = dht.readHumidity();
    temps = dht.readTemperature();
    gass = analogRead(INPUT_PIN);

    //Impresión a monitor serial
    Serial.print("Humidity: ");
    Serial.print(hums, 2);
    Serial.print(" Temperature: ");
    Serial.print(temps, 2);
    Serial.print(" Gas: ");
    Serial.print(gass, 2);
    Serial.println();

    //Impresión a interface web
    ESPUI.print("Humedad:", String(hums));
    ESPUI.print("Temperatura:", String(temps));
    ESPUI.print("Saturación:", String(gass));

    
  }
}
