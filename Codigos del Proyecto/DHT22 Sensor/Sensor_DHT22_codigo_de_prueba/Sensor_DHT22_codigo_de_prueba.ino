#include "DHT.h"
#define DHTPIN D4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
   Serial.begin(9600);
   Serial.setTimeout(2000); 

   while(!Serial){}

   Serial.println("Device Started");
   Serial.println ("---------------------");
   Serial.println("Running DHT!");
   Serial.println ("---------------------");  
  
}

int timeSinceLastRead =0;

void loop() {
   if(timeSinceLastRead > 2000){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) ||isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    timeSinceLastRead = 0;
    return;
    }
    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F ");
    Serial.print("Heat index: ");
    Serial.print(hic);
    Serial.print(" *C ");
    Serial.print(hif);
    Serial.print(" *F ");
    Serial.print("\n");

    timeSinceLastRead = 0;
    
   }
   
 delay(100);
 timeSinceLastRead += 100;  
}
