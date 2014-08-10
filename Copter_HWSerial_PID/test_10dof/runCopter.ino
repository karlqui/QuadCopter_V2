//running quadcopter
#include "Kalman.h"
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

union double_type { //union to convert from byte array to double
    byte b[4];
    double dval;
} u;

char RFString[20];
double kp, ki, kd;
double kalAngleX, kalAngleY, kalAngleZ = 0; // Calculated angle using a Kalman filter

int speedOffset;

Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;
Kalman kalmanZ;

double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
uint32_t timer;

unsigned long previousMillis, previousMillisRF = 0; 
const long interval = 5;  //200 hz
const long RF_Interval = 100; //read RF communication at 10 HZ

double baseHeading = 0;

void testMode3(){ //also test balancing algorithm
  
  accX = mpu.getAccelerationX();
  accY = mpu.getAccelerationY();
  accZ = mpu.getAccelerationZ();
  gyroX = mpu.getRotationX();
  gyroY = mpu.getRotationY();
  gyroZ = mpu.getRotationZ();
  roll  = atan2(accY, accZ) * RAD_TO_DEG;
  pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
  updateHeading();
  kalmanX.setAngle(roll); // Set starting angle
  kalmanY.setAngle(pitch);
  kalmanZ.setAngle(heading);
  baseHeading = heading;
  timer = micros();
  unsigned long currentMillis = millis();
  unsigned long currentMillisRF = millis();
  while(1){
    
    currentMillis = millis();
    
    if(currentMillis - previousMillis >= interval) {
    
      previousMillis = currentMillis;
       
      accX = mpu.getAccelerationX();
      accY = mpu.getAccelerationY();
      accZ = mpu.getAccelerationZ();
      gyroX = mpu.getRotationX();
      gyroY = mpu.getRotationY();
      gyroZ = mpu.getRotationZ();
      
      double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
      timer = micros();
      
      roll  = atan2(accY, accZ) * RAD_TO_DEG;
      pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
      
      double gyroXrate = gyroX / 131.0; //from radians to degrees
      double gyroYrate = gyroY / 131.0; 
      double gyroZrate = gyroZ / 131.0;
      
      if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
      kalmanX.setAngle(roll);
      kalAngleX = roll;
      } 
      else
        kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
    
      if (abs(kalAngleX) > 90)
        gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
        
      kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
     
      updateHeading();
      kalAngleZ = kalmanZ.getAngle(heading, -gyroZrate, dt);
      
      balance(kalAngleZ, kalAngleX, kalAngleY, 0, baseHeading, 0, 0, 0, speedOffset);
    }
    
    //read string from sender
    currentMillisRF = millis();
    if(currentMillis - previousMillisRF >= RF_Interval){ //checkRF
      previousMillisRF = currentMillis;
      
      if(charAvail()){
       
        for(int i=0; i < 20; i++)
          RFString[i] = '\0';
          
        readStringRF(RFString, timeout);
        //parse string -> the command
        int i = 0;
        String command = "";
        while(RFString[i] != ':'){//check what to do
          command += RFString[i];
          i++;
        }
        i++;
        //next is data
        byte data[10]; //buffer to hold the data
        
        if(command == "sp"){ //speed
          for(int j = 0; j < sizeof(int); j++){
            data[j] = RFString[i];
            i++;
          }
          speedOffset = word(data[0], data[1]);
          
        }
        
        else if(command == "kp"){ //kalman process variable
          for(int j = 0; j < sizeof(double); j++){
            data[j] = RFString[i];
             u.b[j] = data[j];
            i++;
          }
          if(abs(kp - u.dval) <0.20 || kp == 0) //fail safe
            kp = u.dval;
        }
        
        else if(command == "ki"){ //kalman integral variable
          for(int j = 0; j < sizeof(double); j++){
            data[j] = RFString[i];
             u.b[j] = data[j];
            i++;
          }
          if(abs(ki - u.dval) <0.20 || ki == 0)//fail safe
            ki = u.dval;
        }
        
        else if(command == "kd"){ //kalman derivative variable
          for(int j = 0; j < sizeof(double); j++){
            data[j] = RFString[i];
             u.b[j] = data[j];
            i++;
          }
          if(abs(kd - u.dval) <0.20 || kd == 0)//fail safe
            kd = u.dval;
        }
        setConsParam(kp, ki, kd); //update PID param
     
        flushRF();
      }
      
    }
  }
}
