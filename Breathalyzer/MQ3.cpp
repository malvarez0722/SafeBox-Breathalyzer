#include <stdio.h>
#include <string.h>
#include "UI.h"
#include "MQ3.h"
#include <Arduino.h>

void MQ3setup(){
  
}

int getMQ3(){
  return analogRead(A0);
  
}
