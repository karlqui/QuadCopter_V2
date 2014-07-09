void runCopter(){
  flushRF();
  sendChar('s'); //start
  EsploraTFT.background(0,0,0);
  while(1);
}
