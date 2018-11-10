#include <EasyTransfer.h>

#define IF1 1
#define IF2 1
#define IF3 1
#define DF1 7
#define DF2 8
#define DF3 9

#define IR1 4
#define IR2 5
#define IR3 6
#define DR1 10
#define DR2 11
#define DR3 12

int16_t SP_IF1, SP_IF2, SP_IF3, SP_DF1, SP_DF2, SP_DF3, SP_IR1, SP_IR2, SP_IR3, SP_DR1, SP_DR2, SP_DR3;

//create object
EasyTransfer Front;
EasyTransfer Rear; 

//*********************************************************************
struct SEND_DATA_STRUCTURE{

  int16_t SSP_IF1, SSP_IF2, SSP_IF3, SSP_DF1, SSP_DF2, SSP_DF3;
  
};

//give a name to the group of data
SEND_DATA_STRUCTURE frontData;
//*********************************************************************


//*********************************************************************
struct SEND_DATA_STRUCTURE_2{

  int16_t SSP_IR1, SSP_IR2, SSP_IR3, SSP_DR1, SSP_DR2, SSP_DR3;
  
};

SEND_DATA_STRUCTURE_2 rearData;
//*********************************************************************
void setup(){
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial3.begin(9600);
  
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  Front.begin(details(frontData), &Serial2);
  Rear.begin(details(rearData), &Serial3);
  
}

void loop(){
  //send the data

  Front.sendData();
  Rear.sendData();
  
}
