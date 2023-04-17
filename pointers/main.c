#include <msp430.h> 

int a[5] = {1,2,3,4,5};
int *pnt_a;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	pnt_a = a;
	*pnt_a = 2021;
	pnt_a += 3;
	*pnt_a = 0;
	pnt_a = a;

	while(1);

}
