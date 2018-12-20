
#include "pidMotorControl.h"
#include <EasyTransfer.h>

uint32_t lastCycle, currentTime, lastCycle2;
bool alternar=true;

#define REAR

#ifdef FRONT
//*********************************************************************
EasyTransfer Front;

struct RECEIVED_DATA_STRUCTURE{

  double SSP_IF1, SSP_IF2, SSP_IF3, SSP_DF1, SSP_DF2, SSP_DF3;
  
};

//give a name to the group of data
RECEIVED_DATA_STRUCTURE frontData;
//*********************************************************************
#endif

#ifdef REAR
//*********************************************************************
EasyTransfer Rear; 

struct RECEIVED_DATA_STRUCTURE_2{

  double SSP_IR1, SSP_IR2, SSP_IR3, SSP_DR1, SSP_DR2, SSP_DR3;
  
};

RECEIVED_DATA_STRUCTURE_2 rearData;
//*********************************************************************
#endif 

//GPIO
//IF1 IO
#define IF1_ENC PA2
#define IF1_PWM PB6
#define IF1_FWD PB12
#define IF1_REV PB13//0 //PB13

//IF2 IO
#define IF2_ENC PA3
#define IF2_PWM PB7
#define IF2_FWD PB14
#define IF2_REV PB15//1 //PB4

//IF3 IO
#define IF3_ENC PA4
#define IF3_PWM PB8
#define IF3_FWD PA8
#define IF3_REV PA9//2 //PB15

//DF1 IO
#define DF1_ENC PA5
#define DF1_PWM PB9
#define DF1_FWD PB5//PA11
#define DF1_REV PA11//3 //PC13

//DF2 IO
#define DF2_ENC PA6
#define DF2_PWM PA0
#define DF2_FWD PA12
#define DF2_REV PA15//4 //PB13

//DF3 IO
#define DF3_ENC PA7
#define DF3_PWM PA1
#define DF3_FWD PB3
#define DF3_REV PB4


//Parámetros de PID
double FKP=85;
double FKI=0;
double FKD=5;


//Variables de datos
double IF1_ENCREAD, IF2_ENCREAD, IF3_ENCREAD, DF1_ENCREAD, DF2_ENCREAD, DF3_ENCREAD; 
double IF1_OUT, IF2_OUT, IF3_OUT, DF1_OUT, DF2_OUT, DF3_OUT;

#ifdef FRONT

pidControl IF1(&IF1_ENCREAD,&IF1_OUT,&frontData.SSP_IF1,FKP,FKI,FKD);
pidControl IF2(&IF2_ENCREAD,&IF2_OUT,&frontData.SSP_IF2,FKP,FKI,FKD);
pidControl IF3(&IF3_ENCREAD,&IF3_OUT,&frontData.SSP_IF3,FKP,FKI,FKD);
pidControl DF1(&DF1_ENCREAD,&DF1_OUT,&frontData.SSP_DF1,FKP,FKI,FKD);
pidControl DF2(&DF2_ENCREAD,&DF2_OUT,&frontData.SSP_DF2,FKP,FKI,FKD);
pidControl DF3(&DF3_ENCREAD,&DF3_OUT,&frontData.SSP_DF3,FKP,FKI,FKD);
#endif

#ifdef REAR
pidControl IR1(&IF1_ENCREAD,&IF1_OUT,&rearData.SSP_IR1,FKP,FKI,FKD);
pidControl IR2(&IF2_ENCREAD,&IF2_OUT,&rearData.SSP_IR2,FKP,FKI,FKD);
pidControl IR3(&IF3_ENCREAD,&IF3_OUT,&rearData.SSP_IR3,FKP,FKI,FKD);
pidControl DR1(&DF1_ENCREAD,&DF1_OUT,&rearData.SSP_DR1,FKP,FKI,FKD);
pidControl DR2(&DF2_ENCREAD,&DF2_OUT,&rearData.SSP_DR2,FKP,FKI,FKD);
pidControl DR3(&DF3_ENCREAD,&DF3_OUT,&rearData.SSP_DR3,FKP,FKI,FKD);
#endif

void setup(){
	Serial.begin(115200);
	Serial1.begin(9600);

#ifdef FRONT  
    Front.begin(details(frontData), &Serial1); //comunicación frontal
#endif
#ifdef REAR
    Rear.begin(details(rearData), &Serial1); //comunicación trasera
#endif

  //EJEMPLO:
	//IF1.softwareLimits(250,3750);
	//IF1.controllerBegin(ENCODER,PWM,FWD,REV,-65535,65535,15000);
#ifdef FRONT
  IF1.softwareLimits(250,3750);
  IF1.controllerBegin(IF1_ENC,IF1_PWM,IF1_FWD,IF2_REV,-65535,65535,15000);

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
#endif

#ifdef REAR
  IR1.softwareLimits(250,3750);
  IR1.controllerBegin(IF1_ENC,IF1_PWM,IF1_FWD,IF2_REV,-65535,65535,15000);

  IR2.softwareLimits(250,3750);
  IR2.controllerBegin(IF2_ENC,IF2_PWM,IF2_FWD,IF2_REV,-65535,65535,15000);

  IR3.softwareLimits(250,3750);
  IR3.controllerBegin(IF3_ENC,IF3_PWM,IF3_FWD,IF3_REV,-65535,65535,15000);

  DR1.softwareLimits(250,3750);
  DR1.controllerBegin(DF1_ENC,DF1_PWM,DF1_FWD,DF1_REV,-65535,65535,15000);

  DR2.softwareLimits(250,3750);
  DR2.controllerBegin(DF2_ENC,DF2_PWM,DF2_FWD,DF2_REV,-65535,65535,15000);

  DR3.softwareLimits(250,3750);
  DR3.controllerBegin(DF3_ENC,DF3_PWM,DF3_FWD,DF3_REV,-65535,65535,15000);	
#endif
  //IF1.goTo(1000);
}

