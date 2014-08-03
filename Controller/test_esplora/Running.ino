int motorX1Speed, motorX2Speed, motorY1Speed, motorY2Speed = 0;
String sTemp = "";
char sBuff[10];

void runCopter(){
  flushRF();
  sendChar('s'); //start
  testMode3();
}

/*void testMode2(){
  EsploraTFT.background(0,0,0);
  EsploraTFT.text("SWITCH 1 -> MOTOR_X1++", 5,5);
  EsploraTFT.text("SWITCH 2 -> MOTOR_X2++", 5,15);
  EsploraTFT.text("SWITCH 3 -> MOTOR_Y1++", 5,25);
  EsploraTFT.text("SWITCH 4 -> MOTOR_Y2++", 5,35);
  
  EsploraTFT.text("MOTOR_X1: ", 5,50);
  EsploraTFT.text("MOTOR_X2", 5,65);
  EsploraTFT.text("MOTOR_Y1", 5,80);
  EsploraTFT.text("MOTOR_Y2", 5,95);
  EsploraTFT.stroke(0,255,0);
  
  sTemp = String(motorX1Speed);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.text(sBuff, 80, 50);
  
  sTemp = String(motorX2Speed);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.text(sBuff, 80, 65);
  
  sTemp = String(motorY1Speed);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.text(sBuff, 80, 80);
  
  sTemp = String(motorY2Speed);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.text(sBuff, 80, 95);
  while(1){
    int s1 = Esplora.readButton(SWITCH_1);
    int s2 = Esplora.readButton(SWITCH_2);
    int s3 = Esplora.readButton(SWITCH_3);
    int s4 = Esplora.readButton(SWITCH_4);
    
    if(s1 == LOW){
      motorX1Speed++;
      RFSerial.print("X1|" + String(motorX1Speed) + "!");
      sTemp = String(motorX1Speed);
      sTemp.toCharArray(sBuff, 10);
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(80, 50, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(sBuff, 80, 50);
    }
    else if(s2 == LOW){
      motorX2Speed++;
      RFSerial.print("X2|" + String(motorX2Speed) + "!");
      sTemp = String(motorX2Speed);
      sTemp.toCharArray(sBuff, 10);
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(80, 65, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(sBuff, 80, 65);
    }
    else if(s3 == LOW){
      motorY1Speed++;
      RFSerial.print("Y1|" + String(motorY1Speed) + "!");
      sTemp = String(motorY1Speed);
      sTemp.toCharArray(sBuff, 10);
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(80, 80, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(sBuff, 80, 80);
    }
    else if(s4 == LOW){
      motorY2Speed++;
      RFSerial.print("Y2|" + String(motorY2Speed) + "!");
      sTemp = String(motorY2Speed);
      sTemp.toCharArray(sBuff, 10);
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(80, 95, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(sBuff, 80, 95);
    }
    delay(50);
    
  }

}*/
void testMode3(){
  int motorOffset = 0;
  double kp, ki, kd = 0.0;
  bool isIncr = true;
  EsploraTFT.background(0,0,0);
  EsploraTFT.text("SWITCH_1 -> increase kp", 5,5);
  EsploraTFT.text("SWITCH_2 -> increase ki", 5,15);
  EsploraTFT.text("SWITCH_3 -> increase kd", 5,25);
  EsploraTFT.text("SWITCH_4 -> change incr/decr", 5,35);
  EsploraTFT.text("JOY_UP -> increase speed", 5,45);
  EsploraTFT.text("JOW_DOWN -> decrease speed", 5,55);
  
  EsploraTFT.text("Current speed:", 5,70);
  EsploraTFT.text("kp:", 5, 85);
  EsploraTFT.text("ki:", 5, 95);
  EsploraTFT.text("kd:", 5, 105);
    
 
  for(int i=0; i<10; i++)
    sBuff[i] = '\0';
 
  sTemp = String(motorOffset);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(sBuff, 90, 70);
  
  for(int i=0; i<10; i++)
    sBuff[i] = '\0';
  
  sTemp = String(kp);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(sBuff, 90, 85);
  
  for(int i=0; i<10; i++)
    sBuff[i] = '\0';
  
  sTemp = String(ki);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(sBuff, 90, 95);
  
  for(int i=0; i<10; i++)
    sBuff[i] = '\0';
  
  sTemp = String(kd);
  sTemp.toCharArray(sBuff, 10);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(sBuff, 90, 105);
  
  while(1){
    if(Esplora.readButton(SWITCH_1) == LOW){
      if(isIncr)
        kp+=0.01;
      else
        kp-=0.01;
        
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(90, 60, 100, 10);
      EsploraTFT.stroke(0,255,0);
    }
    else if(Esplora.readButton(SWITCH_2) == LOW){
      if(isIncr)
        ki+=0.01;
      else
        kp-=0.01;
    }
    else if(Esplora.readButton(SWITCH_3) == LOW){
      if(isIncr)
        kd+=0.01;
      else
        kd-=0.01;
      
    }
    else if(Esplora.readButton(SWITCH_4) == LOW){
      isIncr = !isIncr;
    }
    else if(Esplora.readButton(JOYSTICK_UP) == LOW){
      motorOffset++;
      if(motorOffset > 1000)
        motorOffset = 1000;
      RFSerial.flush();
      RFSerial.print("sp:");
      RFSerial.write(highByte(motorOffset));
      RFSerial.write(lowByte(motorOffset));
      RFSerial.print("!");
      
      sTemp = String(motorOffset);
      sTemp.toCharArray(sBuff, 10);
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(90, 60, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(sBuff, 90, 70);
      delay(50);
    }
    else if(Esplora.readButton(JOYSTICK_DOWN) == LOW){
      motorOffset--;
      if(motorOffset < 0)
        motorOffset = 0;
      
      for(int i=0; i<10; i++)
        sBuff[i] = '\0';  
      
      RFSerial.flush();
      RFSerial.print("sp:");
      RFSerial.write(highByte(motorOffset));
      RFSerial.write(lowByte(motorOffset));
      RFSerial.print("!");
      sTemp = String(motorOffset);
      sTemp.toCharArray(sBuff, 10);
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(90, 60, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(sBuff, 90, 70);
      delay(50);
    }
  }
}
