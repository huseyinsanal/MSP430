#include <msp430.h> 


/**
 * Hüseyin Þanal
 * 2018514056
 * main.c
 */
//Very-Low-Power Low Frequency Oscillator---DCO
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	if(CALBC1_1MHZ == 0XFF || CALDCO_1MHZ == 0XFF){
	    while(1);
	}

	BCSCTL1 = CALBC1_1MHZ; //Basic clock system controller 1
	DCOCTL = CALDCO_1MHZ;

	P1DIR = 0X40;
	P1OUT = 0;


	IFG1 &= ~OFIFG; //Interrupt flag generator
	_bis_SR_register(SCG1 + SCG0); //System register configuration

	BCSCTL2 |= SELM_1 + DIVM_3; //DCOCLK + /8

	while(1){ //Infinite loop

	    P1OUT = 0X40;
	    _delay_cycles(100);
	    P1OUT = 0;
	    _delay_cycles(5000); //3.3 second


	}







}
