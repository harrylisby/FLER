#include <EasyTransfer.h>



//create object
EasyTransfer Front;
EasyTransfer Rear; 



//*********************************************************************
struct SEND_DATA_STRUCTURE{

  
  
};

//give a name to the group of data
SEND_DATA_STRUCTURE frontData;
//*********************************************************************


//*********************************************************************
struct SEND_DATA_STRUCTURE_2{


  
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
