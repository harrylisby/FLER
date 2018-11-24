#include "pidMotorControl.h"
#include <EasyTransfer.h>

uint32_t lastCycle, currentTime;

#define FRONT

//int16_t SP_IF1, SP_IF2, SP_IF3, SP_DF1, SP_DF2, SP_DF3; //Variables frontales
//int16_t SP_IR1, SP_IR2, SP_IR3, SP_DR1, SP_DR2, SP_DR3; //Variables traseras


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


//Parámetros de PID
double FKP=85;
double FKI=0;
double FKD=5;


//Variables de datos
double IF1_ENCREAD, IF2_ENCREAD, IF3_ENCREAD, DF1_ENCREAD, DF2_ENCREAD, DF3_ENCREAD; 
double IF1_OUT, IF2_OUT, IF3_OUT, DF1_OUT, DF2_OUT, DF3_OUT;
double IF1_SP, IF2_SP, IF3_SP, DF1_SP, DF2_SP, DF3_SP;


pidControl IF1(&IF1_ENCREAD,&IF1_OUT,&IF1_SP,FKP,FKI,FKD);
pidControl IF2(&IF2_ENCREAD,&IF2_OUT,&IF2_SP,FKP,FKI,FKD);
pidControl IF3(&IF3_ENCREAD,&IF3_OUT,&IF3_SP,FKP,FKI,FKD);
pidControl DF1(&DF1_ENCREAD,&DF1_OUT,&DF1_SP,FKP,FKI,FKD);
pidControl DF2(&DF2_ENCREAD,&DF2_OUT,&DF2_SP,FKP,FKI,FKD);
pidControl DF3(&DF3_ENCREAD,&DF3_OUT,&DF3_SP,FKP,FKI,FKD);


void setup(){
	Serial.begin(115200);

	IF1.softwareLimits(250,3750);
	IF1.controllerBegin(PA0,PB8,PB12,PB13,-65535,65535,15000);	

  IF1.goTo(1000);
}

void loop(){

  currentTime=millis();
  if((currentTime-lastCycle)>10){
    IF1.run(false);
    Serial.println(String(IF1.getEncoder())+"  "+String(IF1.getSetpoint())+"  "+String(IF1.getOutput())+"   "+String(IF1.checkWrongDirection()));

    //serialDecoder();
    lastCycle=currentTime;
  }	
}


void serialDecoder(){
  if (Serial.available() > 0) {
    if(Serial.peek()=='c'){  //Comando c: Cambiar PID SP1
      Serial.read();
      IF1_SP=Serial.parseInt();
      IF1.goTo(IF1_SP);
    }
  }
  while(Serial.available() > 0)Serial.read();
}
