#ifndef pidMotorControl_h
#define pidMotorControl_h
#define LIBRARY_VERSION 1.0.0

#include <PID_v1.h>

class pidControl{
public:
	pidControl(uint16_t,uint16_t,uint16_t ,float ,float ,float);
	PID workPID;

private:
	uint16_t _encRead;
	uint16_t _output;
	uint16_t _setPoint;
	float _kp;
	float _ki;
	float _kd;
	int mode=DIRECT;
	//PID workPID();
	
};
#endif