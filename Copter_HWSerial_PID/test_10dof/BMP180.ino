#include <SFE_BMP180.h>

SFE_BMP180 pressure;
double baseline;


bool BMPIsInit = false;
void setupBMP180() {
    BMPIsInit = pressure.begin();
    printDebugMessage(BMPIsInit ? "BMP085 connection successful" : "BMP085 connection failed");
    baseline = getPressure();
}
void updateTemperature(){
    double T;
 
    pressure.getTemperature(T);
    temperature =T;
}
bool testConnectionBMP(){
  return BMPIsInit;
}

double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
      }
    }
  }
}


void updateAltitude() {
      double a,P;
  
  // Get a new pressure reading:

  P = getPressure();

  // Show the relative altitude difference between
  // the new reading and the baseline reading:

    altitude_ = pressure.altitude(P,baseline);
    
#ifdef PRINT_ALTITUDE
    Serial.print("Altitude:  ");
    Serial.println(altitude_);
#endif
    
}
