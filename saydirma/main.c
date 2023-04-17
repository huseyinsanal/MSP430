#include <msp430.h> 

/**
 * Hüseyin ÞANAL
 * 2018514056
 *  * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    P1DIR = 0X01;    // 0100 0001 P1DIR = BIT0;   P1DIR = BIT0 + BIT6; //bit 0 ve 6 output
    P1OUT = 0;      // Leds are off
    P1OUT = BIT3;   //p1.3 = 1
    P1REN |= 0X08;   //0000 1000 (bit 3 pullup/pulldown activated)

    for(;;){

        if((P1IN & BIT3 ) == 0 ){

            P1OUT &=~ 0X01;

        }

        else{
            P1OUT |= 0X01;


        }

    }

}

