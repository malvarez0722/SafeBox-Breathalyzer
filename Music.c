#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "DAC.h"

//Lengths of notes set to 60BPM
#define W						320000000		
#define DH					240000000		
#define H						160000000		
#define Q						80000000			//Same as clock speed 80MHZ
#define DE					60000000
#define	T						26666667
#define EI					40000000		
#define SX					20000000
#define SSX					13333333
#define TS					10000000

//Frequencies for Notes
#define	C7		597
#define	B6		633
#define AS6		670
#define	A6		710
#define	GS6		752
#define	G6		797
#define	FS6		845
#define	F6		895
#define	E6		953
#define	DS6		1004
#define	D6		1064
#define	CS6		1127
#define	C6		1195
#define	B5		1265
#define AS5		1341
#define	A5		1420
#define	GS5		1505
#define	G5		1594
#define	FS5		1689
#define	F5		1790
#define	E5		1896
#define	DS5		2009
#define	D5		2128
#define	CS5		2255
#define	C5		2389
#define	B4		2530
#define AS4		2681
#define	A4		2841
#define	GS4		3012
#define	G4		3189
#define	FS4		3378
#define	F4		3582
#define	E4		3788
#define	DS4		4109
#define	D4		4252
#define	CS4		4513
#define	C4		4771
#define	B3		5062
#define A3		5682
#define G3		6378
#define FS3		6757

#define R			0			 // rest (no sound)

#define MEASURES  288

static uint32_t length;
static uint32_t note;

// Array for sounds

	uint32_t pitch0[MEASURES] = {B4,R,B4,A4,R,A4,R,A4,B4,R,B4,R,B4,A4,R,A4,R,A4,B4,R,FS5,A5,B5,D6,CS6,A5,B5,
		B4,R,B4,A4,R,A4,R,A4,B4,R,FS5,A5,B5,B5,D5,CS5,B4,R,B4,A4,R,A4,R,A4,FS4,FS4,
	FS5,E5,D5,CS5,D5,D5,CS5,B4,A4,CS5,CS5,D5,CS5,A4,A4,FS5,FS5,A5,GS5,E5,FS5,FS5,D5,E5,FS5,E5,
	B5,G5,D5,B5,G5,D5,B5,CS6,D6,CS6,CS6,A5,R,B5,A5,G5,B5,A5,G5,B5,CS6,FS6,E6,E6,
	CS6,D6,CS6,A5,G5,A5,B5,B5,CS6,D6,FS6,E6,D6,CS6,CS6,D6,CS6,A5,B5,B4,A4,GS4,
	R,FS5,D5,B4,D5,FS5,E5,B5,FS5,E5,CS5,D5,E5,A4,A4,A5,G5,FS5,G5,FS5,E5,D5,CS5,A4,
	G5,B5,CS6,D6,E6,FS6,CS6,E6,D6,D6,FS5,A5,B5,CS6,D6,CS6,E6,D6,CS6,A5,G5,FS5,
	FS4,FS4,G4,FS4,FS4,G4,FS4,G4,A4,FS4,G4,A4,FS4,CS5,A4,FS4,D4,FS4,FS4,G4,FS4,FS4,G4,FS4,G4,A4,E4,FS4,A4,FS4,CS5,A4,FS4,CS5,
	G5,B5,D6,G5,B5,D6,G5,B5,D6,G5,B5,D6,E6,D6,CS6,FS5,A5,CS6,FS5,A5,CS6,FS5,A5,CS6,FS5,A5,CS6,D6,CS6,CS6,
	G3,FS3,A3,FS3,A3,B3,A3,B3,CS4,B3,CS4,D4,E4,FS4,A4,G4,A4,B4,A4,B4,CS5,B4,CS5,D5,
	FS5,A5,FS5,D5,CS5,D5,FS5,A5,FS5,CS6,A5,FS5,CS6,B5,FS5,D5,FS5,A5,G5,FS5,E5,FS5,G5,A5,A5,FS4,A4,FS4,A4};
		
	uint32_t duration[MEASURES] = {Q,EI,SX,SX,H,Q,EI,SX,SX,H,Q,EI,SX,SX,H,Q,EI,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,
	Q,EI,SX,SX,H,Q,EI,SX,SX,SX,SX,SX,SX,SX,SX,SX,Q,EI,SX,SX,H,Q,EI,SX,SX,H,
	DE,EI,SX,SX,SX,Q,SX,SX,SX,Q,EI,SX,SX,SX,H,Q,SX,SX,SX,SX,Q,SX,SX,SX,SX,W,
	SSX,SSX,SSX,SSX,SSX,SSX,SX,SX,SX,SX,Q,DE,SX,SSX,SSX,SSX,SSX,SSX,SSX,SX,SX,SX,SX,Q,
	SX,SX,SX,SX,EI,SX,SX,SX,SX,SX,SX,EI,SX,SX,SX,SX,SX,SX,DH,T,T,T,
	SX,SX,SX,SX,EI,EI,EI,SX,DE,EI,SX,SX,SX,SX,SX,SX,EI,SSX,SSX,SSX,SX,SX,SX,DE,
	SX,SX,SX,DE,EI,EI,SX,DE,EI,SX,SX,SX,SX,SX,SX,SX,EI,SX,SX,EI,SX,EI,
	SX,TS,TS,SX,TS,TS,SX,SX,SX,EI,SX,SX,SX,SX,SX,SX,SX,SX,TS,TS,SX,TS,TS,SX,SX,SX,EI,SX,SX,SX,SX,SX,SX,SX,
	SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,EI,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,SX,EI,
	SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,SSX,
	EI,SX,EI,SX,SX,SX,EI,SX,SX,SX,SX,SX,DE,EI,T,T,T,EI,SX,EI,SX,SX,SX,H,EI,SX,EI,SX,EI};


