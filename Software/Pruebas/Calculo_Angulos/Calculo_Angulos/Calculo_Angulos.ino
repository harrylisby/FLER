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

void setup() {
  Serial.begin(115200);
}

void loop() {
  angulo1A = acos(c1A/p1);
  angulo1B = acos(c1B/p1);
  angulo2A = acos(c2A/p2);
  angulo2B = acos(c2B/p2);

  Serial.print("Ángulo 1A: ");
  Serial.print(angulo1A);
  Serial.print("  Ángulo 1B: ");
  Serial.print(angulo1B);
  Serial.print("  Ángulo 2A: ");
  Serial.print(angulo2A);
  Serial.print("  Ángulo 2B: ");
  Serial.println(angulo2B);
}
