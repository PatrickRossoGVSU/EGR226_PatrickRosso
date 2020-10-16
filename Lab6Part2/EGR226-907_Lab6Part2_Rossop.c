#include "msp.h"


/**
 * main.c
 */

int num;
int j = -1;
char pin[4];

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
    for(cols=0;cols<3;cols++){//loop through three columns
        P4->DIR = 0;
        P4->DIR |= BIT(4+cols);//making the columns output to avoid short
        P4->OUT &=~ BIT(4+cols);
        systick_delay(10);
        rows = P4->IN & 0x0F;
        while ( !(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3) ); //button debounce
        if(rows != 0x0F){//evaluate button press
            break;
        }
    }
    P4->DIR = 0;
    if(cols==3){//if button is not pressed
        return 0;
    }
    if(rows==0x0E){//the following if statements assign values according to keypad value
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

void shift(void){
    j++;
    if(j==4){
        j=3;
        pin[0] = pin[1];
        pin[1] = pin[2];
        pin[2] = pin[3];
    }
}

void print_keys(void){
    switch(num){
    case 1:
        shift();//shift input
        pin[j] = '1';//set array
        printf("%c\n", pin[j]);//print the key press
        break;
    case 3:
        shift();
        pin[j] = '2';
        printf("%c\n", pin[j]);
        break;
    case 2:
        shift();
        pin[j] = '3';
        printf("%c\n", pin[j]);
        break;
    case 4:
        shift();
        pin[j] = '4';
        printf("%c\n", pin[j]);
        break;
    case 6:
        shift();
        pin[j] = '5';
        printf("%c\n", pin[j]);
        break;
    case 5:
        shift();
        pin[j] = '6';
        printf("%c\n", pin[j]);
        break;
    case 7:
        shift();
        pin[j] = '7';
        printf("%c\n", pin[j]);
        break;
    case 9:
        shift();
        pin[j] = '8';
        printf("%c\n", pin[j]);
        break;
    case 8:
        shift();
        pin[j] = '9';
        printf("%c\n", pin[j]);
        break;
    case 10:
        printf("Not valid input");
        break;
    case 12:
        shift();
        pin[j] = '0';
        printf("%c\n", pin[j]);
        break;
    case 11:
        enter();
        break;
    }
}

void enter(void){
    if(pin[3]=='\0'){
        printf("Please enter 4 numbers");
    }else{
        printf("%c", pin[0]);
        printf("%c", pin[1]);
        printf("%c", pin[2]);
        printf("%c", pin[3]);
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
