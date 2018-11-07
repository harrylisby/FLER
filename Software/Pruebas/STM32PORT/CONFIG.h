#include <PID_v1.h>

#define ENC_1 PA0
#define OUT_1 PB8

#define ENC_2 PA1
#define OUT_2 PB9

#define I_SENSE PA2

bool currentProtection=false;
bool I_ERROR = false;
double I_READ = 0;
double I_CAL = (3300*2)/4096;
double MAX_CURRENT = 1.50;

uint32_t actualMillis = 0;
uint32_t prevMillis = 0;
uint16_t SP1=135;  //Recibe la lectura del puerto serie
uint16_t SP2=135;
int LM298_IN1 = PB12; //Variables control driver
int LM298_IN2 = PB13;
int LM298_IN3 = PB14;
int LM298_IN4 = PB15;
int enc1, enc2;
double setPoint1, encRead1, output1; //Variables para el PID
double setPoint2, encRead2, output2; //Variables para el PID
uint32_t scaled,scaled2;

bool serialWatchdog=false;
uint16_t PID_UMBRAL=15000;
uint8_t PROG_FREQ=10;


//Parámetros para control del PID (agresivo y conservador)
//double aggKp = 100, aggKi = 0.00, aggKd = 50;
double consKp = 2400, consKi = 0, consKd = 195;
//double consKp = 1250, consKi = 0, consKd = 195;
