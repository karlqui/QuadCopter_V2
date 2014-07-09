//running quadcopter
void runCopter(){
  Serial.println("TEST");
  setupMotors();
  testMode2();
}

void testMode1(){
  Serial.println("X1 X2 Y1 Y2");
  while(1){
    if(Serial.available() > 0){
      
      int x1 = Serial.parseInt();
      int x2 = Serial.parseInt();
      int y1 = Serial.parseInt();
      int y2 = Serial.parseInt();
      Serial.println("X1: " + String(x1));
      Serial.println("X2: " + String(x2));
      Serial.println("Y1: " + String(y1));
      Serial.println("Y2: " + String(y2));
      while(Serial.available() > 0 )
        Serial.read();
        
      setSpeedX2(x2);
      setSpeedY1(y1);
      setSpeedY2(y2);
      setSpeedX1(x1);

    }
  }
}
float prevRoll, diffRoll;
float diffRollArr[10];
float rollArr[10];
float diffRollSum = 0;
float rollSum = 0;
int arrIndex = 0;
void testMode2(){
  while(1){
    while(checkInterrupt()){
    
    }
    prevRoll = roll;
    handleInterrupt();
    updateYawPitchRoll();
    updateWorldAccel();
   
    diffRoll = roll - prevRoll;
     
    diffRollArr[arrIndex] = diffRoll;
    rollArr[arrIndex] = roll;
    arrIndex++;
    
    if(arrIndex>9){
      for(int i =0;i < 10; i++){
        double temp = diffRollArr[i];
        diffRollSum += temp;
        rollSum += rollArr[i];
      }
      rollSum /= 10;
      arrIndex = 0;
        Serial.println(String(rollSum));
      diffRollSum = 0;
      rollSum = 0;
    }
  }
}
