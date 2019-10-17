# Sean Prendergast

## Hardware PWM

For this assignment, all implemented code would be written in C with the ultimate goal consisting of replicating the behavior showcased in Software PWM such that the LED would initially be on at a 50% duty cycle. As also shown in Software PWM, the duty cycle of the LED would increase by 10% every time the button/switch is pressed by the user, and once a 100% duty cycle is met, the duty cycle of the LED would then reset to 0% after the next press. Two timers would be instantiated such that the first timer was utilized to debounce the button/switch while the second timer would be used for utilizing the processor's internal PWM function. The timer would directly output to a GPIO pin for the program, where in this case the output would be represented as the on-board LED, which is compatible and could be incorporated alongside the processor's internal PWM function, in addition to selecting the PWM mode for the designated LED under test.
## Processors Utilized
* MSP430FR6989
* MSP430G2553

## Dependencies
This library would only be dependent on the MSP430.h header file used for all TI MSP430 processors. The MSP430.h header file is included in each C file submitted as no other header files were required for the assignment.

## Differences in implementation for FR6989 and G2553
One difference regarding the implementation for both boards, which will probably be seen for many assignments this semester, was that for the MSP430FR6989, the GPIO power-on default high impedance mode had to be disabled prior to testing. The reason behind this action is because the user will not be able to access any previously configured port settings if the default high-impedance mode isn't disabled. To put this into simpler terms, the user will not be able to utilize the appropriate ports and bits assigned to the on-board LEDs if this mode isn't disabled. The only other difference seen in both boards was the designated pins and bits assigned to the on-board button/switch. For both programs, these pins and bits were easily rearranged to ensure the appropriate ones assigned specificially to the on-board button/switch were utilized effectively.
