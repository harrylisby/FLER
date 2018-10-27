#include <PID_v1.h>

#define PIN_INPUT A5
#define PIN_OUTPUT 6


float S_P;  //Recibe la lectura del puerto serie
int LM298_IN1=2; //Variables control driver
int LM298_IN2=3;
int LM298_IN3=4;
int LM298_IN4=5;
double Setpoint, grados, enable, pot; //Variables para el PID


//Parámetros para control del PID (agresivo y conservador)
double aggKp=4, aggKi=0.0, aggKd=1;
double consKp=1, consKi=0.00, consKd=0.25;

//Variables del PID y configuración inicial (agresiva)
PID myPID(&grados, &enable, &Setpoint, consKp, consKi, consKd, DIRECT);


void setup()
{
Serial.begin(9600);

  //Encendido del PID
  myPID.SetOutputLimits(-255,255); //límites de la salida
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  if(Serial.available()>0){
    S_P=Serial.parseFloat();  //lee un numero flotante, en caso de necesitarse seteos finos
    }
    
  Setpoint = S_P; //establecimiento del setpoint
  
  pot = analogRead(PIN_INPUT); //lectura del potenciómetro
  grados = map(pot, 0, 1023, 0, 270); //mapeo de la lectura
  

  double gap = abs(Setpoint-grados); //
  if (gap < 10)
  {  //Si está cercano al setpoint se comporta conservador, por lo que va despacio
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //si está largo del setpoint se comporta agresivo.
     myPID.SetTunings(aggKp, aggKi, aggKd);
  }

  myPID.Compute();
  
  //
  Serial.print(enable);
  Serial.println(" : "+String(grados));

  analogWrite(PIN_OUTPUT, abs(enable));

  if (grados < Setpoint) {
  digitalWrite(LM298_IN1,LOW);
  digitalWrite(LM298_IN2,HIGH);
  }
  else {
  digitalWrite(LM298_IN1,HIGH);
  digitalWrite(LM298_IN2,LOW);
  }

}



