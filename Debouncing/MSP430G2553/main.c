// Author: Sean Prendergast
// Code was initially started on September 18th, 2019
// Code was last modified on October 15th, 2019
// Submitted October 3rd, 2019
// Exercise: Debouncing for MSP430G2553

#include <msp430.h>

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer (WDT)

    P1DIR |= BIT0;                  // Set P1.0 (LED) to the output direction
    P1OUT &= ~BIT0;                 // Turn off P1.0 (LED)

    P1DIR &= ~BIT3;                 // Set P1.3 (button/switch) to input direction
    P1REN |= BIT3;                  /* Enables internal resistor such that P1.3 (Pin 1, Bit 3)
                                    can be connected to 3.6 V (VCC) or ground (GND)*/
    P1IE |= BIT3;                   // Interrupt is enabled on P1.3 (button/switch)
    P1IES |= ~BIT3;                 // Set interrupt flag on high to low for P1.3 (button/switch)
    P1IFG &= ~BIT3;                 // Clear interrupt flag for P1.3 (button/switch)


    TA0CCR0 = 64;                   // Set value for debouncing time
    TA0CCTL0 |= CCIE;               // Interrupt is enabled
    TA0CTL |= TASSEL_1 + MC_2;      // Timer 0 is set up

    __enable_interrupt();           // Interrupt is enabled

    __bis_SR_register(LPM0 + GIE);  // Interrupt is enabled in LPM0 (Low-power mode 0)

    while(1)
    {
            }
}

void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A0 (void)
{
    TA0CTL &= ~TAIFG;       // Interrupt flag is cleared
    TA0CTL |= MC_0;         // Timer is stopped

    if(!(P1IN & BIT3))      // If button/switch (P1.3) is pressed
        P1OUT ^= BIT0;      // The LED (P1.0) will toggle on and off
}

void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
{
        P1IFG &= ~BIT3;     // Interrupt flag is cleared
        TA0R = 0;           // Timer is reset
        TA0CTL |= MC_2;     // Start continuous mode
}
