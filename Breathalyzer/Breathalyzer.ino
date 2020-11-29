#include "UI.h"
#include "WIFI.h"
#include "MQ3.h"
#include <stdio.h>
#include <string.h>

WIFI myWifi;
const int analogInPin = A0;

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  myWifi.SetupWIFI();
  UI_interruptSetup();
}

int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int n5 = 0;
int avg = 0;

int count = 0;

void loop() {
  // put your main code here, to run repeatedly:
  /*if(digitalRead(D1)){
    Serial.print("pressed");
    digitalWrite(D2,HIGH);
  }
  else digitalWrite(D2,LOW);  */
  //Serial.println(getMQ3());


  count++;
  // read the analog in value
  n5=n4; n4=n3; n3=n2; n2=n1;
  n1 = analogRead(analogInPin);
  avg = (n1+n2+n3+n4+n5)/5;

  if(count > 5){
      myWifi.BlynkWrite(avg);
  }
  delay(50);
}
