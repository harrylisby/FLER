#include <ESP8266WiFi.h>
float temps;
float hums;
float gass;
String request;
String data;
char ssid[] = "Lisby";
char pass[] = "lisby12345";
WiFiServer server(80);
IPAddress ip(10, 0, 1, 14);
IPAddress gateway(10, 0, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(9600);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      request = client.readStringUntil('\r');
      hums = request.toFloat();
      client.flush();
      request = client.readStringUntil('\r'); 
      temps = request.toFloat();
      client.flush();
      request = client.readStringUntil('\r');
      gass = request.toFloat();
    }
    client.stop();
    NextionData();
  }
}

void NextionData() {
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
  
}
