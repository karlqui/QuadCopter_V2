char TempString[10];
void startMenu(){
  while(1){ 
    if(charAvail()){
      char c = readCharTimeout(timeout);
      
      if(c == 'E'){  //using '!' as terminating string symbol
        sendChar('E');
      }
      else if(c == 't'){
        if(testConnectionBMP()){
       
        updateTemperature();
         
        for(int i=0; i<10; i++)
          TempString[i] = '\0';
        
        dtostrf(temperature,1,1,TempString);
        Serial.print(TempString);
        sendChar('!');
        }
        else{
           Serial.print("OFFLINE!");
           
           
        }    
       }
       else if(c == 'a'){
           if(testConnectionBMP()){
          
          updateAltitude();
         
         for(int i=0; i<10; i++)
          TempString[i] = '\0';
        
        dtostrf(altitude_,1,1,TempString);
         Serial.println(TempString);
        sendChar('!');
        }
        else{
           Serial.print("OFFLINE!");
           
           
        }
       } 
       else if(c == 'd'){
         if(testConnectionHC()){
           for(int i=0; i<10; i++)
            TempString[i] = '\0';
          dtostrf(distance,2,0,TempString);
          Serial.println(TempString);
          sendChar('!');
        }
        else{
          Serial.print("OFFLINE!");
        }
       }
       else if(c == 'h') //return heading
       {
         if(testConnectionHMC()){
           updateHeading();
           updateHeading();
          for(int i=0; i<10; i++)
            TempString[i] = '\0';
          dtostrf(heading,1,1,TempString);
       
          Serial.print(TempString);
          sendChar('!');
         }
         else{
           Serial.print("OFFLINE!");
         }
       }
       else if(c == 'p') //return pitch
       {
         if(testConnectionMPU()){
           
          // handleInterrupt();
           //updateYawPitchRoll();

          for(int i=0; i<10; i++)
            TempString[i] = '\0';
          dtostrf(pitch,1,1,TempString);
       
          Serial.print(TempString);
          sendChar('!');
         }
         else{
           Serial.print("OFFLINE!");
         }
       }
       else if(c == 'r') //return pitch
       {
         if(testConnectionMPU()){
    //       handleInterrupt();
      //       updateYawPitchRoll();
          for(int i=0; i<10; i++)
            TempString[i] = '\0';
          dtostrf(roll,1,1,TempString);
       
          Serial.print(TempString);
          sendChar('!');
         }
         else{
           Serial.print("OFFLINE!");
         }
       }
       else if(c == 'x'){ // return calibrated x-value (x acc offset)
         sendChar('a');
         Serial.println(String(calibrateMPU_Pitch0()));
         sendChar('!');
       }
       else if(c == 'y'){ // return calibrated y-value (y acc offset)
         sendChar('a');
         Serial.println(String(calibrateMPU_Roll0()));
         sendChar('!');
       }
       else if(c == 'c'){
         sendChar('a');
         calibrateMotors();
       }
       else if(c == 's'){
         runCopter();
       }
    }
  }
}
