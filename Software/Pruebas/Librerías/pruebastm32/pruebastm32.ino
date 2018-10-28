bool pcStat=0;
void setup() {
  pinMode(PC13,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  pcStat=!pcStat;
  digitalWrite(PC13,pcStat);
  delay(1000);
  Serial.println(pcStat);
}
