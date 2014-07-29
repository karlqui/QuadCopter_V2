



MPU6050 mpu;

  float yaw = 0;
float pitch = 0;
float roll = 0;

bool MPUIsInit = false; 
// MPU control/status vars

double calibrationThreshold = 0.1;
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements

VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

bool testConnectionMPU(){
  return mpu.testConnection();
}

int calibrateMPU_Pitch0(){//calibra 0 value on accelerometer
  bool success = false;
   //5 consecutive samples must be betweed 0.05 and -0.05
   while(!success){ //try for 16000 ms
   success = true;
   for(int i=0; i<8;i++){ //8 consecutive samples must be within the threshhold value -- 8*50 ms = 400 ms
   // while(checkInterrupt());
   // handleInterrupt();
    //updateYawPitchRoll();
    if(pitch<-0.01)
      mpu.setXAccelOffset(mpu.getXAccelOffset() + 1);
    else if(pitch>0.01)
      mpu.setXAccelOffset(mpu.getXAccelOffset() - 1);
    
    if(pitch>calibrationThreshold || pitch < -calibrationThreshold)
      success = false;
    delay(50);
   }
  
#ifdef PRINT_CAL_PITCH
  Serial.println(pitch);
  Serial.println(success);
#endif
  }
  return mpu.getXAccelOffset();
}

int calibrateMPU_Roll0(){
  bool success = false;
   //5 consecutive samples must be betweed 0.05 and -0.05
   while(!success){
   success = true;
   for(int i=0; i<8;i++){ //8 consecutive samples must be within the threshhold value
   // while(checkInterrupt());
   // handleInterrupt();
    //updateYawPitchRoll();
      if(roll<-0.01)
    mpu.setYAccelOffset(mpu.getYAccelOffset() + 1);
  else if(roll>0.01)
    mpu.setYAccelOffset(mpu.getYAccelOffset() - 1);
    
    if(roll>calibrationThreshold || roll < -calibrationThreshold)
      success = false;

    delay(50);
    }
#ifdef PRINT_CAL_ROLL
Serial.println(roll);
Serial.println(success);
#endif
   }
   return mpu.getYAccelOffset();
}

void setupMPU6050(){
    mpu.initialize();
    
    MPUIsInit = mpu.testConnection();
    printDebugMessage(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
 
    mpu.setXGyroOffset(220); //@TODO CHANGE GYRO OFFSET VALUES
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    
    mpu.setZAccelOffset(500); // 1688 factory default for my test chip
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    mpu.setFullScaleAccelRange(0);
    mpu.setRate(7);
    mpu.setFSyncInterruptEnabled(false);
    mpu.setDLPFMode(MPU6050_DLPF_BW_256);
    // make sure it worked (returns 0 if so)
    mpu.setI2CBypassEnabled(true);
}


void mpuBypass(bool b){
  mpu.setI2CBypassEnabled(b);
}








