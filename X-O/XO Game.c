#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "GPIO.h"
#include "Screen.h"
#include "game.h"

extern int SW1, SW2;

int main(void)
{
	
	SW1_Init();
	SW2_Init();
	Nokia5110_Init();
	Nokia5110_DisplayBuffer();      
	showIntro();
	reset();
	while(1){
		SW1 = 0, SW2 = 0;
		WaitForInterrupt();
		play();
	}
}