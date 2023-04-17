#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0X41;
	P1OUT = 0X40;
	P1OUT = BIT3;
	P1REN = 0X08;
	
	for(;;){

	    if((P1IN & BIT3) == 0){

	        P1OUT |= 0X40;
	        P1OUT &=~ 0X01;


	    }
	    else{

	        P1OUT |= 0X01;
	        P1OUT &=~ 0X40;

	    }





	}


}
