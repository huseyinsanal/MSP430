#include <msp430.h> 


/**
 * Hüseyin Þanal
 * main.c
 */

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0X01;
	P1OUT = 0X00;  //setting an initial value for the output pin(s)
	P1REN = 0X00;  //disable pullup/pulldown resistors

	while(1){
	    P1OUT ^= 0X01;
	    __delay_cycles(500000);
	}
}
