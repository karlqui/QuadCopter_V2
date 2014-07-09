
 

 
 void setupRFSerial(){
    Serial.begin(9600);
 }
 
 bool charAvail(){
   return Serial.available();
 }
  void flushRF(){
   while(charAvail())
     readCharRF();
 }
 void sendChar(char c){
   Serial.print(c);
 }

 char readCharRF(){
   return Serial.read();
  
 }
 
 char readCharTimeout(int timeout){
   int time = 0;
   while(time < timeout){
     if(charAvail()){
       return readCharRF();
     }
     time++;
     delay(1);
   }
   return -1;
 }
 
void readStringRF(char (&readS)[20],int timeOutDelay){
    int time = 0, i = 0;

    while(1){
      
      if(charAvail()){
        char c = readCharRF();
        readS[i] = c;
        
        if(c == '!'){
          readS[i] = '\0';
          return;
          
          }
        i++;
      }
      time++;
      
      if(time >= timeOutDelay){
         readS[0] = 'E';
         readS[1] = 'R';
         readS[2] = 'R';
         readS[3] = 'O';
         readS[4] = 'R';
         
         return;
       }
      
      delay(1);
    }
    
    
    
 }
