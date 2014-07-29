#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#define MOTOR_X1 0
#define MOTOR_X2 1
#define MOTOR_Y1 2
#define MOTOR_Y2 3



int timeout = 3000;
double heading = 0;
double altitude_ = 0;
double temperature = 0;
long distance = -1;

int liftOffSpeed = 0;
// is used in I2Cdev.htimeout
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//#define DEBUG
//#define PRINT_HEADING
//#define PRINT_ALTITUDE
//#define PRINT_YAW
//#define PRINT_PITCH
//#define PRINT_ROLL
//#define PRINT_WORLDACCEL
//#define PRINT_RF
//#define PRINT_DISTANCE
//#define PRINT_LIFTOFFSPEED
//#define PRINT_CAL_PITCH
//#define PRINT_CAL_ROLL
void readStringRF(char (&inString)[20], int timeOutDelay);

void setup() {

    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

  printDebugMessage("Initializing I2C devices...");
  printDebugMessage("Testing device connections...");
   
  setupPid(); 
  setupBMP180();
  setupHMC5883L();
  setupHC_SR04();
  setupRFSerial();
  setupMPU6050();
  mpuBypass(true);
  runCopter();
  startMenu(); //while the esplora user is still in the start menu -- before 
}



void loop() {
    
}

