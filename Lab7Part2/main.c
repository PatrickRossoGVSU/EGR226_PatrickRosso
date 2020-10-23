//Patrick Rosso Lab 7 Part 3
//EGR 226 Sec 907 - Trevor Ekin


#include "msp.h"


void port4_init(void){//init Port 4
    P4->SEL0 &=~ 0x0F7;
    P4->SEL1 &=~ 0x0F7;
    P4->DIR |= 0x0F7;
    P4->OUT &=~ 0x0F7;
}

void systick_init(void){//init SysTick
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;
}

void delay_micro(unsigned microsec){//Use SysTick to delay in Microseconds
    SysTick->LOAD=((microsec*3)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

void delay_ms(unsigned ms){//Use SysTick to delay in milliseconds
    SysTick->LOAD=((ms*3000)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

void PulseEnablePin(void){
    P4->OUT &=~ BIT1;
    delay_micro(10);
    P4->OUT |= BIT1;
    delay_micro(10);
    P4->OUT &=~ BIT1;
}

void pushNibble(uint8_t nibble){//send data to the LCD
    P4->OUT &=~ 0xF0;
    P4->OUT |= (nibble & 0x0F)<<4;
    PulseEnablePin();
}

void pushByte(uint8_t byte){//Split a byte into two nibbles to send to the LCD
    uint8_t nibble;
    nibble = (byte & 0xF0)>>4;
    pushNibble(nibble);
    nibble = byte & 0x0F;
    pushNibble(nibble);
    delay_micro(100);
}

void write_command(uint8_t command){//send commands to the LCD
    P4->OUT &=~ BIT0;
    pushByte(command);
}

void write_data(uint8_t data){//send data to the LCD
    P4->OUT |= BIT0;
    pushByte(data);
}

void print_string(char string[]){//send a string to the LCD
    int i;
    for(i=0; i<strlen(string); i++){
        write_data(string[i]);
    }
}

void LCD_init(void){//init the LCD
    write_command(3);
    delay_ms(100);
    write_command(3);
    delay_micro(200);
    write_command(3);
    delay_ms(100);
    write_command(2);

    delay_micro(100);
    write_command(0x28);
    delay_micro(100);

    delay_micro(100);
    write_command(0x0F);
    delay_micro(100);
    write_command(1);
    delay_micro(100);
    write_command(6);
    delay_ms(10);
}

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    port4_init();
    systick_init();
    LCD_init();

    int i;

    for(i = 0; i<5; i++){//move to the middle of the first line
        write_command(0b10100);
    }

    print_string("Patrick");

    for(i = 0; i<34; i++){//move to the middle of the second line
        write_command(0b10100);
    }

    print_string("Rosso");

    for(i = 0; i<28; i++){//move to the middle of the third line
        write_command(0b10000);
    }

    print_string("EGR");

    for(i = 0; i<37; i++){//move to the middle of the fourth line
        write_command(0b10100);
    }

    print_string("226");

    while(1){}
}
