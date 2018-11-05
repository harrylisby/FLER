// Analog input pins.
const int ejeY = PB0;
const int ejeX = PB1;
const int boton = PB10;

uint32_t prevMillis;
uint32_t actMillis;

void setup() {
  // Declare analogInputPin as INPUT_ANALOG:
  pinMode(ejeY, INPUT_ANALOG);
  pinMode(ejeX, INPUT_ANALOG);
  pinMode(boton, INPUT_PULLUP);
  	Serial.begin(115200); // Ignored by Maple. But needed by boards using Hardware serial via a USB to Serial Adaptor
}

void loop() {
  actMillis = millis();
  if((actMillis-prevMillis)>20){
    prevMillis=actMillis;
    //su codigo aqui
    // Read the analog input into a variable:
    int value_ejeY = analogRead(ejeY);
    int value_ejeX = analogRead(ejeX);
    int value_boton = digitalRead(boton);
  
    // print the result:
    Serial.print("Boton: ");
    Serial.print(value_boton);
    Serial.print(" ");
    Serial.print("X: ");
    Serial.print(value_ejeX);
    Serial.print(" ");
    Serial.print("Y: ");
    Serial.print(value_ejeY);
    Serial.print(" "); 
  }
}
