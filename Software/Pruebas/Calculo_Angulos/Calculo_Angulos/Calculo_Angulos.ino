uint32_t microsBegin,microsEnd;


double p1 = 175; // en milimetros
double c1A = 165; //en milimetros
double angulo1A; // en radianes
//double c1A = 140;
double angulo1B;

double p2 = 175;
double c2A = 155;
double angulo2A;
double c2B = 165;
double angulo2B;

double HD = 56.1305;
double c3A;
//double c3B;
//double c4A =200; //elegir variable (prueba)
double angulo4A;
//double c4B =200; //elegir variable (prueba)
//double angulo4B;

void setup() {
  Serial.begin(115200);
}

// double c1,c1x,c2,c2x,sita,lamda,beta,omega,alfa,gamma;
// double c1h = 175;



void loop() {
  microsBegin = micros();

//FORMA HARRY///////////////////////////////////////////////

  // c1 = c1h*cos(sita);
  // c1x = c1h*cos(lamda);
  // c2x = c2h*cos(beta);
  // c2 = c2h*cos(omega);

  // alfa = sita+abs(lamda-45);
  // gamma = beta+abs(omega-45);



//FORMA HARRY///////////////////////////////////////////////

// el angulo va de 0 - 90
// nos envia 

  angulo1A = 45 - (acos(c1A/p1)*180)/PI;
  angulo1B = 45 + (acos(c1A/p1)*180)/PI;
  angulo2A = 45 - (acos(c2A/p2)*180)/PI;
  angulo2B = 45 + (acos(c2B/p2)*180)/PI;
  c3A = c1A + c2A;
  //c3B = c1A + c2B;
  angulo4A = (atan(c3A/HD)*180)/PI;
  //angulo4B = (acos(c4B/c3B)*180)/PI;



  Serial.print("Ángulo 1A: ");
  Serial.print(angulo1A);
  Serial.print("  Ángulo 1B: ");
  Serial.print(angulo1B);
  Serial.print("  Ángulo 2A: ");
  Serial.print(angulo2A);
  Serial.print("  Ángulo 2B: ");
  Serial.print(angulo2B);
  Serial.print("  Ángulo 4A: ");
  Serial.println(angulo4A);
  //Serial.print("  Ángulo 4B: ");
  //Serial.println(angulo4B);

  Serial.print("t: ");
  Serial.println(microsBegin-microsEnd);
  microsEnd = microsBegin;
}
