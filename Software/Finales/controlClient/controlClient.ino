#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Nextion.h" 
#include <EasyTransfer.h>



//#define WIRE_COMMS //Habilitar i2c
//#define UART_COMMS //Habilitar UART

#ifdef WIRE_COMMS
#include <Wire.h>
#include <EasyTransferI2C.h>
//Sección de comunicación i2c
//create object
EasyTransferI2C ET; 

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
SEND_DATA_STRUCTURE myDataI2C;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 9

#endif //WIRE_COMMS

/////////////////////////////////////////////////////////////////

#ifdef UART_COMMS

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



const char* host = "192.168.4.1"; 

String data;
float temps;
float hums;
float gass;


//delay
int timeTracker =0; 
int timeInterval= 1000;

void setup() {

#ifdef WIRE_COMMS
  Wire.begin();
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Wire);
#endif //WIRE_COMMS

#ifdef UART_COMMS
  //no implementado
#endif UART_COMMS

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

#ifdef WIRE_COMMS
  myDataI2C.valZ = 200;
  myDataI2C.valY = 300;
  myDataI2C.valX = 400;

  ET.sendData(I2C_SLAVE_ADDRESS);
#endif //WIRE_COMMS


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