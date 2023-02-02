/*
 *  Button Interrupt Example
 *
 *  Created on: Jan 30, 2023
 *      Author: Russell Trafford
 *      Version: 1.0
 *
 *      This example will show you how to configure an Interrupt and Interrupt Service Routine.
 *
 *      Your task for this lab is to change which LED each time the button has been pressed.
 *      For example, this starts blinking the Red LED, and then when the button is pressed,
 *      it should move to the Green LED. If the button is pressed again, it should move to the Red LED again.
 *
 *      There have been some "todo" notes which can be helpful in finding things to change in the code.
 */


#include <msp430.h>

char ToggleEnable = 0x01;                       // Global Variable to track if the LED should be on or off

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    // Configure GPIO
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    // @TODO You need to add in the configuration for the Green LED

    P6OUT &= ~BIT6;                         //Init Green LED
    P6DIR |= BIT6;                          //Set green led to output

    P2OUT |= BIT3;                          // Configure P2.3 as pulled-up
    P2REN |= BIT3;                          // P2.3 pull-up register enable
    P2IES &= ~BIT3;                         // P2.3 Low --> High edge
    P2IE |= BIT3;                           // P2.3 interrupt enabled

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    P2IFG &= ~BIT3;                         // P2.3 IFG cleared

    __bis_SR_register(GIE);                 // Enter LPM3 w/interrupt

    while(1)                                // Infinite loop to run forever
    {

        if (ToggleEnable){                  // Check for interrupt from button
            P6OUT &= ~BIT6;                 //Turn green led off
            while (ToggleEnable) {         // Checks if interrupt is still on
            P1OUT ^= BIT0;                  // Toggle red led

            __delay_cycles(100000);         // Blinks every 0.1s
            }
        }
        else{                               // Checks if no interrupt
            P1OUT &= ~BIT1;                 // Turns off red led
                        while (!ToggleEnable) { //Runs while no interrupt
                        P6OUT ^= BIT6;            //Toggles green led

                        __delay_cycles(100000);     //Blinks every 0.1s
                        }
        }

    }
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    // @TODO You might need to modify this based on your approach to the lab
    P2IFG &= ~BIT3;                         // Clear P1.3 IFG
    ToggleEnable ^= 0x01;                   // Enable if the toggle should be active
}

