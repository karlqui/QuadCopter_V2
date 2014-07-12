//running quadcopter
void runCopter(){
  Serial.println("TEST");
  setupMotors();
  testMode2
  ();
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
        
      setSpeedMotor(MOTOR_X2, x2);
      setSpeedMotor(MOTOR_Y1, y1);
      setSpeedMotor(MOTOR_Y2, y2);
      setSpeedMotor(MOTOR_X1, x1);

    }
  }
}
float prevHeading;
float prevRoll, diffRoll;
float diffRollArr[10];
float rollArr[10];
float pitchArr[10];
float yawArr[10];
float yawSum = 0;
float pitchSum = 0;
float diffRollSum = 0;
float rollSum = 0;
int arrIndex = 0;
float calYaw;
float prevYaw;

void testMode2(){
  calYaw = heading;
  while(1){
    while(checkInterrupt()){
      updateDistance();
      updateHeading();
    }
    prevRoll = roll;
    prevYaw = yaw;
    handleInterrupt();
    updateYawPitchRoll();
    updateWorldAccel();
   
    diffRoll = roll - prevRoll;
     
    diffRollArr[arrIndex] = diffRoll;
    rollArr[arrIndex] = roll;
    pitchArr[arrIndex] = pitch;
    yawArr[arrIndex] = yaw;
    calYaw = (0.98 * (yaw - prevYaw + calYaw)) + (0.02 * (heading)); //simple complimentary filter to get correct but still pretty fast updates on heading changes
    
    arrIndex++;
    
      if(arrIndex>9){
        for(int i =0;i < 10; i++){
          double temp = diffRollArr[i];
          diffRollSum += temp;
          rollSum += rollArr[i];
          pitchSum += pitchArr[i];
          yawSum += yawArr[i];
      }
      rollSum /= 10;
      pitchSum /= 10;
      yawSum /= 10;
      arrIndex = 0;
      Serial.print("Yaw: " + String(yawSum) + "  ");
      Serial.print("Pitch: " + String(pitchSum) + "  ");
      Serial.print("Roll: " + String(rollSum) + "  ");
      Serial.print("Heading: " + String(heading) + "  ");
      Serial.print("calYaw: " + String(calYaw) + "  ");
      Serial.println("Distance: " + String(distance));
      Serial.println("--------------------------------------------------------------------");
        
      diffRollSum = 0;
      rollSum = 0;
      pitchSum = 0;
      yawSum = 0;
    }
  }
}
