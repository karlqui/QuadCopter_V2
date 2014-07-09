//running quadcopter
void runCopter(){
  Serial.println("TEST");
  setupMotors();
  testMode();
}

void testMode(){
  Serial.println("X1 X2 Y1 Y2");
  while(1){
    if(Serial.available() > 0){
      
      int x1 = Serial.parseInt();
      int x2 = Serial.parseInt();
      int y1 = Serial.parseInt();
      int y2 = Serial.parseInt();
      RFSerial.println("ASDASDASD");
      Serial.println("X1: " + String(x1));
      Serial.println("X2: " + String(x2));
      Serial.println("Y1: " + String(y1));
      Serial.println("Y2: " + String(y2));
      while(Serial.available() > 0 )
        Serial.read();
      motorX1.writeMicroseconds(x1);
      motorX2.writeMicroseconds(x2);
      motorY1.writeMicroseconds(y1);
      motorY2.writeMicroseconds(y2);

    }
  }
}
