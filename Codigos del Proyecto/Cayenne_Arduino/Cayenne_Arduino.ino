
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>



//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
 
// WiFi network info.
char ssid[] = "Alonso";
char wifiPassword[] = "karla%21";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "97c3b570-d212-11e8-8e60-53d8c8eabc71";
char password[] = "4b97bdc8512509bd70ddc66f2c88b7d3d8c8e9f9";
char clientID[] = "e6244390-d354-11e8-a254-e163efaadfe8";
#define SENSOR_PIN
//#define VIRTUAL_CHANNEL 1

void setup() {
pinMode(SENSOR_PIN, INPUT);

Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {

SENSOR_PIN = digitalRead(D5);  //tried 14 with same results...         
 Serial.print("sensor = " );                       
 Serial.println(SENSOR_PIN);     
  delay(10);
  Cayenne.loop();
}

CAYENNE_OUT_DEFAULT()
{
 // Here the data we want to send
//  Cayenne.virtualWrite(VIRTUAL_CHANNEL, digitalRead(SENSOR_PIN));
  
}
