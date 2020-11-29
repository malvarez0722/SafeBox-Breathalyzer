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
#ifndef _LATCHH_
#define _LATCHH_

//------------LatchInit------------
// Initialize PWM0
// Input: none
// Output: none
void LatchInit(void);

//------------Close Latch------------
// Close Latch
// Input: none
// Output: none
void CloseLatch(void);

//------------OpenLatch------------
// Open Latch
// Input: none
// Output: none
void OpenLatch(void);


#endif
