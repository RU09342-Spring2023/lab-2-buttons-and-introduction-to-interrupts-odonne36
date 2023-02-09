//Matt O'Donnell
//2/2/23



#include <msp430.h>



unsigned int state = 0;
unsigned int reset = 0;
unsigned int count =0;
unsigned int detected=0;
void main() {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
     P6DIR |= BIT6;              // Configure green led to an Output
     P6OUT &= ~BIT6;            //Turn off green led

                     P2REN |= BIT3;     //Enable the 2.3 pull-up resistor
                   P2OUT |= BIT3;       // Set P2.3 button as an output
                   P2IES &= ~BIT3;      // Set interrupt sens to low --> high
                   P2IE |= BIT3;        // Set interrupt enable to true
                   P2IFG &= ~BIT3;      // Clear interrupt flag


              P4REN |= BIT1;            // Enable 4.1 pull-up resistor
              P4OUT |= BIT1;            // Initalize 4.1 as an output
              P4IES &= ~BIT1;           // Set interrupt sens low --> high
              P4IE |= BIT1;             // Enable interrupt
              P4IFG &= ~BIT1;           // Clear interrupt flag


              P1DIR |= BIT0;              // Configure red led to an Output
               P1OUT &= ~BIT0;            // Turn off red led

         PM5CTL0 &= ~LOCKLPM5;          // Set power mode


         __bis_SR_register(GIE);        // Enable global interrupts

while(1) {


while (state ==0){                      // Check if in armed state
    P6OUT ^= BIT6;                      // Toggle green led
    P1OUT &= ~BIT0;                     // Turn off red led
    __delay_cycles(1000000);            //Wait 1s
    if (detected)                       // If interrupt on button 4.1 set the state to alert
        state =1;
}




if (detected){                          // Check if person is in room
while(state == 1) {                     // Ensure in alert state
    P6OUT &= ~BIT6;                     // Turn off green led
    P1OUT ^= BIT0;                      // Toggle red led every 0.1 ms
    __delay_cycles(100000);
    count++;                            // Keep count of how many times led blinks

    if (count == 100 && !(P4IN & BIT1)) {   // If led blinks 100 times (10s) and there is still a person detected set the state to 2 (alarm)
        state = 2;
        count = 0;

    }
    else if (count == 100 && (P4IN & BIT1)){        // Else if it waited 10s and it doesn't detect a person, go back to armed state
        state = 0;
        count = 0;
        detected=0;
    }
}


}

while (state == 2) {                                  // While in alarm state, keep red led on and green led off
 P1OUT |= BIT0;
 P6OUT &= ~BIT6;



}





}



}



#pragma vector=PORT4_VECTOR                      //P4.1 interrupt
__interrupt void Port_4(void)
{

    P4IFG &= ~BIT1;                             // Clear interrupt flag
    detected = 0x01;                            // Set detected variable to 1
    P6OUT &= ~BIT6;                             // Turn off green led

}

#pragma vector=PORT2_VECTOR                     // P2.3 Interrupt
__interrupt void Port_2(void)
{
    P1OUT &= ~BIT0;                             //Turn off red led
    P2IFG &= ~BIT3;                             // Clear interrupt flag


    if (state == 2) {                           // Check in alarm state only, and go back to armed state and clear all var
        reset = 1;
            count = 0;
            detected=0;
            state=0;
    }

}
