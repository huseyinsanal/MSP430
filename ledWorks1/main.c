#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0x01;
	P1OUT = 0x00;
	P1REN = 0x00; //disable pull up/pull down resistors

	while(1){

	    P1OUT ^= 0x01;
	    __delay_cycles(1000000); //default clock speed is 1 MHz

	}
}
