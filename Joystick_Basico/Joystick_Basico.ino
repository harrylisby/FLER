class Joystick
{
  private: //atributos

    byte xVal;
    byte yVal;
    byte valBoton;
    
  public: //metodos
    uint16_t x = 0;
    uint16_t y = 0;
    bool b = 0;  
};

//Constructor: inicializa los atributos
   Joystick(int _xVal, int _yVal, int _valBoton){
    xVal = _xVal;
    yVal = yVal;
    valBoton = _valBoton;
}

void Joystick::leerX(){
   xVal = analogRead(A0); 
}

void Joystick::leerY(){
  yVal = analogRead(A1);
}

void Joystick::leerBoton(){
  valBoton = digitalRead(boton);
}

int main(){
   
}







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
