#include "tm4c123gh6pm.h"
#include "Timer.h"

void Timer2_Init(unsigned long period) { 
    SYSCTL_RCGCTIMER_R |= 0x04;    // 1) Activate timer2
    TIMER2_CTL_R = 0x00000000;     // 2) Disable timer2A during setup
    TIMER2_CFG_R = 0x00000000;     // 3) Configure for 32-bit mode
    TIMER2_TAMR_R = 0x00000001;    // 4) Configure for one-shot mode
    TIMER2_TAILR_R = period - 1;   // 5) Load the reload value

    TIMER2_ICR_R = 0x00000001;     // 6) Clear Timer2A timeout flag
    TIMER2_IMR_R = 0x00000001;     // 7) Enable Timer2A timeout interrupt

    NVIC_PRI5_R = (NVIC_PRI5_R & 0xFFFF00FF) | 0x00004000; // 8) Set priority to 2
    NVIC_EN0_R = 1 << 23;          // 9) Enable IRQ 23 (Timer2A)
    TIMER2_CTL_R |= 0x00000001;    // 10) Enable timer2A
}

 
