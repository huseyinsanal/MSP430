#include <msp430.h> 

#define BUTTON BIT3
int count = 0;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1IE = BUTTON; //interrupt enabled for P1.3 -- button
	P1IES = BUTTON; //interrupt edge select - falling edge high to low
	P1IFG = 0x00;
	_enable_interrupts();
	while(1);
	
}
#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void){

    count += 1;
    P1IFG = 0x00;
}
