//running quadcopter
void runCopter(){
  setupMotors();
  testMode3();
}

/*void testMode1(){
  
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

  /*     motorX1.writeMicroseconds(x1);
     motorX2.writeMicroseconds(x2);
     motorY1.writeMicroseconds(y1);
     motorY2.writeMicroseconds(y2);*/
/*    }
  }
}*/


float prevHeading;
float prevRoll, diffRoll;
float dist;
float yawSum = 0;
float pitchSum = 0;
float diffRollSum = 0;
float rollSum = 0;
int arrIndex = 0;
float calYaw;
float prevYaw;
float distArr[2];
float distSum;
float baseAlt;
bool usingBMP = false;
float prevCalYaw;
void testMode3(){ //also test balancing algorithm
  calYaw = heading;
  updateDistance();
  updateHeading();
  int updateIndex = 0;
  while(1){
    while(!mpuInterrupt){
      if(distance != getMaximumRange())
      {
        updateDistance();
        dist = distance;
        usingBMP = false;
        
      }
      else{

          updateAltitude();
          if(usingBMP == false)//if just started messuring bmp
            baseAlt = altitude_;
          dist = (altitude_) * 1000 + (float)getMaximumRange();
          if((altitude_) < 0)
            distance = getMaximumRange() - 1; //start using the ultra-sound sensor 
          usingBMP = true;
          updateIndex = 0;
      }

      
      prevHeading = heading;
      updateHeading();
      
      
    }

    handleInterrupt();
    updateYawPitchRoll();
    
    prevCalYaw = calYaw;
    if(abs(prevHeading - heading) > 100)
      calYaw = (0.02 * (yaw - prevYaw + calYaw)) + (0.98 * (heading)); //reverse complimentary for quick update on heading
    else
      calYaw = (0.98 * (yaw - prevYaw + calYaw)) + (0.02 * (heading)); //simple complimentary filter to get correct but still pretty fast updates on heading changescalcalYawArr
    if(calYaw < 0 || calYaw > 360) //for safety in case abs(prevYaw - yaw) gets too big
      calYaw = prevCalYaw;
   

      balance(calYaw, pitch, roll, dist, 0, 0, 0, 100.0);

    
  }
}
