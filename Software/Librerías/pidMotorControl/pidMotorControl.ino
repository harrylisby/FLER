#include "pidMotorControl.h" 
#include <EasyTransfer.h>

#define FRONT

int16_t SP_IF1, SP_IF2, SP_IF3, SP_DF1, SP_DF2, SP_DF3; //Variables frontales
int16_t SP_IR1, SP_IR2, SP_IR3, SP_DR1, SP_DR2, SP_DR3; //Variables traseras


#ifdef FRONT
//*********************************************************************
EasyTransfer Front;

struct RECEIVED_DATA_STRUCTURE{

  int16_t SSP_IF1, SSP_IF2, SSP_IF3, SSP_DF1, SSP_DF2, SSP_DF3;
  
};

//give a name to the group of data
RECEIVED_DATA_STRUCTURE frontData;
//*********************************************************************
#endif

#ifdef REAR
//*********************************************************************
EasyTransfer Rear; 

struct RECEIVED_DATA_STRUCTURE_2{

  int16_t SSP_IR1, SSP_IR2, SSP_IR3, SSP_DR1, SSP_DR2, SSP_DR3;
  
};

RECEIVED_DATA_STRUCTURE_2 rearData;
//*********************************************************************
#endif

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
pidControl DF1(&DF1_ENCREAD,&DF1_OUT,&DF1_SP,DF1_KP,DF1_KD,DF1_KI);
pidControl DF2(&DF2_ENCREAD,&DF2_OUT,&DF2_SP,DF2_KP,DF2_KD,DF2_KI);
pidControl DF3(&DF3_ENCREAD,&DF3_OUT,&DF3_SP,DF3_KP,DF3_KD,DF3_KI);


void setup(){
	Serial.begin(115200);
  	Serial2.begin(9600);
  
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
#ifdef FRONT  
  	Front.begin(details(frontData), &Serial2); //comunicación frontal
#endif
#ifdef REAR
  	Rear.begin(details(rearData), &Serial2); //comunicación trasera
#endif

	IF1.softwareLimits(250,3750);
	IF1.controllerBegin(IF1_ENC,IF1_PWM,IF1_FWD,IF1_REV,-65535,65535,15000);

	IF2.softwareLimits(250,3750);
	IF2.controllerBegin(IF2_ENC,IF2_PWM,IF2_FWD,IF2_REV,-65535,65535,15000);

	IF3.softwareLimits(250,3750);
	IF3.controllerBegin(IF3_ENC,IF3_PWM,IF3_FWD,IF3_REV,-65535,65535,15000);

	DF1.softwareLimits(250,3750);
	DF1.controllerBegin(DF1_ENC,DF1_PWM,DF1_FWD,DF1_REV,-65535,65535,15000);

	DF2.softwareLimits(250,3750);
	DF2.controllerBegin(DF2_ENC,DF2_PWM,DF2_FWD,DF2_REV,-65535,65535,15000);

	DF3.softwareLimits(250,3750);
	DF3.controllerBegin(DF3_ENC,DF3_PWM,DF3_FWD,DF3_REV,-65535,65535,15000);

}

void loop(){

#ifdef FRONT
	//send the data
	Front.receiveData();
	 
	IF1_SP = frontData.SSP_IF1;
	IF2_SP = frontData.SSP_IF2;
	IF3_SP = frontData.SSP_IF3;
	DF1_SP = frontData.SSP_DF1;
	DF2_SP = frontData.SSP_DF2;
	DF3_SP = frontData.SSP_DF3;
	    
	/*Serial.println("SP_IF1: " + String(SP_IF1)+ " SP_IF2: " + String(SP_IF2)+ " SP_IF3: " + String(SP_IF3) + " SP_DF1: " + String(SP_DF1)+ " SP_DF2: " + String(SP_DF2)+ " SP_DF3: " + String(SP_DF3));*/   
#endif

#ifdef REAR
	Rear.receiveData();

	IR1_SP = rearData.SSP_IR1;
	IR2_SP = rearData.SSP_IR2;
	IR3_SP = rearData.SSP_IR3;
	DR1_SP = rearData.SSP_DR1;
	DR2_SP = rearData.SSP_DR2;
	DR3_SP = rearData.SSP_DR3;

	/*Serial.println("SP_IR1: " + String(SP_IR1)+ " SP_IR2: " + String(SP_IR2)+ " SP_IR3: " + String(SP_IR3) + " SP_DR1: " + String(SP_DR1)+ " SP_DR2: " + String(SP_DR2)+ " SP_DR3: " + String(SP_DR3));*/ 
#endif

	IF1.run();
	IF2.run();
	IF3.run();
	DF1.run();
	DF2.run();
	DF3.run();

	//why are U runnin?

}
