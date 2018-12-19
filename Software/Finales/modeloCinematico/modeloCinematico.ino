#include <EasyTransfer.h>
#include <EasyTransferI2C.h>

EasyTransferI2C ET;

struct RECEIVE_DATA_STRUCTURE{
  //Exactamente la misma estructura en el otro microcontrolador.
  int16_t Z;
  int16_t Y;
  int16_t X;
};
//nombre de la estructura
RECEIVE_DATA_STRUCTURE myDataI2C;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 9

int16_t SP_IF1, SP_IF2, SP_IF3, SP_DF1, SP_DF2, SP_DF3, SP_IR1, SP_IR2, SP_IR3, SP_DR1, SP_DR2, SP_DR3;

//create object
EasyTransfer Front;
EasyTransfer Rear; 

#define FRONT

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

//Joystic
#define VRx_R PA1
#define VRy_R PA0
#define VRx_L PA5
#define VRy_L PA4



void setup(){
  //Serial - EasyTransfer
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Front.begin(details(frontData), &Serial2);
  Rear.begin(details(rearData), &Serial3);

  //I2C
  Wire.begin(I2C_SLAVE_ADDRESS);
  ET.begin(details(myDataI2C), &Wire);
  Wire.onReceive(receive);

  //Joystic
  pinMode(VRx_R,INPUT_ANALOG);
  pinMode(VRy_R,INPUT_ANALOG);
  pinMode(VRx_L,INPUT_ANALOG);
  pinMode(VRy_L,INPUT_ANALOG);

}

uint32_t currentTime;
uint32_t lastTime1;//Para modeloCinematicoXYZ
uint32_t lastTime2;//Para Joystic
uint32_t lastTime3;//Print modeloCinematicoXYZ

void loop(){
  currentTime = millis();
  //send the data
  Front.sendData();
  Rear.sendData();
  serialDecoder();

  if((currentTime-lastTime1)>10){
    modeloCinematicoXYZ(controllerReader(VRy_L),controllerReader(VRy_R),controllerReader(VRx_R));
    lastTime1=currentTime;
  }
  

  //JoysticReads
  if((currentTime-lastTime2)>500){
    Serial.println("xL: "+String(controllerReader(VRx_L))+" yL: "+String(controllerReader(VRy_L))+" xR: "+String(controllerReader(VRx_R))+" yR: "+String(controllerReader(VRy_R)));
    lastTime2=currentTime;
  }
}

void modeloCinematicoXYZ(double Zpos, double Ypos, double Xpos){ //zyx

//Conversiones: IMPORTANTE CALCULAR LIMITES GEOMETRICOS
  Zpos = convert(Zpos,0,4095,250,350);
  Ypos = convert(Ypos,0,4095,0,150);
  Xpos = convert(Xpos,0,4095,-45,45);

//Variables
  double cita; //Eje Z: Superior
  double citaPrima; //Eje Z: Inferior
  double citaNewY; //Cita con nuevo offset de alfa
  double ZnewY,ZnewX; //Longitud de pierna recalculada para nuevos angulos
  double beta; //Eje Z extra
  double Zex; //Z extra
  double Xex = 56.1305; //X extra const
  double alfa; //Eje Y
  double rho; //Eje X
  double P = 175.00; //longitud estándar
  double mediaAltura = Zpos/2.00; //Mitad de la altura


  //Calculos del eje Z
  cita = acos(mediaAltura/P);
  cita = cita*RAD_TO_DEG;
  citaPrima = 2*cita;
  //Leer valor de beta?
  Zex = Xex*tan(beta*DEG_TO_RAD);
  convert(Zex,-10,10,10,-10);
  //Zex = Zex*RAD_TO_DEG;


  //Calculos del eje Y
  alfa = atan(Ypos/Zpos);
  alfa = alfa*RAD_TO_DEG;
  citaNewY=cita-alfa;

  if(citaNewY!=cita)cita=citaNewY; //Escribe nuevo valor con offset

  ZnewY=Zpos/(cos(alfa*DEG_TO_RAD));

  //Calculos del eje X
  rho = atan(Xpos/ZnewY);
  rho = rho*RAD_TO_DEG;

  //ZnewX = ZnewY/cos(rho*DEG_TO_RAD);

  ZnewX = (ZnewY+Zex)/cos(rho*DEG_TO_RAD); //Con offset Zex
  cita = constrain(cita,0,45);

  //CORREGIR Y SEPARAR EJES DE NUEVO ZPOS

  if((currentTime-lastTime3)>500){
    Serial.println("cita: "+String(cita)+" citaP: "+String(citaPrima)+" Zpos: "+String(Zpos)+" ZnewX: "+String(ZnewX)+" alfa: "+String(alfa)+" Ypos: "+String(Ypos)
    +" rho: "+String(rho)+" Xpos: "+String(Xpos));
  }
}

double convert(double x, double in_min, double in_max, double out_min, double out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double controllerReader(int analogPin){
  return analogRead(analogPin);
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

//i2c handler
void receive(int numBytes) {}



