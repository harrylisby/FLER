#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "pidMotorControl.h"


pidControl::pidControl(double encRead,double output,double setPoint,double kp,double kd,double ki)  
  : workPID(&encRead,&output,&setPoint,kp,ki,kd,DIRECT),
    _encRead(encRead),
    _output(output),
    _setPoint(setPoint),
    _kp(kp),
    _kd(kd),
    _ki(ki)
    {
	Serial.println("Instance Started");
  }

void pidControl::controllerBegin(int encoderInput, int pwmOutput, int fwdOutput, int revOutput){
	ENCODER = encoderInput;
	PWM_OUTPUT = pwmOutput;
	FWD_OUTPUT = fwdOutput;
	REV_OUTPUT = revOutput;

	pinMode(ENCODER, INPUT_ANALOG);
	pinMode(PWM_OUTPUT, PWM);
	pinMode(FWD_OUTPUT,OUTPUT);
	pinMode(REV_OUTPUT,OUTPUT);

}

void pidControl::goTo(uint16_t goToPosition){

}

void pidControl::run(){

}
