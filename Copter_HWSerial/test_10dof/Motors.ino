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

void setSpeedX1(int val){ // i promille
  if(val == 0){
    motorX1.write(0);
    return;
  }
  int realVal = map(val, 1, 1000, 1185, 2000);
  motorX1.writeMicroseconds(realVal);
}
void setSpeedX2(int val){ // i promille
  if(val == 0){
    motorX2.write(0);
    return;
  }
  int realVal = map(val, 1, 1000, 1185, 2000);
  motorX2.writeMicroseconds(realVal);
}
void setSpeedY1(int val){ // i promille
  if(val == 0){
    motorY1.write(0);
    return;
  }
  int realVal = map(val, 1, 1000, 1185, 2000);
  motorY1.writeMicroseconds(realVal);
}
void setSpeedY2(int val){ // i promille
  if(val == 0){
    motorY2.write(0);
    return;
  }
  int realVal = map(val, 1, 1000, 1185, 2000);
  motorY2.writeMicroseconds(realVal);
}

void incrSpeed(int val){//@TODO
  
}

void decrSpeed(int val){

}

void setSpeedMotors(int val){
   motorX1.writeMicroseconds(val);
   motorX2.writeMicroseconds(val);
   motorY1.writeMicroseconds(val);
   motorY2.writeMicroseconds(val);
   
}

void rollLeft(){

}

void rollRight(){

}

void pitchForward(){

}

void pitchBackwards(){

}

void rotateRight(int angle){ 
  
}

void rotateLeft(int angle){

}
