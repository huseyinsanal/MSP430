#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0X01; //P1.0 defined as output  0000 0001 (1 values are outputs)
	P1OUT = 0X01; //P1.0 defined as high

	P1DIR = 0X41; //P1.0 and P1.6 defined as output   0100 0001
	P1OUT = 0X41; //P1.0 and P1.6 defined as high


}
