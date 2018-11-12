#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "pidMotorControl.h"

pidControl::pidControl():workPID(){}

pidControl::pidControl(uint16_t encRead,uint16_t output,uint16_t setPoint,float kp,float kd,float ki) : workPID(&encRead,&output,&setPoint,kp,ki,kd,DIRECT) {
	Serial.println("Instance Started");
	_encRead=encRead;
	_output=output;
	_setPoint=setPoint;
	_kp=kp;
	_kd=kd;
	_ki=ki;
}

//pidControl::workPID(&_encRead,&_output,&_setPoint,_kp,_ki,_kd,DIRECT);

	