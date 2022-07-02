#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>  
#include "wifi.h"

boolean state;
int EXE_INTERVAL_1 = 1000;
unsigned long lastExecutedMillis_1 = 0;

int EXE_INTERVAL_2 = 1000;
unsigned long lastExecutedMillis_2 = 0;
int soil;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  connectWIFI();
  
  pinMode(A0, INPUT);
  //Serial.println();
  //printState();
}

void connectWIFI(){
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED && i < 15) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println('\n');
    Serial.println("TimeOut!");    
  }
  else{
    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());  
  }

  
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWIFI();  
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - lastExecutedMillis_1 >= EXE_INTERVAL_1) {
    lastExecutedMillis_1 = currentMillis; // save the last executed time
    //printState();
    Serial.println("------------POST-----------");
    soil = analogRead(A0);
    postData();
  }

  if (currentMillis - lastExecutedMillis_2 >= EXE_INTERVAL_2) {
    lastExecutedMillis_2 = currentMillis;
    Serial.println("------------GET-----------");
    getControl();
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

void postData(){
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
  HTTPClient http;    //Declare object of class HTTPClient

  http.begin("http://192.168.1.100:8081/handle");      //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

// Data to send with HTTP POST
  String httpRequestData = String("soil=" + String(soil));
 

  int httpCode = http.POST(httpRequestData);
  Serial.println(httpCode);
  if(httpCode != 200){
    Serial.println("Could not connect to the server");
    http.end();
    return;
  }
  
  String payload = http.getString();

  JSONVar response = JSON.parse(payload);
  
  if (JSON.typeof(response) == "undefined") {
    Serial.println("Parsing input failed!");
    http.end();
    return;
  }
  const char* StatusMessage = response["status"];
  Serial.println(String(StatusMessage));

  http.end();
 
  } 
  else {
 
    Serial.println("Error in WiFi connection");
 
  }
}

void getControl(){
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
  HTTPClient http;    //Declare object of class HTTPClient

  http.begin("http://192.168.1.100:8081/status");      //Specify request destination
 

  int httpResponseCode = http.GET(); 
  Serial.println(httpResponseCode);
  if(httpResponseCode != 200){
    Serial.println("Could not connect to the server");
    http.end();
    return;
  }
  
  String payload = http.getString();

  JSONVar response = JSON.parse(payload);
  
  if (JSON.typeof(response) == "undefined") {
    Serial.println("Parsing input failed!");
    http.end();
    return;
  }
  const char* Interval = response["interval"];

//  
//
  
  int n = int(response["interval"]);
//  String n = String(Interval);
  Serial.println(n);
  EXE_INTERVAL_1 = n;

  http.end();
 
  } 
  else {
 
    Serial.println("Error in WiFi connection");
 
  }
}
