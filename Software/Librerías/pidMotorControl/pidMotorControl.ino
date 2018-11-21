#include "pidMotorControl.h" 

//IF1 IO
static int IF1_ENC = PA0;
static int IF1_PWM = PB9;
static int IF1_FWD = PB8;
static int IF1_REV = PB7;

//IF2 IO
static int IF2_ENC = PA1;
static int IF2_PWM = PB6;
static int IF2_FWD = PB5;
static int IF2_REV = PB4;

//IF3 IO
static int IF3_ENC = PA2;
static int IF3_PWM = PB3;
static int IF3_FWD = PA15;
static int IF3_REV = PA12;

//DF1 IO
static int DF1_ENC = PA3;
static int DF1_PWM = PA12;
static int DF1_FWD = PA11;
static int DF1_REV = PA10;

//DF2 IO
static int DF2_ENC = PA4;
static int DF2_PWM = PA9;
static int DF2_FWD = PA8;
static int DF2_REV = PB15;

//DF3 IO
static int DF3_ENC = PA5;
static int DF3_PWM = PB14;
static int DF3_FWD = PB13;
static int DF3_REV = PB11;


double IF1_ENCREAD, IF2_ENCREAD, IF3_ENCREAD, DF1_ENCREAD, DF2_ENCREAD, DF3_ENCREAD; 
double IF1_OUT, IF2_OUT, IF3_OUT, DF1_OUT, DF2_OUT, DF3_OUT;
double IF1_SP, IF2_SP, IF3_SP, DF1_SP, DF2_SP, DF3_SP;
double IF1_KP=2300, IF2_KP=2300, IF3_KP=2300, DF1_KP=2300, DF2_KP=2300, DF3_KP=2300;
double IF1_KI=0, IF2_KI=0, IF3_KI=0, DF1_KI=0, DF2_KI=0, DF3_KI=0;
double IF1_KD=175, IF2_KD=175, IF3_KD=175, DF1_KD=175, DF2_KD=175, DF3_KD=175;

pidControl IF1(&IF1_ENCREAD,&IF1_OUT,&IF1_SP,IF1_KP,IF1_KD,IF1_KI);
pidControl IF2(&IF2_ENCREAD,&IF2_OUT,&IF2_SP,IF2_KP,IF2_KD,IF2_KI);
pidControl IF3(&IF3_ENCREAD,&IF3_OUT,&IF3_SP,IF3_KP,IF3_KD,IF3_KI);
pidControl DF2(&DF1_ENCREAD,&DF1_OUT,&DF1_SP,DF1_KP,DF1_KD,DF1_KI);
pidControl DF2(&DF2_ENCREAD,&DF2_OUT,&DF2_SP,DF2_KP,DF2_KD,DF2_KI);
pidControl DF2(&DF3_ENCREAD,&DF3_OUT,&DF3_SP,DF3_KP,DF3_KD,DF3_KI);


void setup(){
	Serial.begin(115200);

	IF1.softwareLimits(250,3750);
	IF1.controllerBegin(IF1_ENC,PB8,PB12,PB13,-65535,65535,15000);

	IF2.softwareLimits(250,3750);
	IF2.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);

	IF3.softwareLimits(250,3750);
	IF3.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);

	DF1.softwareLimits(250,3750);
	DF1.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);

	DF2.softwareLimits(250,3750);
	DF2.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);

	DF3.softwareLimits(250,3750);
	DF3.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);

}

void loop(){
	motor1.goTo(15);
	motor1.run();
}
