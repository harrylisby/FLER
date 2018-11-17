#include "Wire.h"
#include "SparkFunBME280.h"
#include <ESP8266WiFi.h>
char ssid[] = "YourSSID";
char pass[] = "YourPass!";
IPAddress server(192, 168, 178, 80);
WiFiClient client;
BME280 mySensor;
float hums;
float temps;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);
  mySensor.setI2CAddress(0x76);
  mySensor.beginI2C();
  WiFi.begin(ssid, pass);      
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop(){ 
  hums = mySensor.readFloatHumidity();
  temps = mySensor.readTempC();
  Serial.print("Humidity: ");
  Serial.print(hums, 2);
  Serial.print(" Temp: ");
  Serial.print(temps, 2);
  Serial.println();
  client.connect(server, 80);   
  client.println(hums,2);
  client.flush();
  delay(500);
  client.println(temps,2);
  client.flush();
  delay(2000);
}
