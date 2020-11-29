//*****************  BlynkTest.c   ************************//
// Runs on TM4C123
// Uses ESP8266 Wi-Fi Module
// Manolo Alvarez
// November 5th, 2020
//*****************************************************//

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

void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s

int main7(void){       
  PLL_Init(Bus80MHz);   // Bus clock at 80 MHz
  DisableInterrupts();  // Disable interrupts until finished with inits
  PortF_Init();
//#ifdef DEBUG3
//  //Output_Init();        // initialize ST7735
//  //ST7735_OutString("EE445L Lab 4D\nBlynk example\n");
//#endif
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
    WaitForInterrupt(); // low power mode
  }
}

