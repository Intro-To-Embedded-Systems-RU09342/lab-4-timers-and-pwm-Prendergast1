// Author: Sean Prendergast
// Code was initially started on September 18th, 2019
// Code was last modified on October 15th, 2019
// Submitted October 15th, 2019
// Exercise: Software PWM G2553

#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           //stop watchdog timer (WDT)

    P1DIR |= BIT0;                      // Set P1.0 (LED1) to output direction
    P1DIR |= BIT6;                      // Set P1.6 (LED2) to output direction
    P1OUT &= ~BIT6;                     // Turn P1.6 (LED2) off

    P1DIR &= ~BIT3;                     // Set P1.3 (button/switch) to input direction
    P1REN |= BIT3;                      /* Enables internal resistor such that P1.3 (Pin 1, Bit 3)
                                        can be connected to 3.6 V (VCC) or ground (GND)*/
    P1OUT |= BIT3;                      /* Set P1.3 (Pin 1, Bit 3) as the input pin, in other words,
                                        the internal resistor is connected to 3.6 V (VCC) and functions as a pull-up resistor.*/
    P1IES |= BIT3;                      // Interrupt enable on low to high edge for P1.3 (button/switch)
    P1IE |= BIT3;                       // Interrupt enable for P1.3 (button/switch)
    P1IFG &= ~BIT3;                     // Clear interrupt flags for P1.3 (button/switch)

    TA1CTL = TASSEL_2 | MC_2;           // Timer A0 is initialized
    TA1CCR0 = 64;                       // Debounce time is set
    TA1CCTL0 |= CCIE;                   // Interrupt is enabled
    TA1CTL |= TAIE;                     // Enable interrupts

    TA0CTL = TASSEL_2 | MC_1;           // Timer A1 is initialized
    TA0CCR0 = 1000;                     // 100% duty cycle
    TA0CCR1 = 500;                      // 50% duty cycle
    TA0CCTL0 |= CCIE;                   // Interrupt is enabled
    TA0CCTL1 |= CCIE;                   // Interrupt is enabled
    TA0CTL |= TAIE;                     // Interrupt is enabled

    __bis_SR_register(LPM0_bits + GIE); // Interrupt is enabled in LPM0 (Low-power mode 0)

   while(1){}
}
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
{
    P1IFG &= ~BIT3;             // Interrupt flag is cleared
    TA1R = 0;                   // Timer is reset
    TA1CTL = TASSEL_1 | MC_2;   // Start in continuous mode
}

void __attribute__((interrupt(TIMER1_A0_VECTOR))) timer1_A0 (void)
{
    TA1CTL &= ~TAIFG;           // Interrupt flag is cleared
    TA1CTL &= ~MC_3;            // Debouncing is stopped

    if(!(P1IN & BIT3) && (P1IES & BIT3)) // If button/switch (P1.3) is pressed by the user
    {
        P1IES &= ~BIT3;                 // Change button/switch (P1.3) interrupt edge
        P1OUT |= BIT6;                  // Turn on P1.6 (LED)

        if(TA0CCR1 <= 900)              // If the duty cycle is not 100%
        {
            TA0CCR1 += 100;             // The duty cycle is increased by 10%
            TA0CTL |= MC_1;             // Up mode
        }
        else
        {
            TA0CCR1 = 0;                // Duty cycle is set back to 0
            TA0CTL &= ~MC_3;            // Timer is stopped
            P1OUT &= ~BIT0;             // P1.0 (LED) is turned off
        }
    }

    if((P1IN & BIT3) && !(P1IES & BIT3)) // If the button/switch (P1.3) is released by the user
    {
        P1IES |= BIT3;              // Button/switch (P1.3) interrupt edge is changed
        P1OUT &= ~BIT6;             // Turn off LED (P1.6)
    }
}

void __attribute__((interrupt(TIMER0_A0_VECTOR))) timer0_A0 (void)
{
    TA0CTL &= ~TAIFG;               // Interrupt flag is cleared
    P1OUT |= BIT0;                  // Turn on LED (P1.0)
}

void __attribute__((interrupt(TIMER0_A1_VECTOR))) timer0_A1 (void)
{
    if(TA0IV == 0x02)               // If the interrupt was generated from CCR1 compare
    {
        P1OUT &= ~BIT0;             // Turn off LED1 (P1.0)
    }
}
