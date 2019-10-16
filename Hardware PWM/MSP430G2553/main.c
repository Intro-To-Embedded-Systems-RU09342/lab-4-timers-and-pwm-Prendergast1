// Author: Sean Prendergast
// Code was initially started on October 3rd, 2019
// Code was last modified on October 15th, 2019
// Submitted October 3rd, 2019
// Exercise: Hardware PWM G2553

#include <msp430.h>

volatile int duty = 500; //duty cycle value

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        //stop watchdog timer

    P1DIR |= BIT0;                  // Set P1.0 to output direction
    P1DIR |= BIT6;                  // Set P1.6 to output direction
    P1SEL |= BIT6;                  // Set P1.6 to PWM
    P1OUT =  BIT3;                  /* Set P1.3 (Pin 1, Bit 3) as the input pin, in other words,
                                    the internal resistor is connected to 3.6 V (VCC) and functions as a pull-up resistor.*/
    P1REN |= BIT3;                  /* Enables internal resistor such that P1.3 (Pin 1, Bit 3)
                                     can be connected to 3.6 V (VCC) or ground (GND)*/
    P1IE |= BIT3;                   // Interrupt enable for P1.3 (button/switch)
    P1IES |= BIT3;                  // Interrupt enable on low to high edge for P1.3 (button/switch)
    P1IFG &= ~BIT3;                 // Clear interrupt flags for P1.3 (button/switch)

    TA0CCR0 = 1000;                 // 100% duty cycle
    TA0CCTL1 = OUTMOD_7;            // Set output mode
    TA0CCR1 = duty;                 // 50% duty cycle
    TA0CTL = TASSEL_2 + MC_1;       // Timer is initialized

     __bis_SR_register(LPM0_bits + GIE);  // Interrupt is enabled in LPM0 (Low-power mode 0)

}

#pragma vector=PORT1_VECTOR       // Interrupt triggers on button press
__interrupt void Button(void)
    {
              P1OUT ^= BIT0;    // Debugging LED (P1.0) toggle

     if (duty == 1000)          // If duty cycle is set at 100%
     {
            duty = 0;          // Set duty cycle back to 0%
        }
     else
     {
            duty += 100;        // Duty cycle increments by 10%
     }
        TA0CCR1 = duty;          // Set duty cycle
        P1IFG = ~BIT3;           // Interrupt flag off
    }
