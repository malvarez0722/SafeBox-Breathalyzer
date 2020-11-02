// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 11/6/2018
// Edited by: Manolo Alvarez
// Last modification date: 12/1/2018


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ADC.h"

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){
   volatile uint32_t delay;    
   SYSCTL_RCGCGPIO_R|=0x08;   //activate clock for port D
   delay = SYSCTL_RCGCGPIO_R; //wait for clock to stabilize
   GPIO_PORTD_DIR_R&= ~0x06;  //PD2 & PD1 is set as an input
   GPIO_PORTD_AFSEL_R|=0x06;  //enable alternate function on PD2 & PD1
   GPIO_PORTD_DEN_R&= ~0x06;  //disable digital IO on PD2 & PD1
   GPIO_PORTD_AMSEL_R|=0x06;  //activate analog function on PD2 & PD1
  
  
   // ADC1 PD1 Channel 6
   SYSCTL_RCGCADC_R|=0x02;      //activate ADC1 clock
   delay = SYSCTL_RCGCADC_R;    //wait for clock to stabilize
   delay = SYSCTL_RCGCADC_R;
   delay = SYSCTL_RCGCADC_R;
   delay = SYSCTL_RCGCADC_R;
   ADC1_PC_R=0x01;              //max sample rate of 125k/second
   ADC1_SSPRI_R=0x0123;         //set sequencer priority
   ADC1_ACTSS_R&= ~0x0008;      //need to disable sample sequencer before configuring it
   ADC1_EMUX_R&= ~0xF000;       //NOT NEEDED?? ADC will be triggered by software start
   ADC1_SSMUX3_R&= 0xFFFFFFF0;  
   ADC1_SSMUX3_R+=6;            //set channel 6
   ADC1_SSCTL3_R=0x0006;        //specifies that ADC will measure voltage, use busy-wait
   ADC1_IM_R&= ~0x0008;         //disable sequencer interrupts
   ADC1_ACTSS_R|=0x0008;        //enable sample sequencer 


   // ADC0 PD2 Channel 5
   SYSCTL_RCGCADC_R|=0x01;      //activate ADC0 clock
   delay = SYSCTL_RCGCADC_R;    //wait for clock to stabilize
   delay = SYSCTL_RCGCADC_R;    //wait for clock to stabilize
   delay = SYSCTL_RCGCADC_R;
   delay = SYSCTL_RCGCADC_R;
   ADC0_PC_R=0x01;              //max sample rate of 125k/second
   ADC0_SSPRI_R=0x0123;         //set sequencer priority
   ADC0_ACTSS_R&= ~0x0008;      //need to disable sample sequencer before configuring it
   ADC0_EMUX_R&= ~0xF000;       //NOT NEEDED?? ADC will be triggered by software start
   ADC0_SSMUX3_R&= 0xFFFFFFF0;  
   ADC0_SSMUX3_R+=5;            //set channel 5
   ADC0_SSCTL3_R=0x0006;        //specifies that ADC will measure voltage, use busy-wait
   ADC0_IM_R&= ~0x0008;         //disable sequencer interrupts
   ADC0_ACTSS_R|=0x0008;        //enable sample sequencer
              
}


//------------ADC0_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC0_In(void){  
	unsigned long result;
	ADC0_PSSI_R = 0x08;		// Initiate SS3
	// Check ADC0
	while((ADC0_RIS_R & 0x08) == 0){};	// Wait
	result = ADC0_SSFIFO3_R & 0xFFF;	// ADC conversion is 12 bits
	ADC0_ISC_R = 0x08;		// Clear flag
	return result;
}


//------------ADC1_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD1, analog channel 6
uint32_t ADC1_In(void){  
	unsigned long result;
	ADC1_PSSI_R = 0x08;		// Initiate SS3
	
	while((ADC1_RIS_R & 0x08) == 0){};	// Wait
	result = ADC1_SSFIFO3_R & 0xFFF;	// ADC conversion is 12 bits
	ADC1_ISC_R = 0x08;		// Clear flag
	return result;
}

uint32_t convertADC(uint32_t value){
	return value>>10;
}

