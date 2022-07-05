#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>  
#include "wifi.h"
//#include <ESP_EEPROM.h>

boolean state;
int EXE_INTERVAL_1 = 1000;
unsigned long lastExecutedMillis_1 = 0;

int EXE_INTERVAL_2 = 1000;
unsigned long lastExecutedMillis_2 = 0;
int soil;
int deviceID = 1;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  connectWIFI();
//
//  while(!Serial);
//  EEPROM.begin(16); // looks like 16 bytes is the minimum
//  EEPROM.put(0, 1234); // first parameter sets the position in the buffer, second the value
//  boolean res = EEPROM.commit();
//  Serial.println(res); // should print 1 (true) if commit worked as expected
//  int myVar;
//  EEPROM.get(0, myVar);
//  Serial.println(myVar);
  
  pinMode(A0, INPUT);
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
    soil = analogRead(A0);
    postData();
  }

  if (currentMillis - lastExecutedMillis_2 >= EXE_INTERVAL_2) {
    lastExecutedMillis_2 = currentMillis;
    getControl();
  }
}


void postData(){
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
  HTTPClient http;    //Declare object of class HTTPClient

  http.begin("http://192.168.1.100:8081/handle");      //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

// Data to send with HTTP POST


  String httpRequestData = String("soil=" + String(soil) + "&deviceID=" + String(deviceID));
 

  int httpCode = http.POST(httpRequestData);
  //Serial.println(httpCode);
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

  http.begin("http://192.168.1.100:8081/status?deviceID=1");      //Specify request destination
 

  int httpResponseCode = http.GET(); 
  //Serial.println(httpResponseCode);
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

  int n = int(response["interval"]);
  EXE_INTERVAL_1 = n;

  http.end();
 
  } 
  else {
 
    Serial.println("Error in WiFi connection");
 
  }
}
