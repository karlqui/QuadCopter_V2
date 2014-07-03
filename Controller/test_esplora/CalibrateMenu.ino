int currentSpeed = 1000; //current speed of motors
int stepVar = 1; //increase by stepVar
String buff = "";
char charBuff[10];
void setupCalibrateMenu(){
  sendChar('c');
  char c = readCharTimeout(timeout);
  if(c == 'a') //acknowledge
  {
    EsploraTFT.background(0,0,0); //clear screen
    createButton(EsploraTFT.width() - 50, EsploraTFT.height() - 30, 40, 20, "Back", 1, 0);
    EsploraTFT.textSize(1);
    EsploraTFT.text("JOY_UP -> speed += step", 5, 5);
    EsploraTFT.text("JOY_DOWN -> speed -= step", 5, 20);
    EsploraTFT.text("JOY_RIGHT -> step++", 5, 35);
    EsploraTFT.text("JOY_LEFT -> step--", 5, 50);
    EsploraTFT.text("Current speed: ", 5, 75);
    EsploraTFT.text("Current step: ", 5, 90);
    paintSpeed();
    paintStep();
  }
  else{
    EsploraTFT.background(0,0,0);
    EsploraTFT.stroke(255,0,0);
    EsploraTFT.textSize(1.6);
    EsploraTFT.text("COMMUNICATION DOWN!", 15, 50);
    createButton(EsploraTFT.width() - 50, EsploraTFT.height() - 30, 40, 20, "Back", 1, 0);
    EsploraTFT.textSize(1);
    EsploraTFT.stroke(255,255,255);
  }

}

void paintSpeed(){
  buff = "";
  buff = String(currentSpeed);
  buff.toCharArray(charBuff, 10);
  EsploraTFT.fill(0,0,0);
  EsploraTFT.stroke(0,0,0);
  EsploraTFT.rect(90,75, 30, 12);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(charBuff, 90, 75);
  EsploraTFT.stroke(255,255,255);
  for(int i=0;i<10;i++){
    charBuff[i] = '\0';
  }
}

void paintStep(){
  buff = "";
  buff = String(stepVar);
  buff.toCharArray(charBuff, 10);
  EsploraTFT.fill(0,0,0);
  EsploraTFT.stroke(0,0,0);
  EsploraTFT.rect(85,90, 25, 12);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(charBuff, 85, 90);
  EsploraTFT.stroke(255,255,255);
  for(int i=0;i<10;i++){
    charBuff[i] = '\0';
  }
}
  

void updateVars(int button){
  switch(button){
    case JOYSTICK_DOWN:
      if(currentSpeed - stepVar > 0)
        currentSpeed-=stepVar;
        RFSerial.println(String(currentSpeed));
        sendChar('!');
      paintSpeed();
      delay(10);
    break;
    case JOYSTICK_LEFT: 
      if(stepVar>0)
        stepVar--;
      paintStep();
    break;
    case JOYSTICK_UP: 
      currentSpeed+=stepVar;
      RFSerial.println(String(currentSpeed));
      sendChar('!');
      paintSpeed();
      delay(10);
    break;
    case JOYSTICK_RIGHT: 
      stepVar++;
      paintStep();
    break;
    default:
    break;
  }
}

void checkCalibrateMenu(){
  int yButton = Esplora.readJoystickSwitch();
  if(Esplora.readButton(JOYSTICK_DOWN) == LOW){
    updateVars(JOYSTICK_DOWN);
  }
  if(Esplora.readButton(JOYSTICK_LEFT) == LOW){
    updateVars(JOYSTICK_LEFT);
  }
  if(Esplora.readButton(JOYSTICK_UP) == LOW){
    updateVars(JOYSTICK_UP);
  }
  if(Esplora.readButton(JOYSTICK_RIGHT) == LOW){
    updateVars(JOYSTICK_RIGHT);
  }

  
  
  
  if(yButton == LOW){
    RFSerial.println("BACK!");
    setCurrentMenu(0);
    setupStartMenu();
  }
}
