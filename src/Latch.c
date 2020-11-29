// -------------------------------------------------------------------
// File name:     Latch.c
// Description:   This starter code is for the Latch on the SafeBox. 
//								Latch is a plastic rod controlled by a micro servo.
// Authors:       Manolo Alvarez
// Last update: 	October 29, 2020

/** ------------------ Micro Servo Configuration ----------------------- //
SG90 9g Micro Servo
 
 Connections:
 Brown - Ground
 Red - +5V
 Organge - PB6 / PWM
 
 Set-Up:
 Periodic PWM Signal - 50 Hz
 Duty Cycle - 1ms (-90°)
							1.5ms (0°)
							2ms (+90°)

	Note: Shaft can only rotate a total of 180°.
** ---------------------------------------------------------------------**/

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"
#include "../inc/PWM.h"

void Clock_Delay1ms(uint32_t);

//------------LatchInit------------
// Initialize PWM0
// Input: none
// Output: none
void LatchInit(void){
  PWM0A_Init(25000, 2500);       // initialize PWM0, 50 Hz, 20% duty
	Clock_Delay1ms(1000);
}
//------------Close Latch------------
// Close Latch
// Input: none
// Output: none
void CloseLatch(void){
	PWM0A_Duty(1250);							 // 20%
	Clock_Delay1ms(1000);
}
//------------OpenLatch------------
// Open Latch
// Input: none
// Output: none
void OpenLatch(void){
	PWM0A_Duty(2500);							 // 10%
	Clock_Delay1ms(1000);
}
