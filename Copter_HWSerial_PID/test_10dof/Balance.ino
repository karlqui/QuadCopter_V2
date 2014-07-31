
#include <PID_v1.h>

double SetpointP, InputP, OutputP;
double SetpointR, InputR, OutputR;
double SetpointY, InputY, OutputY;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=0.6;
double consKp=4, consKi=0.1, consKd=0.3;

PID YPID(&InputY, &OutputY, &SetpointY, consKp, consKi, consKd, DIRECT);

PID PPID(&InputP, &OutputP, &SetpointP, consKp, consKi, consKd, DIRECT);
PID RPID(&InputR, &OutputR, &SetpointR, consKp, consKi, consKd, DIRECT);


void setupPid(){
    PPID.SetMode(AUTOMATIC);
    PPID.SetOutputLimits(-300, 300);
    PPID.SetSampleTime(5); //200 hz
    
    RPID.SetMode(AUTOMATIC);
    RPID.SetOutputLimits(-300, 300);
    RPID.SetSampleTime(5); //200 hz
    
    YPID.SetMode(AUTOMATIC);
    YPID.SetOutputLimits(-200,200);
    YPID.SetSampleTime(5); //200 hz
    
}
void setConsParam(double Kp, double Ki, double Kd){
  consKp = Kp;
  consKi = Ki;
  consKd = Kd;

}
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int X1_Speed, X2_Speed, Y1_Speed, Y2_Speed = 0;

void balance(double y, double p, double r, double alt, double desiredY, double desiredP, double desiredR, double desiredAlt, int speed_Offset){ //try to stay at pitch roll and alt - spin indicates a desired yaw rotation, if zero -> stay at current yaw
  X1_Speed = 0;
  X2_Speed = 0;
  Y1_Speed = 0;
  Y2_Speed = 0;
  balanceYaw(y, desiredY);
  balancePitch(p, desiredP);
  balanceRoll(r, desiredR);

  X1_Speed += speed_Offset;
  X2_Speed += speed_Offset;
  Y1_Speed += speed_Offset;
  Y2_Speed += speed_Offset;
 // Serial.println(speed_Offset);
  setSpeedMotor(MOTOR_X1, X1_Speed);
  setSpeedMotor(MOTOR_X2, X2_Speed);
  setSpeedMotor(MOTOR_Y1, Y1_Speed);
  setSpeedMotor(MOTOR_Y2, Y2_Speed);

}

void balancePitch(double p, double desiredP){
   //ADJUST MOTORS IN PITCH-DIR
  InputP = p;
  SetpointP = desiredP;//desiredP;// (double)desiredP;
  
    //Serial.println(Input);
  double gap = abs(SetpointP-InputP); //distance away from setpoint
  if(gap<5)
  {  //we're close to setpoint, use conservative tuning parameters
    PPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     PPID.SetTunings(aggKp, aggKi, aggKd);
  }
  
  PPID.Compute();
  if(OutputP > 0){ 
    Y2_Speed += abs(OutputP);
    Y1_Speed -= abs(OutputP);
  }
  else if(OutputP < 0){
    Y1_Speed += abs(OutputP);
    Y2_Speed -= abs(OutputP);  
  }
}

void balanceRoll(double r, double desiredR){
      //ADJUST MOTORS IN ROLL-DIR
  InputR = r;
  SetpointR = desiredR;//desiredP;// (double)desiredP;
  
    //Serial.println(Input);
  double gap = abs(SetpointR-InputR); //distance away from setpoint
  if(gap<5)
  {  //we're close to setpoint, use conservative tuning parameters
     RPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     RPID.SetTunings(aggKp, aggKi, aggKd);
  }
  
  RPID.Compute();
  if(OutputR > 0){
    X2_Speed += abs(OutputR);
    X1_Speed -= abs(OutputR);  
  }
  else if(OutputR < 0){
    X1_Speed += abs(OutputR);
    X2_Speed -= abs(OutputR);
  }
}

void balanceYaw(double y, double desiredY){
  //YAW
  // X1 + X2 -> ökar YAW
  // Y1 + Y2 -> minskar YAW
  
  //räkna ut vilket håll ska snurra åt
  //skala abvståndet mallan yaw och desired i förhållande till  setpoint 0 så att PID inte blir förvirrad när magnometern passerar 360
  
   YPID.SetTunings(consKp, consKi, consKd);
   
  SetpointY = 0;
  if(desiredY < y){ //borde snurra vänster
    if(((360 - y) + desiredY) < (y - desiredY)){//om det är närmre via 360 -> alltså åt höger
      InputY = -(360 - y + desiredY); //negativ eftersom måste snurra höger
      YPID.Compute();
      X1_Speed += abs(OutputY);
      X2_Speed += abs(OutputY);
      Y1_Speed -= abs(OutputY);
      Y2_Speed -= abs(OutputY);
    }
    else{ //ska snurra vänster
      InputY = y - desiredY; //positiv eftersom måste snurra vänster
      YPID.Compute();
      Y1_Speed += abs(OutputY);
      Y2_Speed += abs(OutputY);
      X1_Speed -= abs(OutputY);
      X2_Speed -= abs(OutputY);
    }
  }
  else{ //borde snurra höger
    if((y + (360 - desiredY)) <  (desiredY - y))//om det är närmre via 360 -> snurra vänster
    {
      InputY = y + 360 - desiredY; //positiv eftersom vänster
      YPID.Compute();
      Y1_Speed += abs(OutputY);
      Y2_Speed += abs(OutputY);
      X1_Speed -= abs(OutputY);
      X2_Speed -= abs(OutputY);
      
    }
    else //ska snurra höger
    {
      InputY = -(desiredY - y); //negativ eftersom höger
      YPID.Compute();
      
      X1_Speed += abs(OutputY);
      X2_Speed += abs(OutputY);
      Y1_Speed -= abs(OutputY);
      Y2_Speed -= abs(OutputY);
    }
  }
}
