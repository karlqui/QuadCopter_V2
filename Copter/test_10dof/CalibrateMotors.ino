char readS[20] = "";
void calibrateMotors(){
  setupMotors();
  while(1){
    if(charAvail()){
      for(int i = 0; i<20; i++)
        readS[i] = '\0';
      readStringRF(readS, timeout);
      if(String(readS) == "BACK"){
        Serial.println("back");
        break;
      }
      liftOffSpeed = String(readS).toInt();
#ifdef PRINT_LIFTOFFSPEED
  Serial.println("Lift-off speed: " + String(liftOffSpeed));
#endif
    }
  }
  Serial.println("launching startmenu");
  startMenu();
}
