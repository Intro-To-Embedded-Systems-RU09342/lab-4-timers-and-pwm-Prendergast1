// Debouncing G2553

#include <msp430.h>

int main(void)
{
        WDTCTL = WDTPW | WDTHOLD;//stop watchdog timer
        BCSCTL3 = LFXT1S_2;//use internal crystal
        P1SEL = 0; //port 1 is i/o
        P1DIR |= BIT0; //set p1.0 to output (to LED)
        P1DIR &= ~BIT3; //set p1.3 to input (from switch)
        P1IE |= BIT3; //enable interrupts on p1.3
        P1IES |= BIT3; //set interrupt to flag on a falling edge
        //P1REN |= BIT3; //enable pull resistor (apparently unnecessary)

        //initialize count up to value
        TACCR0 = 0x0041; //2ms delay time

        __bis_SR_register(GIE); //enable interrupts

        while (1);


}

//interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void PORT1_vector(void)//
{
    unsigned long delay;
    for(delay = 0; delay < 12345; delay = delay + 1)
    {
        P1OUT ^= BIT0;
    }

    P1IFG &= ~BIT3; //turn off the flag
}
