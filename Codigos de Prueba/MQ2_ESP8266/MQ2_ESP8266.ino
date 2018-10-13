

#include <ESP8266WiFi.h>
#include <Base64.h>

//AP definitions
#define AP_SSID "Lisby"
#define AP_PASSWORD "lisby12345"

// EasyIoT server definitions
#define EIOT_USERNAME    "FLER18"
#define EIOT_PASSWORD    "fler1234"
#define EIOT_IP_ADDRESS  "pp3hTPQ6AwsUW9sv5oiSgMkeRN1RYgvptcclFGyI"
#define EIOT_PORT        80
#define EIOT_NODE        "N8S0"

#define INPUT_PIN         D2
#define USER_PWD_LEN      40


char unameenc[USER_PWD_LEN];
bool oldInputState;
#define base64_encode

void setup() {
  Serial.begin(115200);
  pinMode(INPUT_PIN, INPUT);
  
  wifiConnect();
    
  char uname[USER_PWD_LEN];
  String str = String(EIOT_USERNAME)+":"+String(EIOT_PASSWORD);  
  str.toCharArray(uname, USER_PWD_LEN); 
  memset(unameenc,0,sizeof(unameenc));
  base64_encode(unameenc, uname, strlen(uname));
  
  oldInputState = !digitalRead(INPUT_PIN);
}

void loop() {
  int inputState = digitalRead(INPUT_PIN);;  
  
  if (inputState != oldInputState)
  {
    sendInputState(inputState);
    oldInputState = inputState;
  }
}

void wifiConnect()
{
    Serial.print("Connecting to AP");
    WiFi.begin(AP_SSID, AP_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");  
}

void sendInputState(bool inputState)
{  
   WiFiClient client;
   
   while(!client.connect(EIOT_IP_ADDRESS, EIOT_PORT)) {
    Serial.println("connection failed");
    wifiConnect(); 
  }
 
  String url = "";
  String command = "";
  
  if (inputState)
    command = "ControlOn";
  else
    command = "ControlOff";
  
  url = "/Api/EasyIoT/Control/Module/Virtual/"+ String(EIOT_NODE) + "/"+command; // generate EasIoT server node URL

  Serial.print("POST data to URL: ");
  Serial.println(url);
  
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + String(EIOT_IP_ADDRESS) + "\r\n" + 
               "Connection: close\r\n" + 
               "Authorization: Basic " + unameenc + " \r\n" + 
               "Content-Length: 0\r\n" + 
               "\r\n");

  delay(100);
    while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("Connection closed");
}
