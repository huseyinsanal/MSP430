#include <msp430.h> 


/**
 * 2018514056
 * Hüseyin Þanal
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	BCSCTL1 = CALBC1_1MHZ;  //1MHZ clock
	DCOCTL = CALDCO_1MHZ;

	CCTL0 = CCIE;   //CCR0 interrupt enabled

	BCSCTL2 |= SELM_1;

	//Timer A control register

	TACTL = TASSEL_2 + MC_1 + ID_3;   //SMCLK/8,upmode
	CCR0 = 125000;  // 125kHz
	P1OUT = 0;
	P1DIR |= BIT0 + BIT6;   //All led pins are output
	P1DIR &=~ BIT3; //button is input
	// for Ver 1.5 Enable Pul Up Resistor goes below for BIT3

	P1IE |= BIT3;   //Harware interrupt enable for BIT3
	P1IES |= BIT3;   //P1.3 Hi/lo edge

	P1REN |= BIT3;
	P1OUT |= BIT3;
	P1IFG &= ~BIT3;   //P1.3 IFG cleared

	while(1) //low power mode
	{
	    _BIS_SR(CPUOFF + GIE);   //GIE: Global Interrupt Enable
	}
}

//Timer A0 interrupt service routine

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= BIT0;   //Toggle P1.0
}

//The address of Port 1 interrupt service routine is PORT1_VECTOR
#pragma vector=PORT1_VECTOR
__interrupt void button (void)
{
P1OUT ^= BIT6;   //Toggle BIT1.6
P1IFG &= ~BIT3;  //Clear interrupt flug
__delay_cycles(1000);

}










