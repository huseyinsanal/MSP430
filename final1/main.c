#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0x41;  //set the P1.0 and P1.6 ports as outputs( 41= 0100 0001 )
	P1OUT = 0x41;  //sets the P1.0 and P1.6 output ports as 1

	/*
	 * All other ports are input after this definition
	 */


	P2DIR = 0x01; //sets the P2.0 as output ( 01 = 0000 0001 )

	/*
	 * All other ports are input after this definition
	 */

	P2IN & 0x04;
}
