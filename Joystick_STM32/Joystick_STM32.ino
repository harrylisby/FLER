//Joystick derecho
const int ejeY = PB0;
const int ejeX = PB1;
//Joystick derecho con boton
const int boton = PB10;
//Joystick izquierdo
const int ejeI = PA6;
const int ejeR = PA7;

uint32_t prevMillis;
uint32_t actMillis;

void setup() {
  pinMode(ejeY, INPUT_ANALOG);
  pinMode(ejeX, INPUT_ANALOG);
  pinMode(boton, INPUT_PULLUP);
  pinMode(ejeI, INPUT_ANALOG);
  pinMode(ejeR, INPUT_ANALOG);
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
    int value_ejeZ = analogRead(ejeY);
    int value_ejeG = analogRead(ejeX);
    int value_boton = digitalRead(boton);
    int value_ejeI = analogRead(ejeI);
    int value_ejeR = analogRead(ejeR);
    // print the result:

    if(value_boton == 1){
      Serial.print("X: ");
      Serial.print(value_ejeX);
      Serial.print(" ");
      Serial.print("Y: ");
      Serial.print(value_ejeY);
    }
    else{
      Serial.print("Z: ");
      Serial.print(value_ejeZ);
      Serial.print(" ");
      Serial.print("G: ");
      Serial.print(value_ejeG);
    }

    Serial.print(" ");
    Serial.print("I: ");
    Serial.print(value_ejeI);
    Serial.print(" ");
    Serial.print("R: ");
    Serial.print(value_ejeR);
    Serial.println();
  }
}
