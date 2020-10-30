//Patrick Rosso Lab 8 Part 2
//EGR 226 Sec 907 - Trevor Ekin
#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	int period = 80000;//40 hz
	int dutyCycle = 90;//duty cycle
	P2->DIR |= BIT4;
	P2->SEL0 |= BIT4;//set 2.4 to timer A0
	P2->SEL1 &=~ BIT4;

	TIMER_A0->CCR[0] = period;//declare the period
	TIMER_A0->CCR[1] = dutyCycle * 100;//declare the duty cycle

	TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;//output mode
	TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//source, mode, clear

	while(1){
	    TIMER_A0->CCR[1] = dutyCycle * 100;//re-input the duty cycle when needed
	}
}
