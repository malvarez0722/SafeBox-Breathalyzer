
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/Latch.h"
#include "../inc/ST7735.h"
#include "../inc/PortF.h"

//------------OpenBox------------
// Open Animation
// Input: none
// Output: none
void OpenBox(void){
	ST7735_FillScreen(ST7735_GREEN);
	ST7735_DrawCircle(23, 23, ST7735_WHITE);
	ST7735_DrawString(8,7, "OPEN", ST7735_BLACK);
}

//------------CloseBox------------
// Close Animation
// Input: none
// Output: none
void CloseBox(void){
	ST7735_FillScreen(ST7735_RED);
	ST7735_DrawCircle(23, 23, ST7735_WHITE);
	ST7735_DrawString(8,7, "CLOSED", ST7735_BLACK);
}

//------------StateBox------------
// Prints the State of the Box into the LCD
// Input: none
// Output: none
void StateBox(void){
	ST7735_FillScreen(ST7735_YELLOW);
}
//------------TestBox------------
// Uses switches to test the LCD
// Input: none
// Output: none
//void TestBox(void){
//	//ST7735_FillScreen(ST7735_BLUE);
//		if(!(PortF_Input()&0x01)){
//			OpenBox();
//		}
//		else if(!(PortF_Input()&0x10)){
//			CloseBox();
//		}
//}

