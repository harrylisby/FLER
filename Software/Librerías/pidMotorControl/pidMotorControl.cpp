#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "pidMotorControl.h"


pidControl::pidControl(double* encRead,double* output,double* setPoint,double kp,double kd,double ki)  
  : workPID(&_encRead,&_output,&_setPoint,kp,ki,kd,DIRECT) {
	_encRead=*encRead;
   _output=*output;
   _setPoint=*setPoint;
   _kp=kp;
   _kd=kd;
   _ki=ki;

   //Serial.begin(115200);
	//Serial.println("Instance Started");
  }

void pidControl::softwareLimits(uint16_t minPos=0, uint16_t maxPos=4096){
	_minPos = minPos;
	_maxPos = maxPos;
}

void pidControl::controllerBegin(int encoderInput, int pwmOutput, int fwdOutput, int revOutput, double minOutValue, double maxOutValue, double PID_THRESHOLD=15000){
	ENCODER = encoderInput;
	PWM_OUTPUT = pwmOutput;
	FWD_OUTPUT = fwdOutput;
	REV_OUTPUT = revOutput;
	_PID_THRESHOLD = PID_THRESHOLD; 

	pinMode(ENCODER, INPUT_ANALOG);
	pinMode(PWM_OUTPUT, PWM);
	pinMode(FWD_OUTPUT,OUTPUT);
	pinMode(REV_OUTPUT,OUTPUT);

	minOut = minOutValue;
	maxOut = maxOutValue;

	pidControl::workPID.SetOutputLimits(minOut,maxOut);
	pidControl::workPID.SetMode(AUTOMATIC);
}

void pidControl::goTo(uint16_t goToPosition){ 
	_setPoint=goToPosition;
}

void pidControl::run(){
	pidControl::workPID.Compute();

	uint16_t encoderRead = analogRead(ENCODER);
	bool noErrorWrite = false;

	if((encoderRead>_maxPos)){ //Mejorar para que retorne al punto máximo
		//bool noErrorWrite=true;
		_setPoint=_maxPos;
	}else if((encoderRead<_minPos)){
		//bool noErrorWrite=true;
		_setPoint=_minPos;
	}

	if(encoderRead < _setPoint){
		digitalWrite(FWD_OUTPUT,LOW);
		delay(1);
		digitalWrite(REV_OUTPUT,HIGH);
	}else if(encoderRead > _setPoint){
		digitalWrite(REV_OUTPUT,LOW);
		delay(1);
		digitalWrite(FWD_OUTPUT,HIGH);
	}else{
		digitalWrite(REV_OUTPUT,LOW);
		digitalWrite(FWD_OUTPUT,HIGH);
	}

	if(abs(_output)<_PID_THRESHOLD || abs(_output)<_PID_THRESHOLD)_output=0;

	pwmWrite(PWM_OUTPUT,_output);
}


