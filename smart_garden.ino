boolean state;
int period = 1000;
#define EXE_INTERVAL_1 1000
unsigned long lastExecutedMillis_1 = 0;
#include <ESP8266WiFi.h>  
#include "wifi.h"

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  
  pinMode(A0, INPUT);
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
