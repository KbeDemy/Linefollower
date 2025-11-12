uint32_t vorigeMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
}

void loop() {
  if (millis() - vorigeMillis >= 1000){
    char buffer[200];

    vorigeMillis = millis();

    sprintf(buffer, "S1: %d , S2: %d , S3: %d , S4: %d , S5: %d , S6 : %d , S7 : %d , S8 : %d", 
    analogRead(33), analogRead(32), analogRead(27), analogRead(14), 
    analogRead(39), analogRead(36), analogRead(34), analogRead(35));
    // s1 =33 ,s2=32 ,s3=27 ,s4=14 ,s5=39 ,s6=36 ,s7=34 ,s8=35
    Serial.println(buffer);
  }
}
