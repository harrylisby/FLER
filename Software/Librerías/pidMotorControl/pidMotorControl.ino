#include "pidMotorControl.h" 

uint16_t encRead_=0;
uint16_t output_=0;
uint16_t setPoint_=0;
float kp_=1;
float ki_=0;
float kd_=0;

pidControl motor1(encRead_,output_,setPoint_,kp_,kd_,ki_);

void setup(){
	
}

void loop(){

}