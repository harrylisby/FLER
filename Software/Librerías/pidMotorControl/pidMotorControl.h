#ifndef pidMotorControl_h
#define pidMotorControl_h
#define LIBRARY_VERSION 1.0.0

#include <PID_v1.h>

class pidControl{
public:
	pidControl(double,double,double ,double ,double ,double);
	PID workPID;

private:
	double _encRead;
	double _output;
	double _setPoint;
	float _kp;
	float _ki;
	float _kd;
	int mode=DIRECT;
	
};
#endif
