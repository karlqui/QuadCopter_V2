//@TODO Keep the balance
float prevY, prevP, prevR, prevAlt = 0;
float diffP, diffR, diffAlt;
float prevDiffP, prevDiffR, prevDiffAlt, prevDiffY;
float totSpeedAlt = 0;
float speedP, speedR, speedAlt;
float speedPDiffAngle, speedRDiffAngle;
int nrOfSpins = 0; //the number of 360 spins from original position, the number of times yaw goes from 360 to 0 -> negative if counter-clockwise

bool prevPassed = false;
bool passedC = false;
bool passedCCW = false;

float angularSpeed[5];
int angularSpeedIndex = 0;
float angularSpeedSum = 0;
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void balance(float y, float p, float r, float alt, float spin, float desiredP, float desiredR, float desiredAlt){ //try to stay at pitch roll and alt - spin indicates a desired yaw rotation, if zero -> stay at current yaw
    
    //altitude calc
    diffAlt = desiredAlt - alt; //if positive -> increase speed.. if negative -> decrease speed
    prevDiffAlt = alt - prevAlt; //if positive copter is elevating.. 
    
    speedAlt = mapFloat(abs(prevDiffAlt),0,400.0, 1.0, 20.0); 
    if(speedAlt > 20.0)
      speedAlt = 20;
    if(diffAlt > 0 && prevDiffAlt <= 0){//copter need to elevate but is currently not -> increase speed
      totSpeedAlt += abs(speedAlt);
      if(totSpeedAlt>600){
        totSpeedAlt = 600;
      }
    }
    else if(diffAlt < 0 && prevDiffAlt > 0){ //copter does not need to elevate, but is currently elavating -> decrease speed
      totSpeedAlt -= abs(speedAlt);
      if(totSpeedAlt < 1){
        totSpeedAlt = 1;
      }
    }
    prevAlt = alt;
    
    //calculate speed ïn pitch direction
    diffP = desiredP - p;
    prevDiffP = prevP - p;
    
    angularSpeed[angularSpeedIndex] = prevDiffP;
    angularSpeedIndex++;
    if(angularSpeedIndex > 4){
      angularSpeedSum = 0;
      for(int i = 0; i<5; i++){
        angularSpeedSum += angularSpeed[i];
        
      }
      angularSpeedIndex = 0;
    }
    
    speedP = mapFloat(diffP, -45, 45, -200, 200); 
    speedPDiffAngle = mapFloat(prevDiffP, -30, 30, -500, 500);
    
    if(speedPDiffAngle < 0 && speedP < 0){ //negative angle and still decreasing
      speedP+= speedPDiffAngle;
      setSpeedMotor(MOTOR_X2, totSpeedAlt + abs(speedP));
      setSpeedMotor(MOTOR_X1, totSpeedAlt);
    }
    else if(speedPDiffAngle < 0 && speedP > 0){ //positive angle but decreasing 
      speedP = speedPDiffAngle;
      setSpeedMotor(MOTOR_X2, totSpeedAlt + abs(speedP));
      setSpeedMotor(MOTOR_X1, totSpeedAlt);
    }
    else if(speedPDiffAngle > 0 && speedP > 0){ //positive angle and increasing
      speedP+= speedPDiffAngle;
      setSpeedMotor(MOTOR_X1, totSpeedAlt + abs(speedP));
      setSpeedMotor(MOTOR_X2, totSpeedAlt);
    }
    else if(speedPDiffAngle > 0 && speedP < 0){ //negative angle but increasing
      speedP = speedPDiffAngle;
      setSpeedMotor(MOTOR_X1, totSpeedAlt + abs(speedP));
      setSpeedMotor(MOTOR_X2, totSpeedAlt);
    }
    
    Serial.println(speedP);
    prevP = p;
    
    if(speedP < 0){
      
    }
    else if(speedP > 0){
      
    }
    //roll
    
    diffR = desiredR - r;
    prevDiffR = prevR - r;
    speedR = mapFloat(diffR, -90, 90, -500, 500);
    speedRDiffAngle = mapFloat(prevDiffR, -45, 45, -500, 500);
    speedR += speedRDiffAngle;
    prevR = r;
    
    if(speedR < 0){
      setSpeedMotor(MOTOR_Y1, totSpeedAlt + abs(speedR));
      setSpeedMotor(MOTOR_Y2, totSpeedAlt);
    }
    else if(speedR > 0){
      setSpeedMotor(MOTOR_Y2, totSpeedAlt + abs(speedR));
      setSpeedMotor(MOTOR_Y1, totSpeedAlt);
    }
    
    //yaw
   
    prevDiffY = prevY - y;
    
    if(abs(prevDiffY) > 100) //@TODO bad method for checking spin
    {
      //copter has gone from either 360 to 0 or 0 to 360
      
      if(!prevPassed){
        if(prevDiffY>0)
          passedC = true;
        else
          passedCCW = true;
      }
        
      prevPassed = true;
    }
    else
      prevPassed = false;
    
    if(spin == 0){//stay at prevYaw
      if(prevY > y){ //is rotating counterclockwise 
        if(passedC) //is actually rotating clockwise but went from 360 to 0
        {
          
        }
        else{
        
        }   
      }
      else{ //rotating clockwise -> increase yaw
        if(passedCCW) //is actually rotating ccw but went from 0 to 360
        {
        }
        else{
        
        }
      }
    }
    passedC = passedCCW = false; //reset to false
    prevY = y;
    //Serial.println(alt);
}