static uint32_t position;
//static int32_t play;
//static uint16_t songCount;


//////////////////////////////////////////////////////////////////////////
void Timer3A_Init (void) {
	SYSCTL_RCGCTIMER_R |= 0x08;   // 0) activate TIMER0
  TIMER3_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER3_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER3_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER3_TAILR_R = 0x80000000;  // 4) reload value
  TIMER3_TAPR_R = 0;            // 5) bus clock resolution
  TIMER3_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
	TIMER3_IMR_R = 0x00000001;
  NVIC_PRI8_R |= 0x20000000; // 8) priority 1
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN1_R = 1<<(35-32);           // 9) enable IRQ 19 in NVIC
  TIMER3_CTL_R = 0x00000001;    // 10) enable TIMER0A
	
	return;
};

uint8_t key;
void Play_Note0(uint32_t note){
	if (note ==0){
		NVIC_EN0_R ^= 1<<19;	//turn off note
		TIMER0_ICR_R = 0x00000001;   			 // 6) clear TIMER0A timeout flag
		return;
	}
	restartWaveForm();
	TIMER0_TAILR_R = note;
	TIMER0_ICR_R = 0x00000001;   			 // 6) clear TIMER0A timeout flag
	TIMER0_IMR_R = 0x00000001;				 // 7) arm timeout interrupt
	return;
}

void Music_Play (void) {
	position = 0;														//restart song
	NVIC_EN0_R ^= 1<<19;
	length = duration[position]*8/19;	//Play first note duration
	note = pitch0[position];			//Play first note
	envelope(length,note);
	TIMER3_TAILR_R = length;
	Play_Note0(note);
	TIMER3_ICR_R = 0x00000001;   			 // 6) clear TIMER0A timeout flag
	TIMER3_IMR_R = 0x00000001;    		 // 7) arm timeout interrupt
};

void Timer3A_Handler (void){
	position ++;
	if (position == MEASURES){
		TIMER3_IMR_R = 0x00000000;
		TIMER0_IMR_R = 0x00000000;
		return;
	}
	length = duration[position]*8/19;
	note = pitch0[position];
	envelope(length,note);
	TIMER3_TAILR_R = length;   	 							 // reload value for Timer 3A
	Play_Note0 (note);
	TIMER3_ICR_R = TIMER_ICR_TATOCINT;   			 // Acknowledge
};

