//Patrick Rosso Lab 10 Part 2
//EGR 226 Sec 907 - Trevor Ekin
#include "msp.h"

//intitialize systick
void systick_init(void){
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;

}

//delay function in milliseconds
void systick_delay(uint16_t delay){
    SysTick->LOAD=((delay*3000)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);

}

//initialize adc on pin 5.5
void ADC14_init(void){
    P5->SEL0 |= 0x20;
    P5->SEL1 |= 0x20;
    ADC14->CTL0 &=~ 0x00000002;
    ADC14->CTL0 |= 0x04400110;
    ADC14->CTL1 = 0x00000030;
    ADC14->CTL1 |= 0x00000000;
    ADC14->MCTL[0] = 0x00000000;
    ADC14->CTL0 |= 0x00000002;
}


/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    static volatile uint16_t result;
    float nADC;
    float fval;

    systick_init();
    ADC14_init();

    while(1){
            ADC14->CTL0|=1;
            while(!ADC14->IFGR0);
            result = ADC14->MEM[0];
            nADC = result;
            nADC = (nADC * 3.3)/16384;
            nADC = nADC * 1000;
            nADC = (nADC - 500)/10;

            fval = nADC * 1.8;
            fval += 32;

            printf("%.d\t%.2f\t%.2f\n", result, nADC, fval);//print reading, degrees in c, degrees in f
            systick_delay(1000);
        }
}
