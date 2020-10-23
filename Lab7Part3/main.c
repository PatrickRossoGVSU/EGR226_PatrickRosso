//Patrick Rosso Lab 7 Part 3
//EGR 226 Sec 907 - Trevor Ekin

#include "msp.h"

void port4_init(void){//init P4 pins
    P4->SEL0 &=~ 0x0F7;
    P4->SEL1 &=~ 0x0F7;
    P4->DIR |= 0x0F7;
    P4->OUT &=~ 0x0F7;
}

void systick_init(void){//init Systick
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;
}

void delay_micro(unsigned microsec){//delay in microseconds
    SysTick->LOAD=((microsec*3)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

void delay_ms(unsigned ms){//delay in milliseconds
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

void pushNibble(uint8_t nibble){//push individual nibbles
    P4->OUT &=~ 0xF0;
    P4->OUT |= (nibble & 0x0F)<<4;
    PulseEnablePin();
}

void pushByte(uint8_t byte){//seperate bytes into nibbles
    uint8_t nibble;
    nibble = (byte & 0xF0)>>4;
    pushNibble(nibble);
    nibble = byte & 0x0F;
    pushNibble(nibble);
    delay_micro(100);
}

void write_command(uint8_t command){//writing commands
    P4->OUT &=~ BIT0;
    pushByte(command);
}

void write_data(uint8_t data){//writing data
    P4->OUT |= BIT0;
    pushByte(data);
}

void print_string(char string[]){//sending a string to write data
    int i;
    for(i=0; i<strlen(string); i++){
        write_data(string[i]);
    }
}

void ret(void){//return to index 0 on the LCD
    int i;
    for(i=0; i<=16; i++){
        write_command(0b010000);
    }
    write_command(0b010100);
    delay_ms(500);
}

void phase1(void){//first half of the cycle
    int i;
    int j;
    int k;
    char string[17] = "LABORATORY OVER ";
    print_string(string);
    ret();
    for(k=0; k<16; k++){
    for(j=0; j<16; j++){
    for(i=0; i<16; i++){
        string[j] = string[j+1];
        string[15] = ' ';
    }
    }
    print_string(string);
    ret();
    }
}

void phase2(void){//second half of the cycle
    print_string("               L");
    ret();
    print_string("              LA");
    ret();
    print_string("             LAB");
    ret();
    print_string("            LABO");
    ret();
    print_string("           LABOR");
    ret();
    print_string("          LABORA");
    ret();
    print_string("         LABORAT");
    ret();
    print_string("        LABORATO");
    ret();
    print_string("       LABORATOR");
    ret();
    print_string("      LABORATORY");
    ret();
    print_string("     LABORATORY ");
    ret();
    print_string("    LABORATORY O");
    ret();
    print_string("   LABORATORY OV");
    ret();
    print_string("  LABORATORY OVE");
    ret();
    print_string(" LABORATORY OVER");
    ret();
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

    while(1){
        phase1();
        phase2();
    }
}
