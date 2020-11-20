//Patrick Rosso Lab 11 Part 1
//EGR 226 Sec 907 - Trevor Ekin
#include "msp.h"

void TimerA0init(void)//setup Timer A0
{
  P2->SEL0 |= BIT4;
  P2->SEL1 &=~ BIT4;
  P2->DIR |= BIT4;                  // P2.4 set TA0.1

  TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK |     // SMCLK
              TIMER_A_CTL_MC__UP |      // Up mode
              TIMER_A_CTL_CLR |         //Clear timer
              TIMER_A_CTL_ID__8;        //Divide clock by 8
  TIMER_A0->CCR[0] = 37416;
  TIMER_A0->CCR[1] = 37416 / 2;
  TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
}

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    TimerA0init();
    while (1);
}
