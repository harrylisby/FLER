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
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t blinks;
  int16_t pause;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &Serial2);
  
  pinMode(PC13, OUTPUT);
  
}

void loop(){
  //check and see if a data packet has come in. 
  if(ET.receiveData()){

    Serial.println("B: " + String(mydata.blinks) + "P: " + String(mydata.pause));
    
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
    for(int i = mydata.blinks; i>0; i--){
      digitalWrite(PC13, HIGH);
      delay(mydata.pause * 100);
      digitalWrite(PC13, LOW);
      delay(mydata.pause * 100);
    }
  }
  
  //you should make this delay shorter then your transmit delay or else messages could be lost
  delay(250);
}
