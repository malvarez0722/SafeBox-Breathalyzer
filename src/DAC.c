// DAC.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: Manolo Alvarez
// Date Created: 11/29/2018 
// Last Modified: 11/29/2018
// Hardware connections:
// 

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/DAC.h"

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_RCGCGPIO_R&0x02)==0);
	GPIO_PORTB_AMSEL_R &= ~0x3F;	// no analog
	GPIO_PORTB_PCTL_R &= ~0x00000FFF;	// regular function
	GPIO_PORTB_DIR_R |= 0x3F;
	GPIO_PORTB_AFSEL_R &= ~0x3F;
	GPIO_PORTB_DEN_R |= 0x3F;
	
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R = data& 0x3F;
}

