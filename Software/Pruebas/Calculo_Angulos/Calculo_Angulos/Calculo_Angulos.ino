//I LOVE SOHCAHTOA

uint32_t microsBegin,microsEnd;
double valZ, valX, valY;

void setup() {
  Serial.begin(115200);
}

void loop() {
  microsBegin = micros();

  modeloCinematico(valZ, valY, valX);

  Serial.print("   t: ");
  Serial.println(microsBegin-microsEnd);
  microsEnd = microsBegin;
}


void modeloCinematico(double Zpos, double Ypos, double Xpos){ //zyx
//Variables
  double cita; //Eje Z: Superior
  double citaPrima; //Eje Z: Inferior
  double beta; //Eje Z extra
  double Zex; //Z extra
  double Xex = 56.1305; //X extra const
  double alfa; //Eje Y
  double rho; //Eje X
  double P = 175; //Longitud estándar
  double mediaAltura = Zpos/2; //Mitad de la altura

  //Calculos del eje Z
  cita = acos(mediaAltura/P);
  citaPrima = 2*cita;
  //Leer valor de beta?
  Zex = Xex*tan(beta);
  //Convertir a grados?


  //Calculos del eje Y
  alfa = atan(Ypos/Zpos);
  //Convertir a grados?

  //Calculos del eje X
  rho = atan(Xpos/Zpos);

}
