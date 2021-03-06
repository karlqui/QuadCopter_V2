int DIST_TRIG = 4;
int DIST_ECHO = 3;
int maximumRange = 1500; // Maximum range needed
int minimumRange = 40; // Minimum range needed
long duration; // Duration used to calculate distance

void setupHC_SR04(){
   pinMode(DIST_TRIG, OUTPUT);
   pinMode(DIST_ECHO, INPUT);
}

void setMaximumRange(int range){
  maximumRange = range;
}

int getMaximumRange(){
  return maximumRange;
}
bool testConnectionHC(){
  updateDistance();
  return distance != -1;
}

void updateDistance(){
  double tempDist;
 digitalWrite(DIST_TRIG, LOW); 
 delayMicroseconds(2); 

 digitalWrite(DIST_TRIG, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(DIST_TRIG, LOW);
 duration = pulseIn(DIST_ECHO, HIGH, 10000);

 tempDist = duration/5.82; //distance in millimeters

 if (tempDist >= maximumRange|| tempDist == 0){
   
   distance = maximumRange;
 
 }
 else if(tempDist <= minimumRange){
   distance = minimumRange;
 }
 else {

  distance = tempDist;

 }
 #ifdef PRINT_DISTANCE
  Serial.print("Distance:  ");
  Serial.println(distance);
#endif
}

