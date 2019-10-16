// Author: Sean Prendergast
// Code was initially started on October 3rd, 2019
// Code was last modified on October 15th, 2019
// Submitted October 17th, 2019
// Exercise: Hardware PWM FR6989

#include <msp430.h>

volatile int duty = 500; // Value of the duty cycle

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog timer (WDT)

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    P9DIR |= BIT7;  // Set P9.7 (LED2) to output direction
    P1DIR |= BIT0;  // Set P1.0 (LED1) to output direction
    P1SEL0 |= BIT0;  // Set P1.0 (LED1) to PWM
    P1DIR &= ~BIT1; // Set P1.1 (button/switch) to input direction
    P1OUT =  BIT1;  /* Set P1.1 (Pin 1, Bit 1) as the input pin, in other words,
                      the internal resistor is connected to 3.6 V (VCC) and functions as a pull-up resistor.*/
    P1REN |= BIT1;  /* Enables internal resistor such that P1.1 (Pin 1, Bit 1)
                       can be connected to 3.6 V (VCC) or ground (GND)*/
    P1IE |= BIT1;   // Interrupt enable for P1.1 (button/switch)
    P1IES |= BIT1;  // Interrupt enable on low to high edge for P1.1 (button/switch)
    P1IFG &= ~BIT1; // Clear interrupt flags for P1.1 (button/switch)

    TA0CCR0 = 1000;       // 100% duty cycle
    TA0CCTL1 = OUTMOD_7;  // Set output mode
    TA0CCR1 = duty;       // 50% duty cycle
    TA0CTL = TASSEL_2 + MC_1; // Timer is initialized

     __bis_SR_register(LPM0_bits + GIE);  // Interrupt is enabled in LPM0 (Low-power mode 0)
    }

#pragma vector=PORT1_VECTOR        // Interrupt triggers on button press
__interrupt void Button(void)
{
          P9OUT ^= BIT7;    // Debugging LED (P9.7) toggle
     if (duty == 1000)
     {        // If duty cycle is set at 100%
            duty = 0;          // Set duty cycle back to 0%
     }
     else
     {
            duty += 100;   // Duty cycle increments by 10%
     }
    TA0CCR1 = duty;          // Set duty cycle
    P1IFG = ~BIT1;            // Interrupt flag off
}
