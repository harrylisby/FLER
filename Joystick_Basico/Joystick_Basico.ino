class Joystick
{
  private: //atributos

    byte xVal;
    byte yVal;
    byte valBoton;
    
  public: //metodos
    uint16_t x = 0; //entero de 16 bits
    uint16_t y = 0;
    bool b = 0;
};

//Constructor: inicializa los atributos
    Joystick(int a_xVal, int a_yVal, int a_valBoton){
    xVal = a_xVal;
    yVal = a_yVal;
    valBoton = a_valBoton;
    
   pinMode(valBoton, INPUT_PULLUP);
}

  Sring readCoor(){
    x = analogRead(xVal);
    y = analogRead(yVal);
    b = digitalRead(valBoton);
    return("x: "+String(x)+" y: "+String(y)+" b: "+String(b));
  };








//int xVal; //X values from joystick

//int yVal; //Y values from joystick

//int boton = 2;

//int valBoton;


void setup() {

pinMode(A0, INPUT); //Sets the analog ports used to an input

pinMode(A1, INPUT);

pinMode(boton, INPUT_PULLUP);

}

void loop() {

//xVal = analogRead(A0); //sets the X value
//
//yVal = analogRead(A1); //sets the Y value
//
//valBoton = digitalRead(boton);


}
