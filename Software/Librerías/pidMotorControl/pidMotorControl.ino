#include "Adafruit_MCP23008.h"
Adafruit_MCP23008 exp_io;

#include "pidMotorControl.h"
#include <EasyTransfer.h>

uint32_t lastCycle, currentTime;
bool alternar=true;

#define FRONT

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
#define IF1_ENC PA0
#define IF1_PWM PB8
#define IF1_FWD PB12
#define IF1_REV 0 //PB13

//IF2 IO
#define IF2_ENC PA1
#define IF2_PWM PA7
#define IF2_FWD PB5
#define IF2_REV 1 //PB4

//IF3 IO
#define IF3_ENC PA4
#define IF3_PWM PA9
#define IF3_FWD PA8
#define IF3_REV 2 //PB15

//DF1 IO
#define DF1_ENC PB1
#define DF1_PWM PA7
#define DF1_FWD PA6
#define DF1_REV 3 //PC13

//DF2 IO
#define DF2_ENC PB0
#define DF2_PWM PB9
#define DF2_FWD PB13
#define DF2_REV 4 //PB13

//DF3 IO
#define DF3_ENC PA5
#define DF3_PWM PB14
#define DF3_FWD PB13
#define DF3_REV 5 //PB11


//Parámetros de PID
double FKP=85;
double FKI=0;
double FKD=5;


//Variables de datos
double IF1_ENCREAD, IF2_ENCREAD, IF3_ENCREAD, DF1_ENCREAD, DF2_ENCREAD, DF3_ENCREAD; 
double IF1_OUT, IF2_OUT, IF3_OUT, DF1_OUT, DF2_OUT, DF3_OUT;


pidControl IF1(&IF1_ENCREAD,&IF1_OUT,&frontData.SSP_IF1,FKP,FKI,FKD);
pidControl IF2(&IF2_ENCREAD,&IF2_OUT,&frontData.SSP_IF2,FKP,FKI,FKD);
pidControl IF3(&IF3_ENCREAD,&IF3_OUT,&frontData.SSP_IF3,FKP,FKI,FKD);
pidControl DF1(&DF1_ENCREAD,&DF1_OUT,&frontData.SSP_DF1,FKP,FKI,FKD);
pidControl DF2(&DF2_ENCREAD,&DF2_OUT,&frontData.SSP_DF2,FKP,FKI,FKD);
pidControl DF3(&DF3_ENCREAD,&DF3_OUT,&frontData.SSP_DF3,FKP,FKI,FKD);


void setup(){
	Serial.begin(115200);
  Serial2.begin(9600);

#ifdef FRONT  
    Front.begin(details(frontData), &Serial2); //comunicación frontal
#endif
#ifdef REAR
    Rear.begin(details(rearData), &Serial2); //comunicación trasera
#endif

  //EJEMPLO:
	//IF1.softwareLimits(250,3750);
	//IF1.controllerBegin(ENCODER,PWM,FWD,REV,-65535,65535,15000);

  IF1.softwareLimits(250,3750);
  IF1.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);

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

  //IF1.goTo(1000);
}

void loop(){

  uint32_t cycleBegin = micros();

  currentTime=millis();
  if((currentTime-lastCycle)>10){

    IF1.run(false);
    //IF2.run(false);
    //IF3.run(false);
    //DF1.run(false);
    //DF2.run(false);
    //DF3.run(false);
    //Serial.println(String(IF1.getEncoder())+"  "+String(IF1.getSetpoint())+"  "+String(IF1.getOutput())+"   "+String(IF1.checkWrongDirection()));

    //serialDecoder();

    uint32_t cycleEnd = micros();
    Serial.println((cycleEnd-cycleBegin));
    lastCycle=currentTime;
  }	
}


/*
void serialDecoder(){
  if (Serial.available() > 0) {
    if(Serial.peek()=='c'){  //Comando c: Cambiar PID SP1
      Serial.read();
      IF1_SP=Serial.parseInt();
      IF1.goTo(IF1_SP);
    }
  }
  while(Serial.available() > 0)Serial.read();
}*/
