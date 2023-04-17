#include <msp430.h> 


/**
 * Hüseyin Þanal
 * 2018514056
 * main.c
 */
//Very-Low-Power Low Frequency Oscillator---VLO
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR = 0X40;
    P1OUT = 0;

    BCSCTL3 |= LFXT1S_2; //VL0 basic clock controller

    IFG1 &= ~OFIFG; //Interrupt flag generator
    _bis_SR_register(SCG1 + SCG0); //System register configuration

    BCSCTL2 |= SELM_3 + DIVM_3; //VLOCLK + /8

    while(1){ //Infinite loop

        P1OUT = 0X40;
        _delay_cycles(100);
        P1OUT = 0;
        _delay_cycles(5000); //3.3 second


    }







}
