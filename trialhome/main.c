#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0X40;  //x can be also and P1.0 is setted as an output
	P1OUT = 0X40;  //
}
