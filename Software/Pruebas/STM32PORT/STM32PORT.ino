#include "CONFIG.h"

//Variables del PID y configuración inicial (agresiva)
PID myPID(&encRead1, &output1, &setPoint1, consKp, consKi, consKd, DIRECT);
PID pid2(&encRead2, &output2, &setPoint2, consKp, consKi, consKd, DIRECT);

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
  myPID.SetOutputLimits(-65535, 65535); //límites de la salida
  myPID.SetMode(AUTOMATIC);

  pid2.SetOutputLimits(-65535, 65535);
  pid2.SetMode(AUTOMATIC);

  setPoint1=135;
  setPoint2=135;  //hardcoding
}

void loop() {
  actualMillis = millis();
  if ((actualMillis - prevMillis) > PROG_FREQ) {
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
    
    myPID.Compute();
    pid2.Compute();

    if (encRead1 < setPoint1) {
      digitalWrite(LM298_IN1, LOW);
      delay(1);
      digitalWrite(LM298_IN2, HIGH);
    }else if(encRead1 > setPoint1){
      digitalWrite(LM298_IN2, LOW);
      delay(1);
      digitalWrite(LM298_IN1, HIGH);     
    }else{
      digitalWrite(LM298_IN1, LOW);
      digitalWrite(LM298_IN2, LOW);
    }

    if (encRead2 < setPoint2) {
      digitalWrite(LM298_IN3, LOW);
      delay(1);
      digitalWrite(LM298_IN4, HIGH);
    }else if(encRead2 > setPoint2) {
      digitalWrite(LM298_IN4, LOW);
      delay(1);
      digitalWrite(LM298_IN3, HIGH);     
    }else{
      digitalWrite(LM298_IN3, LOW);
      digitalWrite(LM298_IN4, LOW);
    }

    if(abs(output1)<PID_UMBRAL)output1=0;
    if(abs(output2)<PID_UMBRAL)output2=0;
    
    pwmWrite(OUT_1, abs(output1));
    pwmWrite(OUT_2, abs(output2));

    //Serial.println(String(scaled) + " : " + String(encRead1)+"  |  "+String(scaled2) + " : " + String(encRead2));
    Serial.println(String(output1) + " : " + String(encRead1)+"  |  "+String(output2) + " : " + String(encRead2));
  }

}
