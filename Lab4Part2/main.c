#include "msp.h"





/**

* main.c

*/

uint8_t debounce(int  delay){
    __delay_cycles(2000000);
    if((P1->IN & BIT1) == 0){
        return 1;
    }
    return 0;
}

void main(void)

{

                WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;                   // stop watchdog timer


                P1->SEL0 &=~ BIT1;//Switch (input) setup
                P1->SEL1 &=~ BIT1;
                P1->REN |= BIT1;
                P1->DIR &=~ BIT1;
                P1->OUT |= BIT1;

                P2->SEL0 &=~ 0b00000111;//LED (output) setup
                P2->SEL1 &=~ 0b00000111;
                P2->DIR |= 0b00000111;
                P2->OUT &=~ 0b00000111;

                const int  delay = 2000000;
                int j = 0;


                while(1){
                    if((P1->IN & BIT1) == 0){//if the button is pressed
                        if(debounce(delay)==1){//debounce
                        switch (j){
                        case 0:

                                P2->OUT &=~ BIT2;//clear Blue
                                P2->OUT |= BIT0;//set Red
                                j = 1;
                                printf("red");
                                break;

                        case 1:

                                P2->OUT &=~ BIT0;
                                P2->OUT |= BIT1;
                                j = 2;
                                printf("green");
                                break;

                        case 2:

                                 P2->OUT &=~ BIT1;
                                 P2->OUT |= BIT2;
                                 j = 0;
                                 printf("blue");
                                 break;


                        }
                    }
                }
                }
}
