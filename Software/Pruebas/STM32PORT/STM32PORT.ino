//TODO
//Comentar
//Archivo de config
//Valores inciales


#include <PID_v1.h>

#define ENC_1 PA0
#define OUT_1 PB8

#define ENC_2 PA1
#define OUT_2 PB9


float S_P=135;  //Recibe la lectura del puerto serie
int LM298_IN1 = PB12; //Variables control driver
int LM298_IN2 = PB13;
int LM298_IN3 = PB14;
int LM298_IN4 = PB15;
int enc1, enc2;
double setPoint1, encRead1, output1; //Variables para el PID
double setPoint2, encRead2, output2; //Variables para el PID
uint32_t scaled,scaled2;


//Parámetros para control del PID (agresivo y conservador)
double aggKp = 8, aggKi = 0.00, aggKd = 1.5;
double consKp = 4.5, consKi = 0.00, consKd = 0.75; //consKp=1, consKi=0.00, consKd=0.25;

//Variables del PID y configuración inicial (agresiva)
PID myPID(&encRead1, &output1, &setPoint1, consKp, consKi, consKd, DIRECT);
PID pid2(&encRead2, &output2, &setPoint2, consKp, consKi, consKd, DIRECT);

uint32_t actualMillis = 0;
uint32_t prevMillis = 0;


void setup()
{
  Serial.begin(115200);
  pinMode(ENC_1, INPUT_ANALOG);
  pinMode(OUT_1, PWM);
  pinMode(ENC_2, INPUT_ANALOG);
  pinMode(OUT_2, PWM);
  pinMode(LM298_IN1, OUTPUT);
  pinMode(LM298_IN2, OUTPUT);
  pinMode(LM298_IN3, OUTPUT);
  pinMode(LM298_IN4, OUTPUT);

  //Encendido del PID
  myPID.SetOutputLimits(-255, 255); //límites de la salida
  myPID.SetMode(AUTOMATIC);

  pid2.SetOutputLimits(-255,255);
  pid2.SetMode(AUTOMATIC);

  setPoint1=135;
  setPoint2=135;  //hardcoding
}

void loop() {
  actualMillis = millis();
  if ((actualMillis - prevMillis) > 20) {
    prevMillis = actualMillis;


    if (Serial.available() > 0) {
      S_P = Serial.parseFloat(); //lee un numero flotante, en caso de necesitarse seteos finos
    }

    //setPoint1 = S_P; //establecimiento del setPoint
    setPoint2 = S_P;

    enc1=analogRead(ENC_1); //lectura del potenciómetro
    enc2=analogRead(ENC_2);
    encRead1=map(enc1, 0, 4095, 0, 270); //mapeo de la lectura
    encRead2=map(enc2, 0, 4095, 0, 270);


    double gap = abs(setPoint1 - encRead2); //
    if (gap < 10){ //Si está cercano al setPoint se comporta conservador, por lo que va despacio
      myPID.SetTunings(consKp, consKi, consKd);
    }
    else{
      //si está largo del setPoint se comporta agresivo.
      myPID.SetTunings(aggKp, aggKi, aggKd);
    }

    myPID.Compute();
    pid2.Compute();

    scaled = map(abs(output1), 0, 255, 0, 65535);
    pwmWrite(OUT_1, scaled);
    scaled2 = map(abs(output2), 0, 255, 0, 65535);
    pwmWrite(OUT_2, scaled2);

    if (encRead1 < setPoint1) {
      digitalWrite(LM298_IN1, LOW);
      digitalWrite(LM298_IN2, HIGH);
    }
    else {
      digitalWrite(LM298_IN1, HIGH);
      digitalWrite(LM298_IN2, LOW);
    }

    if (encRead2 < setPoint2) {
      digitalWrite(LM298_IN3, LOW);
      digitalWrite(LM298_IN4, HIGH);
    }
    else {
      digitalWrite(LM298_IN3, HIGH);
      digitalWrite(LM298_IN4, LOW);
    }

    Serial.println(String(scaled) + " : " + String(encRead1)+"  |  "+String(scaled2) + " : " + String(encRead2));
  }

}
