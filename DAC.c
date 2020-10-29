//See DAC.h for functions
#include <stdint.h>
#include "Music.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/LaunchPad.h"
#include "../inc/CortexM.h"

uint16_t I = 0;
uint16_t E = 0;
uint16_t envIndex = 0;
static const uint16_t envelopeArray[16]={ 90, 92, 93, 95, 97, 100, 100, 100, 95, 92, 90, 87, 85, 80, 77, 75};
uint32_t total = 0; //Amount of times timer is triggered per note
uint32_t envNum = 0; //How many timers untill envelope canges


////////////////////////////////////////////
// inputs: initial voltage (0 - 4095)
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

////////////////////////////////////////////
void DAC_Out (uint16_t code){
	while((SSI1_SR_R & 0x00000002) == 0){}; 		// Wait until room in FIFO
	SSI1_DR_R = code; //data out
		
}

void Timer0A_Init(uint32_t period){
  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER0_TAILR_R = period;         // start value for 100 Hz interrupts
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
	
	return;
}

void envelope(uint32_t duration, uint32_t note){
	total = ((note) * (duration / 8000000))/10;
	envNum = total;
	envIndex = 0;
	E = 0;
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
	I = (I+1)&0x3F;
	E++;
	if(E >= envNum){
		E = 0;
		if(envIndex < 15) envIndex++;
	}
	
	DAC_Out((Trumpet64[I] * envelopeArray[envIndex])/100);
}

void restartWaveForm(void){
	I = 0;
	return;
};
