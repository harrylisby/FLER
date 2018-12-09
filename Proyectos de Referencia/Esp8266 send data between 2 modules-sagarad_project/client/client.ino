#include <ESP8266WiFi.h>
#include <WiFiClient.h> 

const char* host = "192.168.4.1"; //Ip of the Host(Our Case esp8266-01 as server. Its the ip of the esp8266-01 as Access point)

void setup() {
  Serial.begin(9600);          //Baud Rate for Communication
  delay(10);                     //Baud rate prper initialization
  pinMode(13,INPUT);             //Pin D7 on NodeMcu Lua. Button to switch on and off the solenoid.
  WiFi.mode(WIFI_STA);           //NodeMcu esp12E in station mode
  WiFi.begin("FLER");      //Connect to this SSID. In our case esp-01 SSID.  

  while (WiFi.status() != WL_CONNECTED) {      //Wait for getting IP assigned by Access Point/ DHCP. 
                                               //Our case  esp-01 as Access point will assign IP to nodemcu esp12E.
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());             //Check out the Ip assigned by the esp12E
}

void loop() {

         if(digitalRead(13)==1){                      //Check out if Pin D7/13 is high. If high activate 
                                                      //the led connected to esp-01. On next press deactivate it. 
              Serial.print("connecting to ");
              Serial.println(host);
              // Use WiFiClient class to create TCP connections
              WiFiClient client;
              const int httpPort = 80;
                if (!client.connect("192.168.4.1", httpPort)) {
                  Serial.println("connection failed");
                  return;
                   }    
              //Request to server to activate the led
              client.print(String("GET ") +"/Led"+" HTTP/1.1\r\n" + 
                           "Host: " + host + "\r\n" + 
                           "Connection: close\r\n\r\n");         
              delay(10);
              // Read all the lines of the reply from server and print them to Serial Monitor etc
              while(client.available()){
                String line = client.readStringUntil('\r');
                Serial.print(line);
              }
              //Close the Connection. Automatically
              Serial.println();
              Serial.println("closing connection");             
            }//End if

}//End Loop
