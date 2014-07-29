//NOTE: Will send data on the rf link when using hw serial instead of sofware serial
#ifdef DEBUG


void printDebugMessage(String s){
    Serial.println(s);
}
#endif



#ifndef DEBUG // dont do anything unless DEBUG is defined

void printDebugMessage(String s){
}

#endif
