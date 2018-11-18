int p1 = 175; // en milimetros
double c1A = 140; //en milimetros
double angulo1A; // en radianes
double c1B = 140;
double angulo1B;

int p2 = 175;
double c2A = 165;
double angulo2A;
double c2B = 165;
double angulo2B;

double c3A;
double c3B;
double c4A =200; //elegir variable (prueba)
double angulo4A;
double c4B =200; //elegir variable (prueba)
double angulo4B;

void setup() {
  Serial.begin(115200);
}

void loop() {
  angulo1A = (acos(c1A/p1)*180)/PI;
  angulo1B = 45 + (45 - (acos(c1B/p1)*180)/PI);
  angulo2A = (acos(c2A/p2)*180)/PI;
  angulo2B = 45 + (45 - (acos(c2B/p2)*180)/PI);
  c3A = c1A + c2A;
  c3B = c1B + c2B;
  angulo4A = (acos(c4A/c3A)*180)/PI;
  angulo4B = 45 + (45 - (acos(c4B/c3B)*180)/PI);

  Serial.print("Ángulo 1A: ");
  Serial.print(angulo1A);
  Serial.print("  Ángulo 1B: ");
  Serial.print(angulo1B);
  Serial.print("  Ángulo 2A: ");
  Serial.print(angulo2A);
  Serial.print("  Ángulo 2B: ");
  Serial.print(angulo2B);
  Serial.print("  Ángulo 4A: ");
  Serial.print(angulo4A);
  Serial.print("  Ángulo 4B: ");
  Serial.println(angulo4B);
}
