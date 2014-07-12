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
  delay(2000);
}

void setSpeedMotor(int motor, int val){ // 0 = x1, 1=x2 , 2= y1, 3 = y2
  int realVal = 0;
  if(val > 0)
    realVal = map(val, 1, 1000, 1185, 2000);
    
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


void incrSpeedMotor(int motor){//@TODO -> 0 = x1, 1 =x2, 2 = y1, 3 = y2
    int realVal = 0;

    
    
  if(motor == MOTOR_X1){
    X1Speed++;
    realVal = map(X1Speed, 1, 1000, 1185, 2000);
    motorX1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_X2){
    X2Speed++;
    realVal = map(X2Speed, 1, 1000, 1185, 2000);
    motorX2.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y1){
    Y1Speed++;
    realVal = map(Y1Speed, 1, 1000, 1185, 2000);
    motorY1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y2){
    Y2Speed++;
    realVal = map(Y2Speed, 1, 1000, 1185, 2000);
    motorY2.writeMicroseconds(realVal);
  }
}

void decrSpeedMotor(int motor){//@TODO -> 0 = x1, 1 =x2, 2 = y1, 3 = y2
    int realVal = 0;
    
  if(motor == MOTOR_X1){
    X1Speed--;
    realVal = map(X1Speed, 1, 1000, 1185, 2000);
    motorX1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_X2){
    X2Speed--;
    realVal = map(X2Speed, 1, 1000, 1185, 2000);
    motorX2.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y1){
    Y1Speed--;
    realVal = map(Y1Speed, 1, 1000, 1185, 2000);
    motorY1.writeMicroseconds(realVal);
  }
  else if(motor == MOTOR_Y2){
    Y2Speed--;
    realVal = map(Y2Speed, 1, 1000, 1185, 2000);
    motorY2.writeMicroseconds(realVal);
  }
}

void setSpeedMotors(int val){
   motorX1.writeMicroseconds(val);
   motorX2.writeMicroseconds(val);
   motorY1.writeMicroseconds(val);
   motorY2.writeMicroseconds(val);
   
}

