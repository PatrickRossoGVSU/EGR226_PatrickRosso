//Patrick Rosso Lab 11 Part 2
//EGR 226 Sec 907 - Trevor Ekin
#include "msp.h"

unsigned short currentedge, period;
unsigned short lastedge = 0;


void LEDinit(void){//init on board LED at pin 2.0
    P2->SEL0 &=~ BIT0;
    P2->SEL1 &=~ BIT0;
    P2->DIR |= BIT0;
    P2->OUT &=~ BIT0;
}

void TimerA0init(void)//init timer a0
{
  P2->SEL0 |= BIT4;
  P2->SEL1 &=~ BIT4;
  P2->DIR |= BIT4;                  // P2.4 set TA0.1
  P2->SEL0 |= BIT5;                 // TA0.CCI2A input capture pin, second function
  P2->SEL1 &=~ BIT5;                  // TA0.CCI2A input capture pin, second function
  P2->DIR  &=~ BIT5;


  TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK |     // SMCLK
              TIMER_A_CTL_MC__UP |      // Up mode
              TIMER_A_CTL_CLR |         //Clear timer
              TIMER_A_CTL_ID__8;        //Divide clock by 8
  TIMER_A0->CCR[0] = 37416;

  TIMER_A0->CCR[1] = 37416 / 2;

  TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;

  TIMER_A0->CCTL[2] =TIMER_A_CCTLN_CM_1|           // Capture rising edge,
                     TIMER_A_CCTLN_CCIS_0|       // Use CCI2A=ACLK,
                     TIMER_A_CCTLN_CCIE|           // Enable capture interrupt
                     TIMER_A_CCTLN_CAP|           // Enable capture mode,
                     TIMER_A_CCTLN_SCS;               // Synchronous capture

}

void TA0_N_IRQHandler(void)         // Timer A0 interrupt service routine
 {
    currentedge = TIMER_A0->CCR[2];
    period = currentedge - lastedge;
    lastedge = currentedge;

    if ( ( 35635 <period ) && ( period < 39375 ) ){    // within 5% of 10Hz period
        P2->OUT |= BIT0;
    }else{
        P2->OUT &=~ BIT0;
    }
    TIMER_A0->CCTL[2] &= ~(TIMER_A_CCTLN_CCIFG);    // Clear the interrupt flag
 }


void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    TimerA0init();
    LEDinit();

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);            // Enable interrupt in NVIC vector
    __enable_irq ( );

    while (1);
}
