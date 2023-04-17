#include  "msp430g2553.h"

// Create a PWM signal using Timer A
static volatile int period = 1000;

void triangleWave();
void delay ( unsigned int );


 void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;


  BCSCTL2 |= SELM_1 ; // Basic Clock System Control Register ---> DCO

  P1DIR |= BIT6;                            // Set P1.6 to output direction
  P1SEL |= BIT6;                            // P1.6 to TA0.1
// Timer A control register
  TACTL = TASSEL_2 + MC_3;                  // SMCLK, up down mode

  CCR0 = period-1;                          // PWM Period
  CCTL1 = OUTMOD_7;                         // TACCR1 reset/set
  CCR1 = 0;                                 // CCR1 PWM duty cycle

  triangleWave();
}

void triangleWave(){
    int upDown = 1;
    while(1){
        CCR0 = period-1;
        if (upDown == 1){
            CCR1 = (CCR1 + 1) % period;
            if (CCR1 == period-1) {
                upDown = 0;
            }
            delay(1);
        }
        else {
            CCR1 = (CCR1 - 1) % period;
            if (CCR1 == 0) {
                upDown = 1;
            }
            delay(1);
        }
    }
}

void delay(unsigned int ms)
{
 while (ms--)
    {
        __delay_cycles(1000);
    }
}
