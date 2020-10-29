// DAC.h
// Runs on TM4C123
// Ethan Denfeld
// Spetember 30th, 2020
// Device Driver for TLV5616 DAC

#include <stdint.h>
////////////////////////////////////////////
//DAC_Init
//Initilizes the DAC
//Inputs:	 None
//Outputs: None

void DAC_Init (void);

////////////////////////////////////////////
//DAC_Out
//Sends data through SSI on TM4C to the DAC
//Inputs:	 None
//Outputs: None

void DAC_Out (void);


//Init for Timer
void Timer0A_Init(uint32_t period);

//When song switches note, the waveform needs to start back at 0
void restartWaveForm(void);

//Call when changing note
void envelope(uint32_t duration, uint32_t note);
