int xVal; //X values from joystick

int yVal; //Y values from joystick

void setup() {

Serial.begin(9600); //Starts serial at 9600 baud

pinMode(A0, INPUT); //Sets the analog ports used to an input

pinMode(A1, INPUT);

}

void loop() {

xVal = analogRead(A0); //sets the X value

yVal = analogRead(A1); //sets the Y value

if(yVal==510 && xVal==512){
  Serial.print("CENTRO");
}

else if(xVal==0){
  Serial.print("DERECHA");
}

else if(xVal == 1023){
  Serial.print("IZQUIERDA");
}

else if(yVal==0){
  Serial.print("ABAJO");
}

else if(yVal==1023){
  Serial.print("ARRIBA");
}

Serial.println();

//Serial.print(" Y is...");
//
//Serial.print(yVal); //prints Y values
//
//Serial.print("   ");
//
//Serial.print(" X is...");
//
//Serial.print(xVal); //prints X values
//
//Serial.println();

}
