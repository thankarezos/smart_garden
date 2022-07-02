boolean state;
int period = 1000;
#define EXE_INTERVAL_1 1000
unsigned long lastExecutedMillis_1 = 0;
void setup() {
  
  pinMode(A0, INPUT);
  Serial.begin(115200);
  Serial.println();
  printState();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastExecutedMillis_1 >= EXE_INTERVAL_1) {
    lastExecutedMillis_1 = currentMillis; // save the last executed time
    printState();
    Serial.println();
  }
}

void printState(){
  if(analogRead(A0) < 700){
    state = true;
    Serial.println("wet");   
  }
  else{
    state = false;
    Serial.println("dry");  
  }
}
