// Contol del lado derecho del motor:

int LM298_IN1=2;
int LM298_IN2=3;

// Contol del lado izquierdo del motor:

int LM298_IN3=4;
int LM298_IN4=5;


char rxChar; 
int ENA = 9;
int ENB = 10;


void setup()
{ 
  
Serial.begin(9600);
    
pinMode(LM298_IN1,OUTPUT);
pinMode(LM298_IN2,OUTPUT);
pinMode(LM298_IN3,OUTPUT);
pinMode(LM298_IN4,OUTPUT);

digitalWrite(LM298_IN1,LOW);
digitalWrite(LM298_IN2,LOW);
digitalWrite(LM298_IN3,LOW);
digitalWrite(LM298_IN4,LOW); 
}

void loop()
{
if(Serial.available())

{
  rxChar = Serial.read();

  
  if(rxChar == 'a')    // avanza
  {

  digitalWrite(LM298_IN1,HIGH);
  digitalWrite(LM298_IN2,LOW);
  digitalWrite(LM298_IN3,HIGH);
  digitalWrite(LM298_IN4,LOW);  
  analogWrite(ENA,20);
  delay(2000);
  analogWrite(ENA,105);
  delay(2000);
  analogWrite(ENA,255);
  delay(2000);
  Serial.println('Adelante');
}

  if(rxChar == 'b')    // giro a la derecha

{
  digitalWrite(LM298_IN1,HIGH);
  digitalWrite(LM298_IN2,LOW);
  digitalWrite(LM298_IN3,LOW);
  digitalWrite(LM298_IN4,HIGH);  
  Serial.println('Derecha');
}

 if(rxChar == 'd')    // giro a la izquierda

{
  digitalWrite(LM298_IN1,LOW);
  digitalWrite(LM298_IN2,HIGH);
  digitalWrite(LM298_IN3,HIGH);
  digitalWrite(LM298_IN4,LOW);  
  Serial.println('Atrás');
}



 if(rxChar == 'c')    // retrocede.

{
   digitalWrite(LM298_IN1,LOW);
  digitalWrite(LM298_IN2,HIGH);
  digitalWrite(LM298_IN3,LOW);
  digitalWrite(LM298_IN4,HIGH); 
  Serial.println('Izquierda'); 
}

 if(rxChar == 'e')    // se detienen

{
   digitalWrite(LM298_IN1,LOW);
  digitalWrite(LM298_IN2,LOW);
  digitalWrite(LM298_IN3,LOW);
  digitalWrite(LM298_IN4,LOW); 
  Serial.println('Apagado'); 
}
}
}



