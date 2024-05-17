#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "Timer.h"


void EnableInterrupts(void); 
extern int SW1, SW2;

void SW1_Init(void){                          
  SYSCTL_RCGC2_R |= 0x00000002; // (a) activate clock for port B
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
  GPIO_PORTB_DIR_R &= ~0x10;    // (c) make PF4 input (built-in button)
  GPIO_PORTB_AFSEL_R &= ~0x10;  //     disable alt funct on PF4
  GPIO_PORTB_DEN_R |= 0x10;     //     enable digital I/O on PF4
  GPIO_PORTB_PCTL_R &= ~0x000F0000; // configure PF4 as GPIO
  GPIO_PORTB_AMSEL_R = 0;       //     disable analog functionality on PF
  GPIO_PORTB_PUR_R |= 0x10;     //     enable weak pull-up on PF4
  GPIO_PORTB_IS_R &= ~0x10;     // (d) PF4 is edge-sensitive
  GPIO_PORTB_IBE_R &= ~0x10;    //     PF4 is not both edges
  GPIO_PORTB_IEV_R &= ~0x10;    //     PF4 falling edge event
  GPIO_PORTB_ICR_R = 0x10;      // (e) clear flag4
  GPIO_PORTB_IM_R |= 0x10;      // (f) arm interrupt on PF4
  NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFFFF00)|0x000000A0; // (g) priority 5
  NVIC_EN0_R = 1 << 1;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}


void SW2_Init(void){
	  SYSCTL_RCGC2_R |= 0x00000002; // (a) activate clock for port B
  GPIO_PORTB_LOCK_R   = 0x4C4F434B;
  GPIO_PORTB_CR_R |= (1<<0);
  GPIO_PORTB_DIR_R &= ~(1<<0);
  GPIO_PORTB_AFSEL_R &= ~(1<<0);
  GPIO_PORTB_DEN_R |= (1<<0);
  GPIO_PORTB_PCTL_R  &= 0xFFFFFFF0;
  GPIO_PORTB_AMSEL_R &= ~(1<<0);
  GPIO_PORTB_PUR_R |= (1<<0);
  GPIO_PORTB_IS_R &= ~(1<<0);
  GPIO_PORTB_IBE_R &= ~(1<<0);
  GPIO_PORTB_IEV_R &= ~(1<<0);
  GPIO_PORTB_ICR_R |= (1<<0);
  GPIO_PORTB_IM_R |= (1<<0);
  NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFFFF00)|0x000000A0; // (g) priority 5
  NVIC_EN0_R = 1 << 1;      // (h) enable interrupt 30 in NVIC
	EnableInterrupts();
}
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
