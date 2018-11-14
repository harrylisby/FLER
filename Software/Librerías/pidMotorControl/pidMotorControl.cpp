#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "pidMotorControl.h"

pidControl::pidControl(double encRead,double output,double setPoint,double kp,double kd,double ki) : workPID(&encRead,&output,&setPoint,kp,ki,kd,DIRECT) {
	Serial.println("Instance Started");
	_encRead=encRead;
	_output=output;
	_setPoint=setPoint;
	_kp=kp;
	_kd=kd;
	_ki=ki;
}

//pidControl::workPID(&_encRead,&_output,&_setPoint,_kp,_ki,_kd,DIRECT);

	