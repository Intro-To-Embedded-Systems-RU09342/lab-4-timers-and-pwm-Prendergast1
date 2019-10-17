# Sean Prendergast

## Software PWM

For this assignment, all implemented code would be written in C with the ultimate goal consisting of having the on-board LED initially run at a 50% duty cycle when the processor starts up. Every time the on-board button/switch is pressed by the user, the duty cycle of the LED will increase by 10% until a 100% duty cycle is met. Once a 100% duty cycle has been reached for the LED, the LED will turn off and continue the same procedure beginning at a 0% duty cycle. The signal of the button/switch would also be debounced to optimize the performance of the entire program, this was achieved by initializing two timers. The first timer is responsible for debouncing the button/switch and the second timer for sending the PWM signal to the LED. In order to control the state of the LED between on and off at varying duty cycles, the output mode of the second timer would need to be modified.
## Processors Utilized
* MSP430FR6989
* MSP430G2553

## Dependencies
This library would only be dependent on the MSP430.h header file used for all TI MSP430 processors. The MSP430.h header file is included in each C file submitted as no other header files were required for the assignment.

## Differences in implementation for FR6989 and G2553
One difference regarding the implementation for both boards, which will probably be seen for many assignments this semester, was that for the MSP430FR6989, the GPIO power-on default high impedance mode had to be disabled prior to testing. The reason behind this action is because the user will not be able to access any previously configured port settings if the default high-impedance mode isn't disabled. To put this into simpler terms, the user will not be able to utilize the appropriate ports and bits assigned to the on-board LEDs if this mode isn't disabled. The only other difference seen in both boards was the designated pins and bits assigned to the on-board button/switch. For both programs, these pins and bits were easily rearranged to ensure the appropriate ones assigned specificially to the on-board button/switch were utilized effectively.
