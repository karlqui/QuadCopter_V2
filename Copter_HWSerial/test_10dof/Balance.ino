//@TODO Keep the balance

void balance(float y, float p, float r, float alt, float desiredY, float desiredP, float desiredR, float disiredAlt){ //try to stay at yaw pitch roll and alt

    //calibrate for yaw
    if(y > desiredY){
      incrSpeedMotor(MOTOR_Y1);
      incrSpeedMotor(MOTOR_Y2);
      decrSpeedMotor(MOTOR_X1);
      decrSpeedMotor(MOTOR_X2);
    }
    else if(y < desiredY){
      decrSpeedMotor(MOTOR_Y1);
      decrSpeedMotor(MOTOR_Y2);
      incrSpeedMotor(MOTOR_X1);
      incrSpeedMotor(MOTOR_X2);
    }
    
    //calibrate for pitch
    if(p > desiredP){
      decrSpeedMotor(MOTOR_Y2);
      incrSpeedMotor(MOTOR_Y1);
    }
    else if(p < desiredP){
      incrSpeedMotor(MOTOR_Y2);
      decrSpeedMotor(MOTOR_Y1);
    }
    
    //calibrate for roll
    if(r > desiredR){
      decrSpeedMotor(MOTOR_X1);
      incrSpeedMotor(MOTOR_X2);
    }
    else if(r < desiredR){
      incrSpeedMotor(MOTOR_X1);
      decrSpeedMotor(MOTOR_X2);
    }
    
    //calibrate alt
    
    if(alt > desiredAlt){
      decrSpeedMotor(MOTOR_Y1);
      decrSpeedMotor(MOTOR_Y2);
      decrSpeedMotor(MOTOR_X1);
      decrSpeedMotor(MOTOR_X2);
    }
    else if(alt < desiredAlt){
      incrSpeedMotor(MOTOR_Y1);
      incrSpeedMotor(MOTOR_Y2);
      incrSpeedMotor(MOTOR_X1);
      incrSpeedMotor(MOTOR_X2);
    }
      /*om + X1 -> + roll
    om + Y2 -> + pitch
       
    Ta reda på z-rot och heading i förrhållande till motorer
    
    Höger - > ökar heading
    
    x1 + x2 -> heading ökar
    y1 + y2 -> heading minskar*/
}
