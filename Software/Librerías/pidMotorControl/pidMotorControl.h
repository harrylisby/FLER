#ifndef pidMotorControl_h
#define pidMotorControl_h
#define LIBRARY_VERSION 1.0.0

#include <PID_v1.h>

class pidControl{
public:
	pidControl(double*,double*,double*,double,double,double);
	PID workPID;
	void controllerBegin(int, int, int, int, double, double, double);
	void softwareLimits(int16_t, int16_t);
	void goTo(int16_t);
	bool checkWrongDirection();
	void run();


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
	int16_t m_setPoint;
	int16_t currentPos;
	double minOut, maxOut;
	double _PID_THRESHOLD;
	bool direction; //true = fwd, false = rev
	int16_t _lastPosition;

	int16_t _maxPos;
	int16_t _minPos;
};
#endif
