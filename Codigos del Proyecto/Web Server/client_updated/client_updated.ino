#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Nextion.h" 

const char* host = "192.168.4.1"; 

String data;
float temps;
float hums;
float gass;


//delay
int timeTracker =0; 
int timeInterval= 1000;

void setup() {
  Serial.begin(9600);        
  delay(10);                            
  WiFi.mode(WIFI_STA);          
  WiFi.begin("FLER");     
  while (WiFi.status() != WL_CONNECTED) {    
  delay(500);
    Serial.print(".");
  }
//Impresión de la IP 
    Serial.println(WiFi.localIP());            
}

void loop() {
//Inicialización de la comunicación por TCP
        WiFiClient client;
        const int httpPort = 80;
        !client.connect("192.168.4.1", httpPort);
 
 //Inicia la petición del sting /DataSensores al server
        client.print(String("GET ") +"/DataSensores"+" HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");         
       delay(10);
//Lectura de todas las lineas de datos y las imprime en el serial
        while(client.available()){
        String line = client.readStringUntil('\r');
        hums = line.substring(14,19).toFloat();
        Serial.println(hums);
        temps = line.substring(33,38).toFloat();
        Serial.println(temps);
        gass = line.substring(52,57).toFloat();
        Serial.println(gass); 
        //Serial.print(line);
       }
       
//Cierra la conexión entre los dos ESP8266
       //Serial.println();


  int currentTime=millis();
  if((currentTime-timeTracker)>timeInterval){
    timeTracker=currentTime;
  data = "gass.txt=\"" + String(gass, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  data = "gass.txt=\"" + String(gass, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  data = "hums.txt=\"" + String(hums, 1) + "\"";
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
