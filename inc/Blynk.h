//*****************  Blynk.h   ************************//
// Runs on TM4C123
// Uses ESP8266 Wi-Fi Module
// Manolo Alvarez
// November 5th, 2020
//*****************************************************//

// Hardware Configuration -------------------------------
// TM4C123       ESP8266-ESP01 (2 by 4 header)
// PE5 (U5TX) to Pin 1 (Rx)
// PE4 (U5RX) to Pin 5 (TX)
// PE3 output debugging
// PE2 nc
// PE1 output    Pin 7 Reset
// PE0 input     Pin 3 Rdy IO2
//               Pin 2 IO0, 10k pullup to 3.3V  
//               Pin 8 Vcc, 3.3V (separate supply from LaunchPad 
// Gnd           Pin 4 Gnd  
// Place a 4.7uF tantalum and 0.1 ceramic next to ESP8266 3.3V power pin
// Use LM2937-3.3 and two 4.7 uF capacitors to convert USB +5V to 3.3V for the ESP8266
// http://www.ti.com/lit/ds/symlink/lm2937-3.3.pdf

#ifndef BLYNK_H
#define BLYNK_H
#include <stdint.h>
#include <stdbool.h>

extern bool alcoholLimit;
extern uint32_t pin_num; 
extern uint32_t pin_int;
extern int pinFlag;
// -------------------------   TM4C_to_Blynk  -----------------------------------
// Send data to the Blynk App
// It uses Virtual Pin numbers between 70 and 99
// so that the ESP8266 knows to forward the data to the Blynk App
void TM4C_to_Blynk(uint32_t pin,uint32_t value);

// -------------------------   Blynk_to_TM4C  -----------------------------------
// This routine receives the Blynk Virtual Pin data via the ESP8266 and parses the
// data and feeds the commands to the TM4C.
void Blynk_to_TM4C(void);

void SendInformation(void);

#endif
