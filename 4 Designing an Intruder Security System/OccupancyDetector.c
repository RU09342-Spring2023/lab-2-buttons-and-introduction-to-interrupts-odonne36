//Matt O'Donnell
//2/2/23


#include <msp430.h>

 WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
 P6DIR |= BIT6;              // Configure P6.6 to an Output
     P2DIR &= ~BIT3;             // Configure P2.3 to an Input

     P2REN |= BIT3;               // Enable Resistor on P2.3
     P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

          P4DIR &= ~BIT1;
          P4REN |= BIT1;
          P4OUT |= BIT1;

     PM5CTL0 &= ~LOCKLPM5;

void main() {

while (1)




}
