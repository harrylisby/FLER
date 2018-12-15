uint32_t microsBegin,microsEnd;

double p1 = 175; // en milimetros
double c1A = 165; //en milimetros
double angulo1A; // de radianes a grados
double angulo1B;

double p2 = 175;
double c2A = 155;
double angulo2A;
double c2B = 165;
double angulo2B;

double HD = 56.1305;
double c3A;
double angulo4A;
double angulo4B1 = 0.174533;
double angulo4B2 = 0.261799;
double HD1;
double HD2;

void setup() {
  Serial.begin(115200);
}

void loop() {
  microsBegin = micros();

  angulo1A = 45 - RAD_TO_DEG*(acos(c1A/p1));
  angulo1B = 45 + RAD_TO_DEG*(acos(c1A/p1));
  angulo2A = 45 - RAD_TO_DEG*(acos(c2A/p2));
  angulo2B = 45 + RAD_TO_DEG*(acos(c2B/p2));
  c3A = c1A + c2A;
  angulo4A = RAD_TO_DEG*(atan(c3A/HD)); //triángulo verde
  HD1 = tan(angulo4B1)*HD;//ultimo triangulo
  HD2 = tan(angulo4B2)*HD;
  
  Serial.print("Ángulo 1A: ");
  Serial.print(angulo1A);
  Serial.print("  Ángulo 1B: ");
  Serial.print(angulo1B);
  Serial.print("  Ángulo 2A: ");
  Serial.print(angulo2A);
  Serial.print("  Ángulo 2B: ");
  Serial.print(angulo2B);
  Serial.print("  Ángulo 4A: "); //triángulo verde
  Serial.print(angulo4A);
  Serial.print("  HD1: "); // triángulo de arriba
  Serial.print(HD1);  
  Serial.print("  HD2: "); // triángulo de arriba
  Serial.print(HD2);
  
  Serial.print("   t: ");
  Serial.println(microsBegin-microsEnd);
  microsEnd = microsBegin;
}
