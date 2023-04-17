


#include <msp430g2553.h>


//huseyinsanal (works 1 line)

/**
 * Hüseyin Þanal
 * 2018514056
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR = 0X01;  //x can be also and P1.0 is setted as an output
    P1OUT = 0X01;  //

}