void loop(){

  uint32_t cycleBegin = micros();

#ifdef FRONT
  Front.receiveData();
#endif

#ifdef REAR
  Rear.receiveData();
#endif

  currentTime=millis();

#ifdef FRONT
  if((currentTime-lastCycle2)>250){
  	Serial.println(IF2.getEncoder());
  }
#endif

#ifdef REAR
  if((currentTime-lastCycle2)>250){
  	Serial.println(IR2.getEncoder());
  }
#endif


  if((currentTime-lastCycle)>10){
#ifdef FRONT
    IF1.run(false);
    IF2.run(false);
    IF3.run(false);
    DF1.run(false);
    DF2.run(false);
    DF3.run(false);
    //Serial.println(String(IF1.getEncoder())+"  "+String(IF1.getSetpoint())+"  "+String(IF1.getOutput())+"   "+String(IF1.checkWrongDirection()));
#endif

#ifdef REAR
    IR1.run(false);
    IR2.run(false);
    IR3.run(false);
    DR1.run(false);
    DR2.run(false);
    DR3.run(false);
#endif

    serialDecoder();
    serialDataPrint();

    uint32_t cycleEnd = micros();
    //Serial.println((cycleEnd-cycleBegin));
    lastCycle=currentTime;
  }	
}

double filter(double lengthOrig, double currentValue) {
  double filter = 30;//mydata_back.filter;
  double lengthFiltered =  (lengthOrig + (currentValue * filter)) / (filter + 1);
  return lengthFiltered;  
}


uint32_t currentTimeSerial;
uint32_t previousTimeSerial;
void serialDataPrint(){
	currentTimeSerial=currentTime;
	if((currentTimeSerial-previousTimeSerial)>1000){
#ifdef FRONT
		Serial.print("SSP_IF1: ");
		Serial.println(frontData.SSP_IF1);
		Serial.print("SSP_IF2: ");
		Serial.println(frontData.SSP_IF2);
		Serial.print("SSP_IF3: ");
		Serial.println(frontData.SSP_IF3);
		Serial.print("SSP_DF1: ");
		Serial.println(frontData.SSP_DF1);
		Serial.print("SSP_DF2: ");
		Serial.println(frontData.SSP_DF2);
		Serial.print("SSP_DF3: ");
		Serial.println(frontData.SSP_DF3);
#endif //FRONT

#ifdef REAR
		Serial.print("SSP_IR1: ");
		Serial.println(rearData.SSP_IR1);
		Serial.print("SSP_IR2: ");
		Serial.println(rearData.SSP_IR2);
		Serial.print("SSP_IR3: ");
		Serial.println(rearData.SSP_IR3);
		Serial.print("SSP_DR1: ");
		Serial.println(rearData.SSP_DR1);
		Serial.print("SSP_DR2: ");
		Serial.println(rearData.SSP_DR2);
		Serial.print("SSP_DR3: ");
		Serial.println(rearData.SSP_DR3);
#endif //REAR

		Serial.println(" ");

		previousTimeSerial=currentTimeSerial;
	}
}

#ifdef FRONT
void serialDecoder(){
  if (Serial.available() > 0) {
    frontData.SSP_IF1=decodePrintData('z',frontData.SSP_IF1);
    frontData.SSP_IF2=decodePrintData('x',frontData.SSP_IF2);
    frontData.SSP_IF3=decodePrintData('c',frontData.SSP_IF3);
    frontData.SSP_DF1=decodePrintData('v',frontData.SSP_IF1);
    frontData.SSP_DF2=decodePrintData('b',frontData.SSP_IF2);
    frontData.SSP_DF3=decodePrintData('n',frontData.SSP_IF3);
  }
  while(Serial.available() > 0)Serial.read();
}
#endif

#ifdef REAR
void serialDecoder(){
  if (Serial.available() > 0) {
    rearData.SSP_IR1=decodePrintData('z',rearData.SSP_IR1);
    rearData.SSP_IR2=decodePrintData('x',rearData.SSP_IR2);
    rearData.SSP_IR3=decodePrintData('c',rearData.SSP_IR3);
    rearData.SSP_DR1=decodePrintData('v',rearData.SSP_IR1);
    rearData.SSP_DR2=decodePrintData('b',rearData.SSP_IR2);
    rearData.SSP_DR3=decodePrintData('n',rearData.SSP_IR3);
  }
  while(Serial.available() > 0)Serial.read();
}
#endif


uint16_t decodePrintData(char expectedChar,uint16_t currentData){
  uint16_t readV=currentData;
  if(Serial.peek()==expectedChar){
    Serial.read();
    readV=Serial.parseInt();
    Serial.println("Nuevo valor: "+String(readV));
  }
  return readV;
}