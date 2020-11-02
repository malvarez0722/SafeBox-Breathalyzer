// -------------------------------------------------------------------
// File name:     BreathBox.c
// Description:   this starter code is for the Breathalyzer box. It receives 
//								data from the ESP8266.c and Locks or Closes the Box.
// Authors:       Emilio Cantu, Manolo Alvarez, Adrian, Ethan
// Converted to EE445L style Jonathan Valvano
// Date:          October 29, 2020
// Last update: October 29, 2020
//
// 
//
#ifndef _BREATHBOXH_
#define _BREATHBOXH_

#include <stdint.h>
#include <string.h>
#include "inc/tm4c123gh6pm.h"
#include "UART.h"
#include "ST7735.h"
#include "esp8266.h"

void BoxInit();
void LockBox();
void UnlockBox();


#endif