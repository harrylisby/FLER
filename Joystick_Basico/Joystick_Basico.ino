int xVal; //X values from joystick

int yVal; //Y values from joystick

int boton = 2;

int valBoton;

void setup() {

Serial.begin(9600); //Starts serial at 9600 baud

pinMode(A0, INPUT); //Sets the analog ports used to an input

pinMode(A1, INPUT);

pinMode(boton, INPUT_PULLUP);

}

void loop() {

xVal = analogRead(A0); //sets the X value

yVal = analogRead(A1); //sets the Y value

valBoton = digitalRead(boton);

}
