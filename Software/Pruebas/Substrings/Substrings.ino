String cadena;

void setup(){
  Serial.begin(9600);
  
}

void loop(){
  if (Serial.available()){
    cadena = Serial.readString();
  String temp = cadena.substring(0,4);
  String HR = cadena.substring(5,7);
  String gas = cadena.substring(8,9);
   
  Serial.println("Temp: " + temp + " HR: " + HR + " Gas: " + gas);
    //Serial.println(cadena);
  }

   //while(Serial.available()>0)Serial.read();
 
  
}


