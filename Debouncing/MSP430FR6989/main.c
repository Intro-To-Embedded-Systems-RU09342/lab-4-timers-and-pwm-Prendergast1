// Author: Sean Prendergast
// Code was initially started on September 18th, 2019
// Code was last modified on October 15th, 2019
// Submitted October 3rd, 2019
// Exercise: Debouncing for MSP430FR6989

#include <msp430.h>

int main(void)
{
        WDTCTL = WDTPW | WDTHOLD;        //stop watchdog timer (WDT)
        PM5CTL0 &= ~LOCKLPM5;            /* Disable the GPIO power-on default high-impedance mode
                                         to activate previously configured port settings*/

        P1DIR |= BIT0;                   // Set P1.0 (LED) to output direction
        P1OUT &= ~BIT0;                  // Turn off P1.0 (LED)
        P1DIR &= ~BIT1;                  // Set P1.3 (button/switch) to input direction
        P1REN |= BIT1;                   /* Enables internal resistor such that P1.3 (Pin 1, Bit 3)
                                         can be connected to 3.6 V (VCC) or ground (GND)*/
        P1OUT |= BIT1;                  // Interrupt is enabled on P1.1 (button/switch)
        P1IFG = 0x00;                   // Clear interrupt flag
        P1IES |= BIT1;                  // Button/switch (P1.1) press triggers interrupts
        P1IE |= BIT1;                   // Interrupt is enabled on P1.1 (button/switch)

        TA0CTL |= TASSEL_2;             // SMCLK
        TA0CTL |= MC_2;                 // Continuous mode
        TA0CCR0 = 0x0041;               // Timer count up to 2ms
        TA0CCTL0 |= CCIE;               // Interrupt is enabled
        TA0CTL |= TAIE;                 // Timer 0 is set up

        __bis_SR_register(LPM0_bits + GIE);     // Interrupt is enabled in LPM0 (Low-power mode 0)


        while(1) {
                  __no_operation();
              }
        //loops infinitely
}


void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A0 (void)
{
        TA0CTL &= ~TAIFG;       // Interrupt flag is cleared
        TA0CTL &= ~MC_3;        // Stops timer

        if(!(P1IN & BIT1))
        {
            P1OUT ^= BIT0;       // The LED (P1.0) will toggle on and off
        }


}

// Button Interrupt
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
{//button interrupt
        P1IFG &= ~BIT1;         // Interrupt flag is cleared

        TA0R = 0;               // Timer is reset
        TA0CTL &= ~MC_3;
        TA0CTL |= MC_2;         // Timer is reset
}
