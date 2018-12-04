#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "pidMotorControl.h"


pidControl::pidControl(double* encRead,double* output,double* setPoint,double kp,double kd,double ki)  
  : workPID(&_encRead,&_output,&_setPoint,kp,ki,kd,DIRECT){// , ext_io() {
	_encRead=*encRead;
   _output=*output;
   _setPoint=*setPoint;
   _kp=kp;
   _kd=kd;
   _ki=ki;

   //Serial.begin(115200);
	//Serial.println("Instance Started");
  }

void pidControl::softwareLimits(double minPos=0, double maxPos=4096){
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
	exp_io.pinMode(REV_OUTPUT,OUTPUT);

	minOut = minOutValue;
	maxOut = maxOutValue;

	pidControl::workPID.SetOutputLimits(minOut,maxOut);
	pidControl::workPID.SetMode(AUTOMATIC);
}

void pidControl::goTo(double goToPosition){ 
	_setPoint=goToPosition;
}

bool pidControl::checkWrongDirection(){
	if(oneTime1){
		oneTime1=false;
		_encRead = analogRead(ENCODER);
		_lastPosition = _encRead;
	}else{
		if(_setPoint>_encRead){
		if((_lastPosition-_encRead)>100)return true; 
		}else if(_setPoint<_encRead){
			if((_lastPosition-_encRead)>-100)return true;
		}
	}
  return false;
}

void pidControl::run(bool enableAlarm = false){
	pidControl::workPID.Compute();

	_encRead = analogRead(ENCODER);

	if((_encRead>_maxPos)){ //Mejorar para que retorne al punto máximo
		//bool noErrorWrite=true;
		_setPoint=_maxPos;
	}else if((_encRead<_minPos)){
		//bool noErrorWrite=true;
		_setPoint=_minPos;
	}

	if(_encRead < _setPoint){
		digitalWrite(FWD_OUTPUT,LOW);
		//delay(1);
		exp_io.digitalWrite(REV_OUTPUT,HIGH);
	}else if(_encRead > _setPoint){
		exp_io.digitalWrite(REV_OUTPUT,LOW);
		//delay(1);
		digitalWrite(FWD_OUTPUT,HIGH);
	}else{
		exp_io.digitalWrite(REV_OUTPUT,LOW);
		digitalWrite(FWD_OUTPUT,HIGH);
	}

	//if(abs(_output)<_PID_THRESHOLD || abs(_output)<_PID_THRESHOLD)_output=0;

	pwmWrite(PWM_OUTPUT,abs(_output));
}

double pidControl::getEncoder(){
	return _encRead;
}

double pidControl::getOutput(){
	return _output;
}

double pidControl::getSetpoint(){
	return _setPoint;
}

