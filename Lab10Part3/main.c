//Patrick Rosso Lab 10 Part 3
//EGR 226 Sec 907 - Trevor Ekin
#include "msp.h"



//initialize adc on 5.5
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

//initialize LCD pins
void port4_init(void){//init Port 4
    P4->SEL0 &=~ 0x0F7;
    P4->SEL1 &=~ 0x0F7;
    P4->DIR |= 0x0F7;
    P4->OUT &=~ 0x0F7;
}

//initialize systick
void systick_init(void){//init SysTick
    SysTick->CTRL=0;
    SysTick->LOAD=0x00FFFF;
    SysTick->VAL=0;
    SysTick->CTRL=0x00000005;
}

//delay in microseconds
void delay_micro(unsigned microsec){//Use SysTick to delay in Microseconds
    SysTick->LOAD=((microsec*3)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

//delay in milliseconds
void delay_ms(unsigned ms){//Use SysTick to delay in milliseconds
    SysTick->LOAD=((ms*3000)-1);
    SysTick->VAL=0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

//pulse the enable pin
void PulseEnablePin(void){
    P4->OUT &=~ BIT1;
    delay_micro(10);
    P4->OUT |= BIT1;
    delay_micro(10);
    P4->OUT &=~ BIT1;
}

//send a nibble of data to the LCD
void pushNibble(uint8_t nibble){//send data to the LCD
    P4->OUT &=~ 0xF0;
    P4->OUT |= (nibble & 0x0F)<<4;
    PulseEnablePin();
}

//seperate a byte into two nibbles and send them to pushNibble
void pushByte(uint8_t byte){//Split a byte into two nibbles to send to the LCD
    uint8_t nibble;
    nibble = (byte & 0xF0)>>4;
    pushNibble(nibble);
    nibble = byte & 0x0F;
    pushNibble(nibble);
    delay_micro(100);
}

//write a command to the LCD
void write_command(uint8_t command){//send commands to the LCD
    P4->OUT &=~ BIT0;
    pushByte(command);
}

//write data to the LCD
void write_data(uint8_t data){//send data to the LCD
    P4->OUT |= BIT0;
    pushByte(data);
}

//print a string to the LCD
void print_string(char string[]){//send a string to the LCD
    int i;
    for(i=0; i<strlen(string); i++){
        write_data(string[i]);
    }
}

//initialize the LCD
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

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    static volatile uint16_t result;
    float nADC;
    int i;
    char buffer[50];

    systick_init();
    ADC14_init();
    port4_init();
    LCD_init();

    print_string("Current Temp. Is");

    for(i = 0; i<4; i++){
            write_command(0b10100);
        }

    while(1){
            ADC14->CTL0|=1;
            while(!ADC14->IFGR0);
            result = ADC14->MEM[0];
            nADC = result;
            nADC = (nADC * 3.3)/16384;
            nADC = nADC * 1000;
            nADC = (nADC - 500)/10;

            sprintf(buffer, "%.1f", nADC);

            print_string(buffer);
            write_data(223);
            write_data('C');
            delay_ms(500);
            for(i = 0; i<(strlen(buffer)+2); i++){
                    write_command(0b10000);
                }
        }
}
