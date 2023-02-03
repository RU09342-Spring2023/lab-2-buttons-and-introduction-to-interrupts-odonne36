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
     P6OUT &= ~BIT6;

                     P2REN |= BIT3;
                   P2OUT |= BIT3;
                   P2IES &= ~BIT3;
                   P2IE |= BIT3;
                   P2IFG &= ~BIT3;


              P4REN |= BIT1;
              P4OUT |= BIT1;
              P4IES &= ~BIT1;
              P4IE |= BIT1;
              P4IFG &= ~BIT1;


              P1DIR |= BIT0;              // Configure red led to an Output
               P1OUT &= ~BIT0;

         PM5CTL0 &= ~LOCKLPM5;


         __bis_SR_register(GIE);

while(1) {


while (state ==0){
    P6OUT ^= BIT6;
    P1OUT &= ~BIT0;
    __delay_cycles(1000000);
    if (detected)
        state =1;
}




if (detected){
while(state == 1) {
    P6OUT &= ~BIT6;
    P1OUT ^= BIT0;
    __delay_cycles(100000);
    count++;

    if (count == 100 && !(P4IN & BIT1)) {
        state = 2;
        count = 0;

    }
    else if (count == 100 && (P4IN & BIT1)){
        state = 0;
        count = 0;
        detected=0;
    }
}


}

while (state == 2) {
 P1OUT |= BIT0;
 P6OUT &= ~BIT6;


}





}
}



#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{

    P4IFG &= ~BIT1;
    detected = 0x01;
    P6OUT &= ~BIT6;

}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1OUT &= ~BIT0;
    P2IFG &= ~BIT3;
    reset = 1;
    count = 0;
    detected=0;
    state=0;
}
