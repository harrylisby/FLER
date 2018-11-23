#ifndef pidMotorControl_h
#define pidMotorControl_h
#define LIBRARY_VERSION 1.0.0

#include <PID_v1.h>

class pidControl{
public:
	pidControl(double*,double*,double*,double,double,double);
	PID workPID;
	void controllerBegin(int, int, int, int, double, double, double);
	void softwareLimits(double, double);
	void goTo(double);
	void run(bool);
	double getEncoder();
	double getSetpoint();
	double getOutput();
	bool checkWrongDirection();


private:
	double _encRead;
	double _output;
	double _setPoint;
	float _kp;
	float _ki;
	float _kd;
	int mode=DIRECT;

	int ENCODER;
	int PWM_OUTPUT;
	int FWD_OUTPUT;
	int REV_OUTPUT;
	double m_setPoint;
	double currentPos;
	double minOut, maxOut;
	double _PID_THRESHOLD;
	double _encoderRead;
	bool direction; //true = fwd, false = rev
	double _lastPosition;
	bool oneTime1=true;

	double _maxPos;
	double _minPos;
};
#endif
