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


#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "UART.h"
#include "ST7735.h"
#include "esp8266.h"

bool close = false;		//normal mode

//------------BoxInit------------
// Initialize Box features ---> Switches and GPIO's
// Input: none
// Output: none
void BoxInit(){
	
}
//------------LockBox------------
// Send a signal to PB6 and close the box. Set close = true.
// Input: none
// Output: none
void LockBox(){
	close = true;
}
//------------UnlockBox------------
// Send a signal to PB6 and close the box
// Input: none
// Output: none
void UnlockBox(){
	close = false;
}
