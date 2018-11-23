#include "pidMotorControl.h" 

uint32_t lastCycle, currentTime;

double encRead_w=0;
double output=0;
double setPoint=0;
double kp=85;
double ki=0;
double kd=5;

pidControl motor1(&encRead_w,&output,&setPoint,kp,kd,ki);


void setup(){
	Serial.begin(115200);

	motor1.softwareLimits(250,3750);
	motor1.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);	

  motor1.goTo(1000);
}

void loop(){

  currentTime=millis();
  if((currentTime-lastCycle)>10){
    motor1.run(false);
    Serial.println(String(motor1.getEncoder())+"  "+String(motor1.getSetpoint())+"  "+String(motor1.getOutput())+"   "+String(motor1.checkWrongDirection()));

    serialDecoder();
    lastCycle=currentTime;
  }	
}


void serialDecoder(){
  if (Serial.available() > 0) {
    if(Serial.peek()=='c'){  //Comando c: Cambiar PID SP1
      Serial.read();
      setPoint=Serial.parseInt();
      motor1.goTo(setPoint);
    }
  }
  while(Serial.available() > 0)Serial.read();
}
