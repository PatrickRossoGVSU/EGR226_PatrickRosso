//Patrick Rosso Lab 8 Part 3
//EGR 226 Sec 907 - Trevor Ekin
#include "msp.h"


/**
 * main.c
 */

int num;
int dutyCycle = 0;

void systick_init(void){//init systick
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;

}

void systick_delay(uint16_t delay){//delay function
    SysTick->LOAD=((delay*300)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);

}

uint8_t read_keypad(void){
    int rows;
    int cols;
    for(cols=0;cols<3;cols++){//scan through columns
        P4->DIR = 0;
        P4->DIR |= BIT(4+cols);
        P4->OUT &=~ BIT(4+cols);
        systick_delay(10);
        rows = P4->IN & 0x0F;
        while ( !(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3) );
        if(rows != 0x0F){
            break;
        }
    }
    P4->DIR = 0;
    if(cols==3){
        return 0;
    }
    if(rows==0x0E){//give num a value depending on row and column
        num = cols+1;
    }
    if(rows==0x0D){
        num = cols+4;
    }
    if(rows==0x0B){
        num = cols+7;
    }
    if(rows==0x07){
        num = cols+10;
    }
    return 1;
}

void print_keys(void){
    switch(num){//takes the num value and assigns it to dutyCycle
    case 1:
        printf("1\n");
        dutyCycle = 10;
        break;
    case 2:
        printf("2\n");
        dutyCycle = 20;
        break;
    case 3:
        printf("3\n");
        dutyCycle = 30;
        break;
    case 4:
        printf("4\n");
        dutyCycle = 40;
        break;
    case 5:
        printf("5\n");
        dutyCycle = 50;
        break;
    case 6:
        printf("6\n");
        dutyCycle = 60;
        break;
    case 7:
        printf("7\n");
        dutyCycle = 70;
        break;
    case 8:
        printf("8\n");
        dutyCycle = 80;
        break;
    case 9:
        printf("9\n");
        dutyCycle = 90;
        break;
    case 10:
        printf("*\n");
        dutyCycle = 100;
        break;
    case 11:
        printf("0\n");
        dutyCycle = 0;
        break;
    case 12:
        printf("Enter Valid Input\n");
        break;
    }
}

void main(void)
{
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
systick_init();
int check = 0;

P4->SEL0 &=~ 0x0F;//columns
P4->SEL1 &=~ 0x0F;
P4->REN |= 0x0F;
P4->DIR &=~ 0x0F;
P4->OUT |= 0x0F;


P4->SEL0 &=~ 0x70;//rows
P4->SEL1 &=~ 0x70;
P4->DIR &=~ 0x70;

int period = 80000;//needs to be 40hz

P2->DIR |= BIT4;//Timer A
P2->SEL0 |= BIT4;
P2->SEL1 &=~ BIT4;

TIMER_A0->CCR[0] = period;//period
TIMER_A0->CCR[1] = dutyCycle*100;//dutyCycle

TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;//output mode
TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;//source, mode, clear

while(1){
    check = read_keypad();//read the keypad
    if(check){//check if a key was pressed
            print_keys();//assign it to dutyCycle
            systick_delay(10);
}
    TIMER_A0->CCR[1] = dutyCycle*100;//set the dutyCycle
}
}
