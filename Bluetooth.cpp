/************************************************
 Written by Cruz Monrreal II
 Created on 06-26-2012
 Modified on 11-11-2012
 
 Updates can be found here:
  https://github.com/cmonr/Arduino-Bluetooth-Library
************************************************/

#include <stdint.h>
#include <Arduino.h>
#include <Bluetooth.h>

Bluetooth::Bluetooth(){
    Serial.begin(115200);
}

Bluetooth::~Bluetooth(){}

char Bluetooth::beginCMD(){
  Serial.print("$$$");
  
  return readUntilLine() == "CMD";
}
void Bluetooth::endCMD(){
  Serial.println("---");
  
  readUntilStr("END", 5000);
}

void Bluetooth::connect(){
  do{
    Serial.println("C");
  } while(readUntilStr("failed", 10000).indexOf("failed") != -1);
}

char Bluetooth::connectToAddr(String addr){
  
}

char Bluetooth::isConnected(){
  Serial.println("GK");
  
  return readUntilDelay(1000) != "0";
}

String Bluetooth::readUntilStr(String str, unsigned long timeout){
  String resp = "";
  char c = 0;
  
  start = millis();
  Serial.flush();
  while (resp.indexOf(str) == -1 && start + timeout > millis()){
    while(Serial.available()){
      c = char(Serial.read());
      
      resp.concat(c);
    }
  }
  
  return resp;
}

String Bluetooth::readUntilLine(){
  String resp = "";
  char c = 0;
  
  while (c != '\n'){
    while(Serial.available()){
      c = char(Serial.read());
      
      resp.concat(c);
    }
  }
  
  return resp;
}

String Bluetooth::readUntilDelay(unsigned long delay){
  String resp = "";
  
  start = millis();
  Serial.flush();
  while(start + delay > millis()){
    while(Serial.available())
      resp.concat(char(Serial.read()));
  }
  
  return resp;
}
