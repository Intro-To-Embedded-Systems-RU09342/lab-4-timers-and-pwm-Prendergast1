# Software Debouncing
Debouncing a signal is a necessary step when adding mechanical switches to digital circuits so a single press doesn't appear like multiple presses. You're going to need this feature in a later portion of this lab as you'll be using a button press to change the duty cycle of your signal and you don't want to count the "false positives" as a button press. Debouncing is also only one of many applications which would require the use of built in Timers to allow for other processes to take place. Check out this nice tutorial on the subject. [http://www.labbookpages.co.uk/electronics/debounce.html]

## Task
You'll need to use the TIMER modules within the MSP430 processors to implement a debounced switch to control the state of an LED. You'll likely want to hook up your buttons on the development boards to an oscilloscope to see how much time it takes for the buttons to settle. The idea here is that your processor should be able to run other code, while relying on timers and interrupts to manage the debouncing in the background. *You should not be using polling techniques for this assignment.*

## Deliverables
You will need to have two folders in this repository, one for each of the processors that you used for this part of the lab. Remember to replace this README with your own.

### Hints
You need to take a look at how the P1IE and P1IES registers work and how to control them within an interrupt routine. Remember that the debouncing is not going to be the main process you are going to run by the end of the lab.

## Extra Work
### Low Power Modes
Go into the datasheets or look online for information about the low power modes of your processors and using Energy Trace, see what the lowest power consumption you can achieve while still running your debouncing code. Take a note when your processor is not driving the LED (or unplug the header connecting the LED and check) but running the interrupt routine for your debouncing.

### Double the fun
Can you expand your code to debounce two switches? Do you have to use two Timer peripherals to do this?

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
