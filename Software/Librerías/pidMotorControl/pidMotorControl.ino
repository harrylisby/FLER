#include "pidMotorControl.h" 

double encRead_w=0;
double output=0;
double setPoint=0;
double kp=230;
double ki=0;
double kd=17.5;

pidControl motor1(&encRead_w,&output,&setPoint,kp,kd,ki);


void setup(){
	Serial.begin(115200);

	motor1.softwareLimits(250,3750);
	motor1.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);	

  motor1.goTo(500);
}

void loop(){
	
	motor1.run();
  Serial.println(String(motor1.getEncoder())+"  "+String(motor1.getSetpoint())+"  "+String(motor1.getOutput()));


}
