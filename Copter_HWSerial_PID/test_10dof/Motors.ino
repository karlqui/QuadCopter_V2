#include <Servo.h>

Servo motorX1, motorX2, motorY1, motorY2;
int X1Speed, X2Speed, Y1Speed, Y2Speed = 0;


void setupMotors(){
  motorX1.attach(10); //X positive angle	
  motorY1.attach(9); //Y positive angle
  motorX2.attach(6); //X negative angle
  motorY2.attach(11); //Y negative angle
  delay(50);
  motorX1.write(10); //Initiate motors
  motorX2.write(10);
  motorY1.write(10);
  motorY2.write(10);
  delay(3000);
}

int getSpeedMotor(int motor){
  if(motor == MOTOR_X1)
    return X1Speed;
  else if(motor == MOTOR_X2)
    return X2Speed;
  else if(motor == MOTOR_Y1)
    return Y1Speed;
  else if(motor == MOTOR_Y2)
    return Y2Speed;
}

void setSpeedMotor(int motor, int val){ // 0 = x1, 1=x2 , 2= y1, 3 = y2
  int realVal = 0;
  
  if(val < 1)
    val = 1;
  else if(val > 1000)
    val = 1000;
  
  realVal = map(val, 1, 1000, 1048, 2000);
    
  if(motor == MOTOR_X1){
    X1Speed = val;
    motorX1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_X2){
    X2Speed = val;
    motorX2.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y1){
    Y1Speed = val;
    motorY1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y2){
    Y2Speed = val;
    motorY2.writeMicroseconds(realVal);
  }
}


void incrSpeedMotor(int motor, int val){//@TODO -> 0 = x1, 1 =x2, 2 = y1, 3 = y2
    int realVal = 0;
  
    
    
  if(motor == MOTOR_X1){
    X1Speed+=val;
    if(X1Speed > 1000)
      X1Speed = 1000;
    realVal = map(X1Speed, 1, 1000, 1048, 2000);
    motorX1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_X2){
    X2Speed+=val;
    if(X2Speed > 1000)
      X2Speed = 1000;
    realVal = map(X2Speed, 1, 1000, 1048, 2000);
    motorX2.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y1){
    Y1Speed+=val;
    if(Y1Speed > 1000)
      Y1Speed = 1000;
    realVal = map(Y1Speed, 1, 1000, 1048, 2000);
    motorY1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y2){
    Y2Speed+=val;
    if(Y2Speed > 1000)
      Y2Speed = 1000;
    realVal = map(Y2Speed, 1, 1000, 1048, 2000);
    motorY2.writeMicroseconds(realVal);
  }
}

void decrSpeedMotor(int motor, int val){
    int realVal = 0;
    
  if(motor == MOTOR_X1){
    X1Speed-=val;
    if(X1Speed < 0)
      X1Speed = 0;
    
    realVal = map(X1Speed, 1, 1000, 1048, 2000);
    motorX1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_X2){
    X2Speed-=val;
    if(X2Speed < 0)
      X2Speed = 0;
    realVal = map(X2Speed, 1, 1000, 1048, 2000);
    motorX2.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y1){
    Y1Speed-=val;
    if(Y1Speed < 0)
      Y1Speed = 0;
    realVal = map(Y1Speed, 1, 1000, 1048, 2000);
    motorY1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y2){
    Y2Speed-=val;
    if(Y2Speed < 0)
      Y2Speed = 0;
    realVal = map(Y2Speed, 1, 1000, 1048, 2000);
    motorY2.writeMicroseconds(realVal);
  }
}





