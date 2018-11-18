void setup() {
//  int p1 = 175; // en milimetros
//  double c1 = 140; //en milimetros
//  double angulo1;
  Serial.begin(115200);
}

void loop() {
  int p1 = 175; // en milimetros
  double c1 = 140; //en milimetros
  double angulo1;
  angulo1 = acos(c1/p1);
  
  int p2 = 175; // en milimetros
  double c2 = 165; //en milimetros
  double angulo2;
  angulo2 = acos(c2/p2);

  Serial.print("Ángulo 1: ");
  Serial.print(angulo1);
  Serial.print("  Ángulo 2: ");
  Serial.println(angulo2);
}
