#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
float tempitod;
float humitod;
String data;
String result;
char ssid[] = "YourSSID";
char pass[] = "YourPass";
String APIKEY = "YourAPI";
String CityID = "YourCityID";

WiFiClient client;
char servername[] = "api.openweathermap.org";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
    getWeatherData();
    NextionData();
    delay(10000);
  }

void getWeatherData()
{
  if (client.connect(servername, 80)) { 
    client.println("GET /data/2.5/weather?id=" + CityID + "&units=metric&APPID=" + APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
  while (client.connected() && !client.available()) delay(1); 
  while (client.connected() || client.available()) { 
    char c = client.read();
    result = result + c;
  }
  client.stop();
  result.replace('[', ' ');
  result.replace(']', ' ');
  char jsonArray [result.length() + 1];
  result.toCharArray(jsonArray, sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';
  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);
  String location = root["name"];
  String country = root["sys"]["country"];
  float temperature = root["main"]["temp"];
  float humidity = root["main"]["humidity"];
  String weather = root["weather"]["main"];
  String description = root["weather"]["description"];
  float pressure = root["main"]["pressure"];
  tempitod = temperature;
  humitod = humidity;
}

void NextionData() {
  data = "tempitod.txt=\"" + String(tempitod, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(500);
  data = "humitod.txt=\"" + String(humitod, 1) + "\"";
  Serial.print(data);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}
