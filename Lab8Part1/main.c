//Patrick Rosso Lab 8 Part 1
//EGR 226 Sec 907 - Trevor Ekin
#include "msp.h"

void systick_init(void){//initialize Systick
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;

}

void delay_ms(uint16_t delay){//delay function in ms
    SysTick->LOAD=((delay*3000)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);

}
void main(void)
{
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
systick_init();
int period = 25;//needs to be around 40 Hz
int dutyCycle = 50;
P6->SEL0 &=~ BIT0;//initialize the pin going to the transitor gate
P6->SEL1 &=~ BIT0;
P6->DIR |= BIT0;
P6->OUT |= BIT0;



while(1){
P6->OUT |= BIT0;
delay_ms((period * dutyCycle)/100);//on for the duty cycle
P6->OUT &=~ BIT0;
delay_ms(period - ((period * dutyCycle)/100));//off for the remainder of the period
}
}
