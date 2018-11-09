

int INPUT_PIN = A0;




void setup() {
   Serial.begin(9600);
   pinMode(INPUT_PIN, INPUT);
   Serial.setTimeout(2000); 


   
}

int timeSinceLastRead =0;

void loop() {
  int analogsensor = analogRead(INPUT_PIN); {


    Serial.print("Gas: ");
    Serial.println (analogsensor);
    timeSinceLastRead = 0;
    millis();
   }
   
 
}
