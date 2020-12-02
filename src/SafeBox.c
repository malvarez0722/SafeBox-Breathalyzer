
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/Timer2.h"
#include "../inc/Timer3.h"
#include "../inc/UART.h"
#include "../inc/PortF.h"
#include "../inc/esp8266.h"
#include "../inc/Blynk.h"
#include "../inc/PWM.h"
#include "../inc/CortexM.h"
#include "../inc/Latch.h"
#include "../inc/LCD.h"

void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s

int main(void){
  PLL_Init(Bus80MHz);   // Bus clock at 80 MHz
  DisableInterrupts();  // Disable interrupts until finished with inits
	ST7735_InitR(INITR_REDTAB);
	ST7735_OutString("Breathalyzer Box\n");
	StateBox();
  PortF_Init();
	LatchInit();
	
#ifdef DEBUG1
  UART_Init(5);         // Enable Debug Serial Port
  UART_OutString("\n\rEE445L Lab 4D\n\rBlynk example");
#endif

  ESP8266_Init();       // Enable ESP8266 Serial Port
  ESP8266_Reset();      // Reset the WiFi module
  ESP8266_SetupWiFi();  // Setup communications to Blynk Server  
  
  Timer2_Init(&Blynk_to_TM4C,800000); 
  // check for receive data from Blynk App every 10ms

  Timer3_Init(&SendInformation,40000000); 
  // Send data back to Blynk App every 1/2 second
  EnableInterrupts();

  while(1) {
		PF2^= 0x02;
    WaitForInterrupt(); // low power mode
		if(pinFlag){
			switch (pin_num){
	  // ---------------------------- VP #1 ----------------------------------------
		// INITIALIZE SYSTEM/////
			case 1:
				EnableInterrupts();
				ST7735_FillScreen(ST7735_YELLOW);
				ST7735_DrawString(1,7, "Heating the sensor...", ST7735_BLACK);
				//Start Heating the MQ3 signal
				break;
		// ---------------------------- VP #2 ----------------------------------------
		// SLEEP MODE/////
			case 2:
				ST7735_FillScreen(ST7735_BLUE);
				ST7735_DrawCircle(23, 23, ST7735_WHITE);
				ST7735_DrawString(5,7, "Sleeping ZZZ...", ST7735_BLACK);
				Clock_Delay1ms(1000);
				ST7735_FillScreen(0);
				break;
		// ---------------------------- VP #3 ----------------------------------------
		// OPEN BOX/////
			case 3:		
				if(!alcoholLimit){ 
					OpenBox();
					OpenLatch();
					TM4C_to_Blynk(70, 0);
					break;
				}
				else break;
	// ---------------------------- VP #4 ----------------------------------------
  //// CLOSE BOX/////
			case 4:
				CloseBox();
				CloseLatch();
				TM4C_to_Blynk(70, 255);
				break;
	// ---------------------------- DEFAULT ----------------------------------------		
			default:
					break;
		}
			pinFlag = 0;
		}
  }
}
