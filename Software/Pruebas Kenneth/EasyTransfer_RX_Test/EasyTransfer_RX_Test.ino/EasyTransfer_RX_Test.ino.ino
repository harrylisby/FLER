#include <EasyTransfer.h>

#define FRONT

int16_t SP_IF1, SP_IF2, SP_IF3, SP_DF1, SP_DF2, SP_DF3; //Variables frontales
int16_t SP_IR1, SP_IR2, SP_IR3, SP_DR1, SP_DR2, SP_DR3; //Variables traseras

//create object
EasyTransfer Front;
EasyTransfer Rear; 

#ifdef FRONT
//*********************************************************************
struct RECEIVED_DATA_STRUCTURE{

  int16_t SSP_IF1, SSP_IF2, SSP_IF3, SSP_DF1, SSP_DF2, SSP_DF3;
  
};

//give a name to the group of data
RECEIVED_DATA_STRUCTURE frontData;
//*********************************************************************
#endif

#ifdef REAR
//*********************************************************************
struct RECEIVED_DATA_STRUCTURE_2{

  int16_t SSP_IR1, SSP_IR2, SSP_IR3, SSP_DR1, SSP_DR2, SSP_DR3;
  
};

RECEIVED_DATA_STRUCTURE_2 rearData;
//*********************************************************************
#endif

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial3.begin(9600);
  
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
#ifdef FRONT  
  Front.begin(details(frontData), &Serial2); //comunicación frontal
#endif
#ifdef REAR
  Rear.begin(details(rearData), &Serial2); //comunicación trasera
#endif
}

void loop(){

#ifdef FRONT
  //send the data
  Front.receiveData();
     
  SP_IF1 = frontData.SSP_IF1;
  SP_IF2 = frontData.SSP_IF2;
  SP_IF3 = frontData.SSP_IF3;
  SP_DF1 = frontData.SSP_DF1;
  SP_DF2 = frontData.SSP_DF2;
  SP_DF3 = frontData.SSP_DF3;
        
  /*Serial.println("SP_IF1: " + String(SP_IF1)+ " SP_IF2: " + String(SP_IF2)+ " SP_IF3: " + String(SP_IF3) + " SP_DF1: " + String(SP_DF1)+ " SP_DF2: " + String(SP_DF2)+ " SP_DF3: " + String(SP_DF3));*/   
#endif

#ifdef REAR

  Rear.receiveData();

  SP_IR1 = rearData.SSP_IR1;
  SP_IR2 = rearData.SSP_IR2;
  SP_IR3 = rearData.SSP_IR3;
  SP_DR1 = rearData.SSP_DR1;
  SP_DR2 = rearData.SSP_DR2;
  SP_DR3 = rearData.SSP_DR3;

  /*Serial.println("SP_IR1: " + String(SP_IR1)+ " SP_IR2: " + String(SP_IR2)+ " SP_IR3: " + String(SP_IR3) + " SP_DR1: " + String(SP_DR1)+ " SP_DR2: " + String(SP_DR2)+ " SP_DR3: " + String(SP_DR3));*/ 
#endif
}
 

