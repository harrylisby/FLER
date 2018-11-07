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

    serialDecoder();

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
    
    if(!I_ERROR){  //Solo escribe a los pines PWM si no se sobrepasa el límite de corriente
      pwmWrite(OUT_1, abs(output1));
      pwmWrite(OUT_2, abs(output2));
    }
    
    if(serialWatchdog){
      Serial.println(String(output1) + " : " + String(encRead1)+"  |  "+String(output2) + " : " + String(encRead2));
    }
    if(currentProtection){
      I_READ = I_CAL*analogRead(I_SENSE)-1280;
      Serial.println("Current: "+String(I_READ));
      if(I_READ >= MAX_CURRENT){
        I_ERROR = true;
        pwmWrite(OUT_1, 0);
        pwmWrite(OUT_2, 0);
      }
    }
  }
}

void serialDecoder(){
  if (Serial.available() > 0) {
    if(Serial.peek()=='c'){  //Comando c: Cambiar PID SP1
      Serial.read();
      SP1=Serial.parseInt();
      setPoint1=SP1;
    }
    
    if(Serial.peek()=='v'){ //Comando v: Cambiar PID SP2
      Serial.read();
      SP2=Serial.parseInt();
      setPoint2=SP2;
    }

    if(Serial.peek()=='p'){ //Comando p: Cambiar PID P
      Serial.read();
      consKp=Serial.parseFloat();
      Serial.println("Nuevo Kp: " +String(consKp));
    }
    
    if(Serial.peek()=='i'){ //Comando i: Cambiar PID I
      Serial.read();
      consKi=Serial.parseFloat();
      Serial.println("Nuevo Ki: " +String(consKi));
    }

    if(Serial.peek()=='d'){
      Serial.read();
      consKd=Serial.parseFloat(); //Comando d: Cambiar PID D
      Serial.println("Nuevo Kd: " +String(consKd));
    }

    if(Serial.peek()=='s'){ //Comando s: activa/desactiva debug serial (1)
      Serial.read();
      serialWatchdog=Serial.parseInt();
    }

    if(Serial.peek()=='q'){ //Comando q: limpiar alarmas (1)
      Serial.read();
      I_ERROR=Serial.parseInt();  
    }
  }
  while(Serial.available() > 0)Serial.read();
}

