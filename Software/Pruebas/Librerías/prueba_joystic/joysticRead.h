class joystickReader{
  
private:
  byte analogPinX;
  byte analogPinY;
  byte buttonIn;
   
public:
  uint16_t x = 0;
  uint16_t y = 0;
  bool b = 0;

  joystickReader(int aPinX, int aPinY, int bIn){  //Constructor de la clase private <> public
    analogPinX=aPinX;
    analogPinY=aPinY;
    buttonIn=bIn;
    
    pinMode(buttonIn,INPUT_PULLUP);
  }

  String readCoords(){  //Lectura de los valores
    x=analogRead(analogPinX);
    y=analogRead(analogPinY);
    b=digitalRead(buttonIn);
    return("x: "+String(x)+" y: "+String(y)+" b: "+String(b));
  } 
};

