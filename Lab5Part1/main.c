#include "msp.h"

/**

* main.c

*/


void systick_init(void){
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;
}

void systick_delay(uint16_t delay){
    SysTick->LOAD=((delay*3000)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

uint8_t debounce(int delay){
    systick_delay(delay);
    if((P1->IN & BIT6) == 0){
        return 1;
    }
    return 0;
}

void main(void)

{

                WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;                   // stop watchdog timer

                systick_init();

                P1->SEL0 &=~ BIT6;//Switch (input) setup
                P1->SEL1 &=~ BIT6;
                P1->REN |= BIT6;
                P1->DIR &=~ BIT6;
                P1->OUT |= BIT6;

                P4->SEL0 &=~ 0b00000111;//LED (output) setup
                P4->SEL1 &=~ 0b00000111;
                P4->DIR |= 0b00000111;
                P4->OUT &=~ 0b00000111;

                uint16_t delay = 70;
                int j = 0;

                while(1){//infinate loop
                    if((P1->IN & BIT6) == 0){//if the button is pressed
                        if(debounce(delay)==1){//debounce
                        switch (j){
                        case 0:

                                P4->OUT &=~ BIT2;
                                P4->OUT |= BIT0;
                                while((P1->IN & BIT6) == 0){//delay until button is released
                                    systick_delay(5);
                                }
                                j = 1;
                                break;

                        case 1:

                                P4->OUT &=~ BIT0;
                                P4->OUT |= BIT1;
                                while((P1->IN & BIT6) == 0){
                                    systick_delay(5);
                                }
                                j = 2;
                                break;

                        case 2:

                                 P4->OUT &=~ BIT1;
                                 P4->OUT |= BIT2;
                                 while((P1->IN & BIT6) == 0){
                                     systick_delay(5);
                                 }
                                 j = 0;
                                 break;


                        }
                    }
                }
                }
}
