int timeout = 2000;
char readS[20];
#include "Esplora.h"  
#include "TFT.h"
#include "SPI.h"
#include <SoftwareSerial.h>
SoftwareSerial RFSerial(11, 3);
//#DEFINE DEBUG
//#DEFINE PRINT_RF



char curString[20];
void setup() {
  // put your setup code here, to run once:
    EsploraTFT.begin();
    EsploraTFT.background(0,0,0);
    Serial.begin(9600);
    setupRFSerial();
  
  
  setupStartMenu();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  
}
