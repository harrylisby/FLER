#include <EasyTransfer.h>

int16_t SP_IF1, SP_IF2, SP_IF3, SP_DF1, SP_DF2, SP_DF3, SP_IR1, SP_IR2, SP_IR3, SP_DR1, SP_DR2, SP_DR3;

//create object
EasyTransfer Front;
EasyTransfer Rear; 

#define FRONT

#ifdef FRONT
String valorAImprimir = "front";
#endif

#ifdef REAR
String valorAImprimir = "rear";
#endif

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
  serialDecoder();


  //Serial.println(valorAImprimir);
  
}

void modeloCinematico(double Zpos, double Ypos, double Xpos){ //zyx
//Variables
  double cita; //Eje Z: Superior
  double citaPrima; //Eje Z: Inferior
  double beta; //Eje Z extra
  double Zex; //Z extra
  double Xex = 56.1305; //X extra const
  double alfa; //Eje Y
  double rho; //Eje X
  double P = 175; //Longitud estándar
  double mediaAltura = Zpos/2; //Mitad de la altura

  //Calculos del eje Z
  cita = acos(mediaAltura/P);
  citaPrima = 2*cita;
  //Leer valor de beta?
  Zex = Xex*tan(beta);
  //Convertir a grados?


  //Calculos del eje Y
  alfa = atan(Ypos/Zpos);
  //Convertir a grados?

  //Calculos del eje X
  rho = atan(Xpos/Zpos);

}

void serialDecoder(){
  if (Serial.available() > 0) {
    frontData.SSP_IF1=decodePrintData('z',frontData.SSP_IF1);
    frontData.SSP_IF2=decodePrintData('x',frontData.SSP_IF2);
    frontData.SSP_IF3=decodePrintData('c',frontData.SSP_IF3);
    rearData.SSP_IR1=decodePrintData('v',rearData.SSP_IR1);
    rearData.SSP_IR2=decodePrintData('b',rearData.SSP_IR2);
    rearData.SSP_IR3=decodePrintData('n',rearData.SSP_IR3);

  }
  while(Serial.available() > 0)Serial.read();
}

uint16_t decodePrintData(char expectedChar,uint16_t currentData){
  uint16_t readV=currentData;
  if(Serial.peek()==expectedChar){
    Serial.read();
    readV=Serial.parseInt();
    Serial.println("Nuevo valor: "+String(readV));
  }
  return readV;
}