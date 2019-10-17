# Sean Prendergast

## Debouncing

For this assignment, all implemented code would be written in C with the ultimate goal consisting of changing the state of the on-board LED, between on and off, as the on-board button/switch is pressed by the user and the signal from the button/switch is being debounced. In order to implement this program accordingly, the timer would be built to run at 2 ms. The reason the timer was built to run at this specific rate is to prevent the possibility of having the signal from the on-board button/switch change several times over the duration of this period. Having the timer run at this rate would allow the LED to toggle at a much more applicable rate visible to the user.

## Processors Utilized
* MSP430FR6989
* MSP430G2553

## Dependencies
This library would only be dependent on the MSP430.h header file used for all TI MSP430 processors. The MSP430.h header file is included in each C file submitted as no other header files were required for the assignment.

## Differences in implementation for FR6989 and G2553
One difference regarding the implementation for both boards, which will probably be seen for many assignments this semester, was that for the MSP430FR6989, the GPIO power-on default high impedance mode had to be disabled prior to testing. The reason behind this action is because the user will not be able to access any previously configured port settings if the default high-impedance mode isn't disabled. To put this into simpler terms, the user will not be able to utilize the appropriate ports and bits assigned to the on-board LEDs if this mode isn't disabled. The only other difference seen in both boards was the designated pins and bits assigned to the on-board button/switch. For both programs, these pins and bits were easily rearranged to ensure the appropriate ones assigned specificially to the on-board button/switch were utilized effectively.
