//Matt O'Donnell
//2/2/23


#include <msp430.h>

 WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
 P6DIR |= BIT6;              // Configure green led to an Output
 P6OUT &= ~BIT6;
     P2DIR &= ~BIT3;             // Configure P2.3 to an Input

     P2REN |= BIT3;               // Enable Resistor on P2.3
     P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

          P4DIR &= ~BIT1;
          P4REN |= BIT1;
          P4OUT |= BIT1;

          P1DIR |= BIT0;              // Configure red led to an Output
           P1OUT &= ~BIT0;

     PM5CTL0 &= ~LOCKLPM5;

     unsigned int state = 0;
void main() {
while(1)
while (state ==0){
    P6OUT ^= BIT6;
    __delay_cycles(1000000);

}

if (persondetected && state ==0x00) {
state =1;
P6OUT &= ~BIT6;

while(persondetected()) {
    P1OUT ^= BIT0;
    __delay_cycles(100000);
}
}


if (state == 2) {
 P1OUT |= BIT0;
 P6OUT &= ~BIT6;

 if (P2OUT & BIT3)
     state=0;
}







}
}

int persondetected(int x) {
    if (!(P4OUT & BIT1 >0) && x==0) {
        return 1;
        __delay_cycles(10000000);

        persondected(1);
    }
    else
        return 0;

    if (x == 1 & P4OUT & BIT1 >0)
        persondetected(0);
        else{
           state=2;
    break;
    }
}
