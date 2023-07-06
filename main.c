#include <msp430.h> 
#define led BIT0

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= led;
	P1OUT &= ~led;

	//setup timer
	TA0CTL |= TACLR; //reset TB0
	TA0CTL |= MC__UP;
	TA0CTL |= TASSEL__ACLK;
    TA0CCR0 = 16384; //set CCR0

    //-setup timer compare

    TA0CCTL0 |= CCIE; // local enable for CCR0
    __enable_interrupt();
    TA0CCTL0 &= ~CCIFG; //clear flag
	for(;;){}
	
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void ISR_TA0_CCR0(void){
    P1OUT  ^= led;
    TA0CCTL0 &= ~CCIFG;
}
