#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "GPIO.h"
#include "Screen.h"
#include "game.h"
#include "TExaS.h"

extern int SW1, SW2;
void GPIOPortB_Handler(void)
{
  
    if (GPIO_PORTB_MIS_R & 0x10) 
    {                            
			GPIO_PORTB_ICR_R = 0x10;
      SW1 = 1;
    }
		else if (GPIO_PORTB_MIS_R & 0x01) 
		{                                 
			GPIO_PORTB_ICR_R = 0x01;
			SW2 = 1;
    }
}
int main(void)
{
	
	Nokia5110_Init();
	Nokia5110_DisplayBuffer();      
	showIntro();
	reset();
	GPIO_Init(&PortBconfg,GPIO_PORT_B);
	while(1){
		SW1 = 0, SW2 = 0;
		WaitForInterrupt();
		play();
	}
}