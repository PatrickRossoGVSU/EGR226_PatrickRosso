#include "msp.h"


/**
 * main.c
 */

int num;

void systick_init(void){
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;
    printf("init");

}

void systick_delay(uint16_t delay){
    SysTick->LOAD=((delay*3000)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);

}

uint8_t read_keypad(void){
    printf("\n");
    int rows;
    int cols;
    for(cols=0;cols<3;cols++){
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
    if(rows==0x0E){
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
    printf("\n");
    switch(num){//takes the num value and prints it
    case 1:
        printf("1");
        break;
    case 3:
        printf("2");
        break;
    case 2:
        printf("3");
        break;
    case 4:
        printf("4");
        break;
    case 6:
        printf("5");
        break;
    case 5:
        printf("6");
        break;
    case 7:
        printf("7");
        break;
    case 9:
        printf("8");
        break;
    case 8:
        printf("9");
        break;
    case 10:
        printf("*");
        break;
    case 12:
        printf("0");
        break;
    case 11:
        printf("#");
        break;
    }
}

void main(void)
{
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
systick_init();
printf("check");
int check = 0;

P4->SEL0 &=~ 0x0F;
P4->SEL1 &=~ 0x0F;
P4->REN |= 0x0F;
P4->DIR &=~ 0x0F;
P4->OUT |= 0x0F;

printf("check1");

P4->SEL0 &=~ 0x70;
P4->SEL1 &=~ 0x70;
P4->DIR &=~ 0x70;

while(1){
    check = read_keypad();
    if(check){
            print_keys();
            systick_delay(10);
}
}
}
