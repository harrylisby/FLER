uint32_t microsBegin,microsEnd;

double p1 = 175; // parte de arriba de la pata en milimetros
double c1A = 165; // adyacente pata arriba en milimetros (VARIABLE)
double angulo1A;
double angulo1B;

double p2 = 175; // parte de abajo de la pata en milimetros
double c2A = 165; // adyacente de la parte de abajo (VARIABLE)
double angulo2A;
double angulo2B;

double HD = 56.1305; // distancia entre el eje del hombro y la pata
double c3A; // Parte de arriba + parte de abajo de la pata
double angulo4A; // Triángulo grande (pata completa)
double angulo4B1 = 0.174533; // 10 grados en radianes
double angulo4B2 = 0.261799; // 15 grados en radianes
double HD1; // opuesto del angulo 4B1
double HD2; // opuesto del angulo 4B2

void setup() {
  Serial.begin(115200);
}

void loop() {
  microsBegin = micros();

  angulo1A = 45 - RAD_TO_DEG*(acos(c1A/p1));
  angulo1B = 45 + RAD_TO_DEG*(acos(c1A/p1));
  angulo2A = 45 - RAD_TO_DEG*(acos(c2A/p2));
  angulo2B = 45 + RAD_TO_DEG*(acos(c2A/p2));
  c3A = c1A + c2A;
  angulo4A = RAD_TO_DEG*(atan(c3A/HD));
  HD1 = tan(angulo4B1)*HD;
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
