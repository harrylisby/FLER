//SENSOR ULTRASONICO
const int Trigger = 8; //pin digital 8 para el Trigger del sensor
const int Echo = 9; // pin digital 9 para el Echo del sensor

//MOTOR
int IN3 = 10; //pin de control para el motor
int IN4 = 11; //pin de control para el motor
int motor_speed; 

void setup() {
 Serial.begin(9600); //iniciar la comunicacion
 
 //SENSOR ULTRASONICO
 pinMode(Trigger, OUTPUT); // pin como salida
 pinMode(Echo, INPUT); //pin como entrada
 digitalWrite(Trigger, LOW); // iniciamos el pin con un valor de 0

 //MOTOR
 pinMode(IN3, OUTPUT); //pin de control del motor como salida
 pinMode(IN4, OUTPUT); //pin de contron del motor como salida
 
}

void loop() {
  
  //SENSOR ULTRASONICO
  long t; //tiempo que demora en llegar el eco
  long d; //distancia en centimetros
  
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10); //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);

  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59; //escalamos el tiempo a una distancia en cm

  Serial.print("Distancia: ");
  Serial.print(d); //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //MOTOR
  if (d < 15){
    digitalWrite(IN3, HIGH);
  }
  else{
    digitalWrite(IN3, LOW);
  }
  
  delay(100); // hacemos una pausa de 100ms
}
