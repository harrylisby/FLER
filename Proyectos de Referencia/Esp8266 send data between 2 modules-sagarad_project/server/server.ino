#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "ESP_D54736";  // SSID of esp8266
//const char* password = "123";   //
bool toggle=0;                  //Variable to switch on and off the solenoid
ESP8266WebServer server(80);    //Specify port for TCP connection

void handleRoot() {
  toggle=!toggle;               //Toggling Led Variable
    digitalWrite(2,toggle);     //Toggle Led
        String s = "\r\n\r\n<!DOCTYPE HTML>\r\n<html><h1>Esp8266 Communication</h1> ";
        s += "<p>Success!!!</html>\r\n\r\n";
        server.send(200,"text/html",s);      //Reply to the client
}


void setup() {
  delay(200);                           //Stable Wifi
  Serial.begin(115200);                 //Set Baud Rate
  pinMode(2, OUTPUT);                   //Led/Solenoid at pin 2
  WiFi.softAP(ssid);//, password);      //In Access Point Mode

  IPAddress myIP = WiFi.softAPIP();     //Check the IP assigned. Put this Ip in the client host.
  Serial.print("AP IP address: ");
  Serial.println(myIP);                 //Print the esp8266-01 IP(Client must also be on the save IP series)
  server.on("/Led", handleRoot);           //Checking client connection
  server.begin();                       // Start the server
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected. On first connection switch on the Solenoid on next switch off.
  server.handleClient();
}

