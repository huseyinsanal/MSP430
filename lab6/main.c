#include <msp430.h> 

volatile long tempRaw;
volatile long celcius;

/**
 * Hüseyin Þanal
 * 2018514056
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	if(CALBC1_1MHZ == 0XFF || CALDCO_1MHZ == 0XFF){
	    while(1);
	}

//DCO callibration part
	BCSCTL1 = CALBC1_1MHZ; //Basic clock system controller 1
	DCOCTL = CALDCO_1MHZ;

	IFG1 &= ~OFIFG;   //Set interrupt Flag generator
	BCSCTL2 |= SELM_0 + DIVM_3;  //MCLK = DCO/8

	while(1){
	    ADC10CTL1 = INCH_10 + ADC10DIV_0;

	    ADC10CTL0 |= SREF_1 + ADC10SHT_3 +REFON + ADC10ON; //REFON sets Vref = 2.5V
	    _delay_cycles(5); // wait for ADC Ref to settle

	    ADC10CTL0 |= ENC + ADC10SC; // Sampling & Conversion start
	    _delay_cycles(100);

	    ADC10CTL0 &= ~ENC;
	    ADC10CTL0 &= ~(REFON +ADC10ON); // Stop sampling & conversion

	    tempRaw = ADC10MEM; //Measurement stored in tempRaw.

	    celcius = ((tempRaw - 673) * 423) / 1024; //celcius value



	}


}
