//infrared sensors for line following robot, disconnect the UART jumpers if you're using P1.1. and P1.2
//observe the port registers P1DIR and P1IN
#include <msp430.h> 

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
    P2DIR = 0xFF; //defining P2 port as output

    int period = 0x0FFF;  //PWM period
    float D = 0.52; //duty cycle
    TACCR0 = period-1;  //PWM period
    TACCR1 = period*D;  //CCR1 PWM Duty Cycle
    TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
    TACTL = TASSEL_2|MC_1;   //SMCLK submain clock,upmode

    while (1){
        sensorout = P1IN & 0x18; // sensor sends high voltage on dark surface
        if (sensorout == 0x18)
            straight();
        else if (sensorout == 0x08)
            turnright();
        else if (sensorout ==  0x10)
            turnleft();
        else if (sensorout ==  0x00)
            stop();
    }
}
//first motor poles are in P2.2 and P2.3
//second motor poles are in P2.4 and P2.5
void straight(void){
    P2OUT = 0x00;
    P2OUT |= 0x24;  //0010 01000
}
void turnright(void){
    P2OUT = 0x00;
    P2OUT |= 0x20;  //0010 0000
}
void turnleft(void){
    P2OUT = 0x00;
    P2OUT |= 0x04;  //0000 01000
}
void stop(void){
    P2OUT = 0x00;
    P2OUT |= 0x00;
}
