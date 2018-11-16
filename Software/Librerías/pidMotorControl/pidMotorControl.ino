#include "pidMotorControl.h" 

double encRead_=0;
double output_=0;
double setPoint_=0;
float kp_=1;
float ki_=0;
float kd_=0;

pidControl motor1(encRead_,output_,setPoint_,kp_,kd_,ki_);

void setup(){
	
}

void loop(){

}
