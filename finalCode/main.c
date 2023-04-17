//infrared sensors for line following robot, disconnect the UART jumpers if you're using P1.1. and P1.2
//observe the port registers P1DIR and P1IN
#include <msp430.h> 
#include"PCD8544.h"

#define LCD5110_SCLK_PIN            BIT5
#define LCD5110_DN_PIN              BIT7
#define LCD5110_SCE_PIN             BIT0
#define LCD5110_DC_PIN              BIT1
#define LCD5110_SELECT              P1OUT &= ~LCD5110_SCE_PIN
#define LCD5110_DESELECT            P1OUT |= LCD5110_SCE_PIN
#define LCD5110_SET_COMMAND         P1OUT &= ~LCD5110_DC_PIN
#define LCD5110_SET_DATA            P1OUT |= LCD5110_DC_PIN
#define LCD5110_COMMAND             0
#define LCD5110_DATA                1

// LCD functions declaration

// Sets LCD address (x = 0..83, y = 0..5)
void setAddr(unsigned char xAddr, unsigned char yAddr);
void writeToLCD(unsigned char dataCommand, unsigned char data);
void writeCharToLCD(char c);
void writeStringToLCD(const char *string);
void initLCD();
void clearLCD();

volatile int sensorout;
void straight (void);
void turnright (void);
void turnleft (void);
void stop (void);
void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= 0xE7; //defining  P1.4 P1.3  as input, 2 sensors, the rest output
    P1SEL |= BIT6; //defining P1.6 as timer (PWM)
    P2DIR = 0xFF;

    P1OUT |= LCD5110_SCE_PIN | LCD5110_DC_PIN;  // Disable LCD, set Data mode
    P1DIR |= LCD5110_SCE_PIN | LCD5110_DC_PIN;  // Set pins to output direction

    // Setup USIB
    P1SEL |= LCD5110_SCLK_PIN | LCD5110_DN_PIN;
    P1SEL2 |= LCD5110_SCLK_PIN | LCD5110_DN_PIN;

    UCB0CTL0 |= UCCKPH | UCMSB | UCMST | UCSYNC; // 3-pin, 8-bit SPI master
    UCB0CTL1 |= UCSSEL_2;               // SMCLK
    UCB0BR0 |= 0x01;                    // 1:1
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;               // clear SW

    initLCD();

    int period = 0x0FFF;  //PWM period
    float D = 0.52; //duty cycle
    TACCR0 = period-1;  //PWM period
    TACCR1 = period*D;  //CCR1 PWM Duty Cycle
    TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
    TACTL = TASSEL_2|MC_1;   //SMCLK submain clock,upmode
    while (1){
        sensorout = P1IN & 0x18;// sensor sends high voltage on dark surface
        if (sensorout == 0x18){

            clearLCD();
            setAddr(9,2);
            writeStringToLCD("STRAIGHT");

            straight();

        }
        else if (sensorout == 0x08){

            clearLCD();
            setAddr(9,2);
            writeStringToLCD("TURN RIGHT");

            turnright();


        }
        else if (sensorout ==  0x10){

            clearLCD();
            setAddr(9,2);
            writeStringToLCD("TURN LEFT");

            turnleft();

}

        else if (sensorout ==  0x00){
            clearLCD();
            setAddr(9,2);
            writeStringToLCD("STOP");

            stop();

        }
    }
}

void straight(void){
    P2OUT = 0x00;
    P2OUT |= 0x24;

}
void turnright(void){
    P2OUT = 0x00;
    P2OUT |= 0x20;

}
void turnleft(void){
    P2OUT = 0x00;
    P2OUT |= 0x04;

}
void stop(void){
    P2OUT = 0x00;
    P2OUT |= 0x00;

}

void setAddr(unsigned char xAddr, unsigned char yAddr) {
    writeToLCD(LCD5110_COMMAND, PCD8544_SETXADDR | xAddr);
    writeToLCD(LCD5110_COMMAND, PCD8544_SETYADDR | yAddr);
}

void writeToLCD(unsigned char dataCommand, unsigned char data) {
    LCD5110_SELECT;

    if(dataCommand) {
        LCD5110_SET_DATA;
    } else {
        LCD5110_SET_COMMAND;
    }

    UCB0TXBUF = data;
    while(!(IFG2 & UCB0TXIFG));
    LCD5110_DESELECT;
}

void initLCD() {
    writeToLCD(LCD5110_COMMAND, PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    writeToLCD(LCD5110_COMMAND, PCD8544_SETVOP | 0x3F);
    writeToLCD(LCD5110_COMMAND, PCD8544_SETTEMP | 0x02);
    writeToLCD(LCD5110_COMMAND, PCD8544_SETBIAS | 0x03);
    writeToLCD(LCD5110_COMMAND, PCD8544_FUNCTIONSET);
    writeToLCD(LCD5110_COMMAND, PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

void writeCharToLCD(char c) {
    unsigned char i;
    for(i = 0; i < 5; i++) {
        writeToLCD(LCD5110_DATA, font[c - 0x20][i]);
    }
    writeToLCD(LCD5110_DATA, 0);
}

void writeStringToLCD(const char *string) {
    while(*string) {
        writeCharToLCD(*string++);
    }
}

void clearLCD() {
    setAddr(0, 0);
    int i = 0;
    while(i < PCD8544_MAXBYTES) {
        writeToLCD(LCD5110_DATA, 0);
        i++;
    }
    setAddr(0, 0);
}


