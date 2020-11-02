// DAC.h
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: Manolo Alvarez
// Date Created: 11/29/2018
// Last Modified: 11/29/2018
// Hardware connections
// 

#ifndef DAC_H
#define DAC_H
#include <stdint.h>

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void);


// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data);

#endif
