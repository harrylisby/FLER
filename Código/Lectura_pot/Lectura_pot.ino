int POT = 4;
int POS = 0;
int grados;
int ENA = 9; 
int ENB = 10;

int LM298_IN1=2;
int LM298_IN2=3;
int LM298_IN3=4;
int LM298_IN4=5;

void setup() {
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

void loop() {
  POS = analogRead(POT);
  //Serial.println(POS);

  grados = map(POS, 0, 1023, 0, 270);
  Serial.println(grados);
  delay (1000);
  
  
  digitalWrite(LM298_IN1,HIGH);
  digitalWrite(LM298_IN2,LOW);
  digitalWrite(LM298_IN3,HIGH);
  digitalWrite(LM298_IN4,LOW);  
  analogWrite(ENB,75);

 

  digitalWrite(LM298_IN1,LOW);
  digitalWrite(LM298_IN2,HIGH);
  digitalWrite(LM298_IN3,LOW);
  digitalWrite(LM298_IN4,HIGH);  
  analogWrite(ENA,75);

  
  digitalWrite(LM298_IN1,LOW);
  digitalWrite(LM298_IN2,LOW);
  digitalWrite(LM298_IN3,LOW);
  digitalWrite(LM298_IN4,LOW);  
  analogWrite(ENA,0);
  
 
  

