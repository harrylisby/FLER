#include "CONFIG.h"
#include <EasyTransfer.h> //librería para transferencia entre arduinos

double encRead1_A2;
//Variables del PID y configuración inicial (agresiva)
PID myPID(&encRead1, &output1, &setPoint1, consKp, consKi, consKd, DIRECT);
PID pid2(&encRead2, &output2, &setPoint2, consKp, consKi, consKd, DIRECT);

EasyTransfer RX_In, TX_Out; //se crean los variables de salida y entrada

struct RECEIVE_DATA_STRUCTURE {
  //variables que se van a recibir del otro arduino
  double encRead1;
  //double encRead2;
  };

struct SEND_DATA_STRUCTURE {
  //variables que se van a enviar 
  //double encRead1;
  double encRead2;  
};

RECEIVE_DATA_STRUCTURE rxdata;
SEND_DATA_STRUCTURE txdata;

void setup()
{
  Serial.begin(115200);
  RX_In.begin(details(rxdata), &Serial);
  TX_Out.begin(details(txdata), &Serial);
  
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
    txdata.encRead1=map(enc1, 0, 4095, 0, 270); //mapeo de la lectura.. txdata.x define que esta variable es la que se envía
    txdata.encRead2=map(enc2, 0, 4095, 0, 270);

    TX_Out.sendData(); //envía la información

    for (int i=0; i<5; i++){
      RX_In.receiveData();
      encRead1_A2 = rxdata.encRead1;
    }
    
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
      Serial.println(String(setPoint1) + ":" +String(output1) + " : " + String(encRead1));
    }
    if(S_PLOTTER_M){
      Serial.print("Pos: "+String(encRead1));
      Serial.println("  Out: "+String(map(output1,0,65535,0,500)));      
    }
    if(S_PLOTTER_M2){
      Serial.print("Pos: "+String(encRead2));
      Serial.println("  Out: "+String(map(output2,0,65535,0,500)));
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
      S_READ_S=Serial.parseInt();
      //Serial.println(S_READ_S);
      if(S_READ_S==0){
        serialWatchdog=0;
        S_PLOTTER_M=0;
        S_PLOTTER_M2=0;
      }else if(S_READ_S==1){
        serialWatchdog=1;
        S_PLOTTER_M=0;
        S_PLOTTER_M2=0;
      }else if(S_READ_S==2){
        S_PLOTTER_M=1;
        serialWatchdog=0;
        S_PLOTTER_M2=0;
      }else if(S_READ_S==3){
        S_PLOTTER_M2=1;
        serialWatchdog=0;
        S_PLOTTER_M=0;
      }
    }

    if(Serial.peek()=='q'){ //Comando q: limpiar alarmas (1)
      Serial.read();
      I_ERROR=Serial.parseInt();  
    }
  }
  while(Serial.available() > 0)Serial.read();
}

