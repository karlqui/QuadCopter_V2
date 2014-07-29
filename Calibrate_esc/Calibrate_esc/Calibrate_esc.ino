#include <Servo.h>
#define MOTOR_X1 0
#define MOTOR_X2 1
#define MOTOR_Y1 2
#define MOTOR_Y2 3
Servo motorX1, motorX2, motorY1, motorY2;
int X1Speed, X2Speed, Y1Speed, Y2Speed = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motorX1.attach(10); //X positive angle	
  motorY1.attach(9); //Y positive angle
  motorX2.attach(6); //X negative angle
  motorY2.attach(11); //Y negative angle
  Serial.println("X1 X2 Y1 Y2");
}

void setSpeedMotor(int motor, int val){ // 0 = x1, 1=x2 , 2= y1, 3 = y2
  int realVal = 0;
  if(val > 0)
    realVal = map(val, 1, 1000, 1190, 2000);
    
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

void loop() {
  // put your main code here, to run repeatedly:
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
        
     motorX1.writeMicroseconds(x1);
     motorX2.writeMicroseconds(x2);
     motorY1.writeMicroseconds(y1);
     motorY2.writeMicroseconds(y2);

   
  }
}
