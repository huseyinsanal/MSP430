#include <msp430.h> 

#define LED BIT0
#define BUTTON BIT3

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = LED;
	P1OUT = LED;
	P1IE = BUTTON; //interrupt enabled for P1.3 --- button
	P1IES = BUTTON; //interrupt edge select -  falling edge high to low
	P1IFG = 0x00; //clear the interrupt flag

	_enable_interrupts();

	while(1); //infinite loop - waiting for interrupt

}

#pragma vector=PORT1_VECTOR

__interrupt void PORT1_ISR(void){
    P1OUT ^= 0x01; //toggle LED
    P1IFG = 0x00; //clear the interrupt flag

}

