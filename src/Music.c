#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Music.h"

//Lengths of notes set to 60BPM
#define W						160000000		
#define DH					120000000		
#define H						80000000
#define DQ					60000000
#define Q						40000000			//Half clock speed 80MHZ for 120BPM
#define DE					30000000
#define	T						13333334
#define EI					20000000		
#define SX					10000000
#define SSX					6666667
#define TS					5000000

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

#define TGIF	0
#define RYG		1

static uint32_t length;
static uint32_t note;
static uint32_t position;
static uint8_t Selected_Track;

// Array for sounds
#define TGIF_NOTES 	52
	uint32_t pitchTGIF[TGIF_NOTES] = {AS4,B4,CS5,R,CS5,R,CS5,R,AS4,B4,CS5,R,CS5,R,CS5,R,FS5,CS5,R,R,CS5,GS4,R,
	AS4,B4,CS5,R,CS5,R,CS5,R,AS4,B4,CS5,R,CS5,R,CS5,R,FS5,CS5,AS4,R,GS4,R,AS4,R,GS4,FS4,R,FS4,R};
		
	uint32_t durationTGIF[TGIF_NOTES] = {EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,Q,EI,H,EI,DQ,H,
	EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,EI,Q,EI,DQ,EI,H,EI,EI,EI,EI,EI,EI,EI};
		
#define RYG_NOTES 	80
	uint32_t pitchRYG[RYG_NOTES] = {G4,R,G4,R,G4,R,G4,R,G4,R,G4,R,G4,R,G4,R,E4,E4,G4,E4,G4,A4,G4,G4,D5,B4,A4,R,G4,A4,B4,A4,G4,B4,A4,G4,
	G4,G4,G4,G4,G4,E4,G4,E4,G4,A4,G4,G4,D5,B4,A4,R,G4,A4,B4,A4,G4,B4,A4,G4,G4,R,G4,R,G4,R,G4,A4,B4,A4,G4,B4,A4,G4,C5,R,G4,R,A4,R};
		
	uint32_t durationRYG[RYG_NOTES] = {SX,SX,SX,SX,SX,SX,EI,SX,EI,SX,EI,SX,EI,SX,SX,SX,Q,EI,EI,EI,Q,Q,DE,DE,DE,DE,Q,Q,EI,EI,SX,SX,EI,SX,SX,EI,
	DE,DE,DE,DE,EI,Q,EI,EI,EI,Q,Q,DE,DE,DE,DE,Q,Q,EI,EI,SX,SX,EI,SX,SX,EI,Q,EI,Q,EI,Q,DQ,Q,SX,SX,EI,SX,SX,EI,Q,EI,Q,EI,Q,EI};

//////////////////////////////////////////////////////////////////////////
void DAC_Init (uint16_t data){
	SYSCTL_RCGCSSI_R |= 0x02;				//activate SSI1
	SYSCTL_RCGCGPIO_R |= 0x08;			//activate PORT D
	
	while((SYSCTL_RCGCGPIO_R & 0x08) == 0){};
		SSI1_CR1_R = 0x00000000;
		GPIO_PORTD_AFSEL_R |= 0x0B;
		GPIO_PORTD_DEN_R |= 0x0B;
		GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0xFFFF0F00) + 0x00002022;

		GPIO_PORTD_AMSEL_R &= ~0x0B;
		SSI1_CPSR_R =0x08;						//10MHz SSIClk
		SSI1_CR0_R &= ~(0x0000FFF0);	//SCR = 0    SPH = 0   SPO = 1
		SSI1_CR0_R += 0x40;						//SPO = 1
		SSI1_CR0_R |= 0x0F;						//DSS 16-bit data
		SSI1_DR_R = data;
		SSI1_CR1_R |= 0x00000002;
}

void Timer0A_Init(void){
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = 0x80000000;  // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  NVIC_PRI4_R |= 0x20000000; 		// 8) priority 1
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
	return;
}
void Timer1A_Init(void){
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER0
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = 0x80000000;  // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  NVIC_PRI5_R |= 0x2000; 				// 8) priority 1
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER0A	
	return;
}

void Music_Init(void) {
	DAC_Init(100);
	Timer0A_Init();
	Timer1A_Init();
	return;
}
/////////////////////////////////////////////////////////////////////////////////////
void Play_Note(uint32_t note){
	if (note ==0){
		NVIC_EN0_R = 1<<21;            // 9) disable interrupt 21 in NVIC
		TIMER1_CTL_R = 0x00000000;     // 10) disable timer1A
		return;
	}
	//restartWaveForm();
	TIMER1_TAILR_R = note;
	TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
	return;
}

void Play_Music (uint8_t Track_Select) {
	Selected_Track = Track_Select;
	position = 0;														//restart song
	NVIC_EN0_R ^= 1<<19;
	NVIC_EN0_R ^= 1<<21;
	
	if (Selected_Track == TGIF){
		length = durationTGIF[position];	//Play first note duration
		note = pitchTGIF[position];				//Play first note
	};
	if (Selected_Track == RYG) {
		length = durationRYG[position];	//Play first note duration
		note = pitchRYG[position];				//Play first note
	};
	//envelope(length,note);
	TIMER0_TAILR_R = length;
	Play_Note(note);
	TIMER0_ICR_R = 0x00000001;   			 // 6) clear TIMER0A timeout flag
	TIMER0_IMR_R = 0x00000001;    		 // 7) arm timeout interrupt
	TIMER1_ICR_R = 0x00000001;   			 // 6) clear TIMER0A timeout flag
	TIMER1_IMR_R = 0x00000001;    		 // 7) arm timeout interrupt
	TIMER0_CTL_R = 0x00000001;				 //Enable Timer 0A
};

// **************DAC_Out*********************
void DAC_Out(uint32_t code){
	while((SSI1_SR_R & 0x00000002) == 0){}; 		// Wait until room in FIFO
	SSI1_DR_R = code; //data out
}
//////////////////////////////////////////////////////////////////////
//////Timer for Duration of Note i.e. Quarter, Half, Whole, etc.//////
void Timer0A_Handler (void){
	position ++;
	if ((Selected_Track == TGIF && position == TGIF_NOTES) || (Selected_Track == RYG && position == RYG_NOTES)){
		TIMER0_IMR_R = 0x00000000;
		TIMER0_IMR_R = 0x00000000;
		return;
	}
	if (Selected_Track == TGIF){
		length = durationTGIF[position];	//Play first note duration
		note = pitchTGIF[position];				//Play first note
	};
	if (Selected_Track == RYG) {
		length = durationRYG[position];	//Play first note duration
		note = pitchRYG[position];				//Play first note
	};
	//envelope(length,note);
	TIMER0_TAILR_R = length;   	 							 // reload value for Timer 0A
	Play_Note(note);
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;   			 // Acknowledge
};

///////////Timer for Frequency of Note i.e. A4,B4,C4, etc.///////////
uint8_t i;
void Timer1A_Handler(void){
	uint16_t data = Trumpet64[i];
	DAC_Out(data);
	i = (i+1) &0x3F;
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;   			 // Acknowledge
	return;
}
