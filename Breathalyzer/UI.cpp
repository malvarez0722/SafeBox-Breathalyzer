
#include <stdio.h>
#include <string.h>
#include "UI.h"
#include <Arduino.h>

const uint8_t button = D8;
const uint8_t LED1 = D2;
int LEDstate = 0;

void UI_interruptSetup(){
  pinMode(button, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1,LOW);
  attachInterrupt(digitalPinToInterrupt(button),ButtonISR,CHANGE);
}

ICACHE_RAM_ATTR void ButtonISR(){
  Serial.println("ISR");
  if(!LEDstate){
    LEDstate = 1;
    digitalWrite(LED1,HIGH);
  }
  else{
    LEDstate = 0;
    digitalWrite(LED1,LOW);
  }
}

void SetLED(int num){
  
}
