#include <msp430.h> 

volatile int sensorout;
void straight (void);
void turnright (void);
void turnleft (void);
void stop (void);
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watch dog timer

    P1DIR |= 0xE7; //define  P1.4 P1.3 input, 2 sensors, the rest output
    P1SEL |= BIT6; //define P1.6 as timer (PWM)
    P2DIR = 0xFF; //define P2 port as output

    int period = 0x0FFF;  //PWM period
    float D = 0.52; //duty cycle

    TACCR0 = period-1;  //PWM period
    TACCR1 = period*D;  //CCR1 PWM Duty Cycle
    TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
    TACTL = TASSEL_2|MC_1;   //SMCLK submain clock,upmode
    while (1){
        sensorout = P1IN & 0x18;  // sensor sends high value on black line to P1.3 and P1.4
        if (sensorout == 0x18)
            straight();
        else if (sensorout == 0x08)  //1000
            turnright();
        else if (sensorout ==  0x10)  //0001
            turnleft();
        else if (sensorout ==  0x00)
            stop();
    }
}
void straight(void){
    P2OUT = 0x00;
    P2OUT |= 0x18; //takes high value on black line to P2.2 and P2.5
}
void turnright(void){
    P2OUT = 0x00;
    P2OUT |= 0x08; //1000
}
void turnleft(void){
    P2OUT = 0x00;
    P2OUT |= 0x10; //0001
}
void stop(void){
    P2OUT = 0x00;
    P2OUT |= 0x00;
}
