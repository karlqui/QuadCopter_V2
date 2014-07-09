int scrollOffset = 0;
char* texts[19];
int nrOfStrings;
char calRBuff[30];
char calPBuff[30];
char calLBuff[30];
void startCopter(){
  printInfoText();

  delay(100);
  while(1){
    checkAction();
  }
}

void checkAction(){
  int yD = Esplora.readButton(JOYSTICK_DOWN);
  int yU = Esplora.readButton(JOYSTICK_UP);
  int s1 = Esplora.readButton(SWITCH_1);
  int s3 = Esplora.readButton(SWITCH_3);
  if(yU ==LOW)
    scroll(true);
  else if(yD == LOW)
    scroll(false);
  else if(s1 == LOW)
    runCopter();
  else if(s3 == LOW)
    setupStartMenu();
}

void printInfoText(){
   EsploraTFT.background(0,0,0);
   paintInfo_2("Starting Quadcopter...", 0);
   paintInfo_2("--------------------------", 1);
   paintInfo_2("Loading calibrated values", 2);
   paintInfo_2("from EEPROM...", 3);
   
   int calP = readEEPROM("CALPITCH");
   int calR = readEEPROM("CALROLL");
   int calLiftOff = readEEPROM("LIFTOFF");
   
   
   String temp = "Pitch offset: " + String(calP);
   for(int i=0; i<30; i++)
    calPBuff[i] = '\0';
   temp.toCharArray(calPBuff, 30);
   paintInfo_2(calPBuff, 4);
   
   temp = "Roll offset: " + String(calR);
  for(int i=0; i<30; i++)
    calRBuff[i] = '\0';
   temp.toCharArray(calRBuff, 30);
   paintInfo_2(calRBuff, 5);
   
   temp = "Lift-off speed: " + String(calLiftOff);
   for(int i=0; i<30; i++)
    calLBuff[i] = '\0';
   temp.toCharArray(calLBuff, 30);
   paintInfo_2(calLBuff, 6);
   
   paintInfo_2("--------------------------", 7);
   paintInfo_2("Testing communication...", 8);
   paintInfo_2("Communication delay:", 9);
   paintInfo_2("--------------------------", 10);
   paintInfo_2("Testing sensors...", 11);
   paintInfo_2("Sensor status:", 12);
   paintInfo_2("--------------------------", 13);
   paintInfo_2("Setting altitude offset..", 14);
   paintInfo_2("Current altitude(offset): ", 15);
   paintInfo_2("-------------------------", 16);
   paintInfo_2("SWITCH 1 -> CONTINUE", 17);
   paintInfo_2("SWITCH 3 -> START MENU", 18);
   nrOfStrings = 19;
}

void scroll(bool up){
  EsploraTFT.background(0,0,0);
  if(up)
    scrollOffset+=5;
  else
    scrollOffset-=5;
    
  for(int i=0; i <nrOfStrings; i++){
    if(5 + i*10 + scrollOffset > 0 && 5 + i*10 + scrollOffset < EsploraTFT.height())
      paintInfoString(i, 5 + i*10 + scrollOffset);
  }
}


void paintInfo_2(char * text, int index){
  texts[index] = text;
  if(index > 5){ //need to scroll
    EsploraTFT.background(0,0,0);
    for(int i=0; i <=index; i++){
      scrollOffset = - ( index - 5 ) * 10;
      if(5 + i*10 + scrollOffset > 0)
        paintInfoString(i, 5 + i*10 + scrollOffset);
    }
  }
  else{
    paintInfoString(index, 5 + index*10);
  }
}

void paintInfoString(int index, int y){
  EsploraTFT.text(texts[index], 5, y);
}
